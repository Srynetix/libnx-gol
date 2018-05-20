#include <stdlib.h>
#include <time.h>

#include "gol.h"
#include "renderer.h"

#define TICKS_PER_FRAME		1
#define CELL_SIZE			2
#define INITIAL_CHANCE		50
#define ALIVE_COLOR			RGBA8_MAXALPHA(200, 100, 50)

int main(int argc, char **argv)
{
    srand(time(0));

    u32* framebuf;
    u32 width, height;
    gol_t* game = NULL;

#ifndef SWITCH
    BOOL clicked = FALSE;
#endif

    // Initialize renderer
    renderer_init();

    // Get framebuffer
    framebuf = renderer_get_framebuffer(&width, &height);

    // Initialize game
    game = gol_init((u32)(width / CELL_SIZE), (u32)(height / CELL_SIZE), CELL_SIZE, INITIAL_CHANCE, ALIVE_COLOR);

    while (renderer_is_running()) {
#ifdef SWITCH
        hidScanInput();

        u32 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
        if (kDown & KEY_PLUS)
            break;
#else
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)) {
                renderer_stop();
            }
        }
#endif

        // Step game
        for (u32 i = 0; i < TICKS_PER_FRAME; ++i) {
            gol_tick(game);
        }

        // Render game
        gol_render(game, framebuf, width);

        // Render
        renderer_render();

#ifdef SWITCH
        // Detect touch and paint screen where screen is touched.
        touchPosition touch;
        u32 touch_count = hidTouchCount();
        for (u32 i = 0; i < touch_count; ++i) {
            hidTouchRead(&touch, i);
            gol_revive_cells_at_position(game, touch.px, touch.py, touch.dx, touch.dy);
        }

        // Randomize screen when pressing A
        if (kDown & KEY_A) {
            gol_randomize(game, INITIAL_CHANCE);
            gol_swap_buffers(game);
        }

        // Clear screen when pressing X
        if (kDown & KEY_X) {
            gol_randomize(game, 0);
            gol_swap_buffers(game);            
        }

        // Pause game when pressing L
        if (kDown & KEY_L)
            gol_pause(game);

        // Resume game when pressing R
        if (kDown & KEY_R)
            gol_resume(game);
#else
        // Detect touch
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                clicked = TRUE;
            }
        }

        else if (event.type == SDL_MOUSEBUTTONUP) {
            if (event.button.button == SDL_BUTTON_LEFT) {
                clicked = FALSE;
            }
        }

        else if (event.type == SDL_MOUSEMOTION) {
            if (clicked == TRUE) {
                gol_revive_cells_at_position(game, event.motion.x, event.motion.y, 30, 30);
            }
        }

        else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.scancode == SDL_SCANCODE_A) {
                gol_randomize(game, INITIAL_CHANCE);
            }

            if (event.key.keysym.scancode == SDL_SCANCODE_L) {
                gol_pause(game);
            }

            if (event.key.keysym.scancode == SDL_SCANCODE_R) {
                gol_resume(game);
            }
        }
#endif
    }

    gol_shutdown(game);

    renderer_shutdown();

    return 0;
}
