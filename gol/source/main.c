#include <stdlib.h>
#include <time.h>

#include <switch.h>

#include "gol.h"

#define TICKS_PER_FRAME		1
#define CELL_SIZE			2
#define INITIAL_CHANCE		50
#define ALIVE_COLOR			RGBA8_MAXALPHA(200, 100, 50)

int main(int argc, char **argv)
{
    srand(time(0));

    u32 *framebuf = NULL;
    u32 width, height;
    gol_t* game = NULL;

    gfxInitDefault();

    framebuf = (u32*) gfxGetFramebuffer((u32*)&width, (u32*)&height);

    // Initialize game
    game = gol_init((u32)(width / CELL_SIZE), (u32)(height / CELL_SIZE), CELL_SIZE, INITIAL_CHANCE, ALIVE_COLOR);

    while(appletMainLoop())
    {
        hidScanInput();

        u32 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS)
            break;

        // Step game
        for (u32 i = 0; i < TICKS_PER_FRAME; ++i) {
            gol_tick(game);
        }

        // Render game
        gol_render(game, framebuf, width);

        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();

        // Detect touch and paint screen where screen is touched.
        touchPosition touch;
        u32 touch_count = hidTouchCount();
        for (u32 i = 0; i < touch_count; ++i) {
            hidTouchRead(&touch, i);

            u32 cell_idx = gol_screenpos_to_cell(game, touch.px, touch.py);
            gol_make_cell_alive(game, cell_idx);
        }

        // Randomize screen when pressing A
        if (kDown & KEY_A)
            gol_randomize(game, INITIAL_CHANCE);

        // Pause game when pressing L
        if (kDown & KEY_L)
            gol_pause(game);

        // Resume game when pressing R
        if (kDown & KEY_R)
            gol_resume(game);
    }

    gol_shutdown(game);

    gfxExit();
    return 0;
}
