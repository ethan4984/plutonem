/* BSD 3-Clause License

Copyright (c) 2021, Smart6502
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/

#ifndef PLUTO_LIB_H
#define PLUTO_LIB_H
#include <stdbool.h>
#include <stdint.h>

typedef unsigned char uchar;

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} pluto_colour_t;

typedef struct
{
    bool antialias;             /* If not 0, use anti-antialiasing */
    int height, width;          /* Height and width of the terminal in chars */
    int cheight, cwidth;        /* Height and width in pixels */
    int bufsize, bmsize;        /* Bitmap and buffer sizes */
    pluto_colour_t *pix_colour; /* 24-bit colour fg */
    uchar *bitmap;              /* Bitmap buffer */
    uchar *buffer;              /* UTF-8 output buffer */
    bool is_init;
} pluto_lib_t;

typedef struct
{
    int x, y;
} pt_t;
/* Origin: (0x, 0y) */

#ifndef PLUTO_PIX_CHAR_OFF
#    define PLUTO_PIX_CHAR_OFF /* Editor fix */
#endif

extern pluto_lib_t _pluto_canvas;
/* Instance */

extern void pluto_init_window(bool antialias);
/* Initialize library:
 * 	- bool antialias: use antialiased lines ?
 */

extern void pluto_render();
/* Write a frame to stdout */

extern void pluto_clear();
/* Clear both buffers and the screen */

extern void pluto_clear_buffers();
/* Clear both buffers only */

extern void pluto_deinit();
/* Free resources and restore states */

extern void pluto_set_pix_colour(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
/* Set a pixel's colour to a 24-bit value
 * The colours of the pixels in a block are averaged
 * 	- int x: x position from origin
 * 	- int y: y position from origin
 *  - uint8_t red: red value (0 - 255)
 *  - uint8_t green: green value (0 - 255)
 *  - uint8_t blue: blue value (0 - 255)
 */

extern void pluto_set_cpix(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
/* Set a pixel, and it's colour to a 24-bit value
 * A wrapper for pluto_set_pix and pluto_set_pix_colour
 * Parameters are same as those for pluto_set_pix_colour
 */

extern void pluto_set_pix(int x, int y);
/* Set a pixel in the bitmap buffer:
 * 	- int x: x position from origin
 * 	- int y: y position from origin
 */

extern void pluto_unset_pix(int x, int y);
/* Unset a pixel in the bitmap buffer:
 * 	- int x: x position from origin
 * 	- int y: y position from origin
 */

extern void pluto_write_out();
/* Write bitmap buffer to UTF-8 buffer */

extern void pluto_draw_line(pt_t p0, pt_t p1, pluto_colour_t colour);
/* Draw a line in the bitmap buffer from p0 to p1 */

extern void pluto_rast_bftri(pt_t p0, pt_t p1, pt_t p2, pluto_colour_t colour);
/* Rasterize a bottom-flat triangle:
 * 	- pt_t p0: highest point 
 * 	- pt_t p0: lower point 
 * 	- pt_t p0 lowest point
 */

extern void pluto_rast_tftri(pt_t p0, pt_t p1, pt_t p2, pluto_colour_t colour);
/* Rasterize a top-flat triangle:
 * 	- pt_t p0: highest point 
 * 	- pt_t p0: lower point 
 * 	- pt_t p0 lowest point
 */

extern void pluto_rast_tri(pt_t p0, pt_t p1, pt_t p2, pluto_colour_t colour);
/* Rasterize any triangle:
 * 	- pt_t p0: highest point 
 * 	- pt_t p0: lower point 
 * 	- pt_t p0 lowest point
 */

extern void pluto_draw_ellipse(pt_t p0, int a, int b, pluto_colour_t colour);
/* Draw an ellipse
 * 	- pt_t p0: centre
 * 	- int a: a offset
 * 	- int b: b offset
 */

#endif
