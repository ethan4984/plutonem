// program.c
#include "../src/pluto.h"
// If you have installed the library, you can do #include <pluto.h>

int main()
{
    pluto_init_window(true);                                                        // Initializes pluto w/ anti-aliasing
    pluto_draw_line((pt_t){5, 25}, (pt_t){70, 65}, (pluto_colour_t){94, 129, 172}); // Draws a line from (5x, 10y) to (20x, 25y)
    pluto_write_out();                                                              // Writes bitmap to UTF-8 buffer
    pluto_render();                                                                 // Writes the UTF-8 buffer to STDOUT
    pluto_deinit();                                                                 // De-initializes pluto

    return 0;
}
