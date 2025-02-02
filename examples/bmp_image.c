#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#include "../src/pluto.h"
 
struct bmp_file_hdr
{
    uint16_t bf_type;
    uint32_t bf_size;
    uint32_t reserved;
    uint32_t bf_offset;
 
    uint32_t bi_size;
    uint32_t bi_width;
    uint32_t bi_height;
    uint16_t bi_planes;
    uint16_t bi_bit_cnt;
    uint32_t bi_compression;
    uint32_t bi_size_image;
    uint32_t bi_x_per_met;
    uint32_t bi_y_per_met;
    uint32_t bi_clr_used;
    uint32_t bi_clr_important;
    uint32_t red_mask;
    uint32_t green_mask;
    uint32_t blue_mask;
} __attribute__((packed));
 
struct bmp_image
{
    struct bmp_file_hdr file_hdr;
    uint32_t *image_buffer;
};
 
uint32_t bmp_get_pixel(uint32_t x, uint32_t y, struct bmp_image *bmp_image)
{
    y = bmp_image->file_hdr.bi_height - 1 - y;
    return bmp_image->image_buffer[x + (y * bmp_image->file_hdr.bi_width)];
}
 
int load_bmp(char *path, struct bmp_image *bmp_image)
{
    FILE *fp = fopen(path, "r");
    if(fp == NULL) 
        return -1;
 
    fread(&bmp_image->file_hdr, sizeof(struct bmp_file_hdr), 1, fp);
    
    fseek(fp, bmp_image->file_hdr.bf_offset, SEEK_SET);
    bmp_image->image_buffer = malloc(bmp_image->file_hdr.bf_size);
    fread(bmp_image->image_buffer, bmp_image->file_hdr.bf_size, 1, fp);
 
    fclose(fp);
 
    return 0;
}
 
void draw_bmp(struct bmp_image *bmp_image)
{
    for(uint32_t i = 0; i < bmp_image->file_hdr.bi_height; i++)
    {
        for(uint32_t j = 0; j < bmp_image->file_hdr.bi_width; j++)
        {
            uint32_t pixel = bmp_get_pixel(j, i, bmp_image);
            pluto_set_cpix(j, i, pixel & 0xff, pixel >> 8 & 0xff, pixel >> 16 & 0xff);
        }
    }
    pluto_write_out();
    pluto_render();
}
 
int main(int argc, char *argv[])
{
    if(argc <= 1)
        return -1;
 
    pluto_init_window(true);

    struct bmp_image bmp_image;
    if(load_bmp(argv[1], &bmp_image) == 0)
        draw_bmp(&bmp_image);

    pluto_deinit();
 
    return 0;
}
