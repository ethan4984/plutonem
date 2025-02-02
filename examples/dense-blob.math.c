#include "../src/pluto.h"
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const float density = 1.3; // Pixel density (low => high density, high => low density)

int main()
{
    pluto_init_window(true);

    float x, y;
    for (x = 1; x < _pluto_canvas.cwidth / 3; x += density)
    {
        for (y = 1; y < _pluto_canvas.cheight; y += density)
        {
            float r = x / y;
            float m = powf(r, 1 / r);
            int xp = m * x, yp = _pluto_canvas.cheight - 1 - (m * y);

            pluto_set_cpix(xp, yp, 94, 129, 172 * yp / (xp + 1));
        }

        pluto_write_out();
        pluto_render();
        usleep(50000);
    }

    pluto_deinit();
}
