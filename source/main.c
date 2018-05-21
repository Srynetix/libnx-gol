#include <stdlib.h>
#include <time.h>

#include "gol.h"
#include "renderer.h"
#include "color.h"

#ifndef SWITCH
#include <SDL2/SDL.h>
#endif

#define INITIAL_TICKS_PER_FRAME 1
#define CELL_SIZE			    2
#define INITIAL_CHANCE		    50
#define ALIVE_COLOR			    RGBA8_MAXALPHA(200, 50, 150)
#define SIMULATED_TOUCH_RADIUS  20

int main(int argc, char **argv)
{
    srand(time(0));

    u32* framebuf;
    u32 width, height;
    u32 ticks_per_frame = INITIAL_TICKS_PER_FRAME;
    gol_t* game = NULL;

#ifndef SWITCH
    bool clicked = false;
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
        u32 kUp = hidKeysUp(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS)
            break;

        // Detect touch and paint screen where screen is touched.
        touchPosition touch;
        u32 touch_count = hidTouchCount();
        bool touched = false;
        for (u32 i = 0; i < touch_count; ++i) {
            hidTouchRead(&touch, i);
            gol_revive_cells_at_position(game, touch.px, touch.py, touch.dx, touch.dy);
            touched = true;
        }
        if (touched) {
            gol_swap_buffers(game);
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

        // Speed up when pressing Y
        if (kDown & KEY_Y) {
            ticks_per_frame = INITIAL_TICKS_PER_FRAME * 5;
        }
        if (kUp & KEY_Y) {
            ticks_per_frame = INITIAL_TICKS_PER_FRAME;
        }

        // Pause game when pressing L
        if (kDown & KEY_L)
            gol_pause(game);

        // Resume game when pressing R
        if (kDown & KEY_R)
            gol_resume(game);
#else
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)) {
                renderer_stop();
            }

            // Detect touch
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    clicked = true;
                }
            }

            else if (event.type == SDL_MOUSEBUTTONUP) {
                if (event.button.button == SDL_BUTTON_LEFT) {
                    clicked = false;
                }
            }

            else if (event.type == SDL_MOUSEMOTION) {
                if (clicked == true) {
                    gol_revive_cells_at_position(game, event.motion.x, event.motion.y, SIMULATED_TOUCH_RADIUS, SIMULATED_TOUCH_RADIUS);
                    gol_swap_buffers(game);
                }
            }

            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.scancode == SDL_SCANCODE_A) {
                    gol_randomize(game, INITIAL_CHANCE);
                    gol_swap_buffers(game);                    
                }

                else if (event.key.keysym.scancode == SDL_SCANCODE_L) {
                    gol_pause(game);
                }

                else if (event.key.keysym.scancode == SDL_SCANCODE_R) {
                    gol_resume(game);
                }

                else if (event.key.keysym.scancode == SDL_SCANCODE_X) {
                    gol_randomize(game, 0);
                    gol_swap_buffers(game);
                }

                else if (event.key.keysym.scancode == SDL_SCANCODE_Y) {
                    ticks_per_frame = INITIAL_TICKS_PER_FRAME * 5;
                }
            }

            else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.scancode == SDL_SCANCODE_Y) {
                    ticks_per_frame = INITIAL_TICKS_PER_FRAME;
                }
            }
        }
#endif

        // Step game
        for (u32 i = 0; i < ticks_per_frame; ++i) {
            gol_tick(game);
        }

        // Render game
        gol_render(game, framebuf, width);

        // Render
        renderer_render();
    }

    gol_shutdown(game);

    renderer_shutdown();

    return 0;
}
