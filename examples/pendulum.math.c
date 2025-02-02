#include "../src/pluto.h"
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    pluto_init_window(true);

    for (int y = 0; y < _pluto_canvas.cheight / 2; y++)
    {
        int xb = (int)(4 * M_PI * M_PI * y / 9.8);
        pluto_draw_line((pt_t){xb, _pluto_canvas.cheight - 1}, (pt_t){xb, _pluto_canvas.cheight - 1 - y}, (pluto_colour_t){94, 129, 172 + xb / 5});

        pluto_write_out();
        pluto_render();
        usleep(45000);
    }

    pluto_deinit();
}
