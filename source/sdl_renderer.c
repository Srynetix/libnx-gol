#ifndef SWITCH

#include <SDL2/SDL.h>

#include "renderer.h"

static SDL_Window* g_window;
static SDL_Renderer* g_renderer;
static SDL_Texture* g_texture;

renderer_t* renderer_init() {
    renderer_t* renderer = (renderer_t*) malloc(sizeof(renderer_t));

    renderer->running = true;
    renderer->width = 1280;
    renderer->height = 720;

    SDL_Init(SDL_INIT_EVERYTHING);
    g_window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, renderer->width, renderer->height, SDL_WINDOW_SHOWN);
    g_renderer = SDL_CreateRenderer(g_window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    g_texture = SDL_CreateTexture(g_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, renderer->width, renderer->height);

    renderer->framebuffer = (u32*) malloc(renderer->width * renderer->height * sizeof(u32));

    SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);

    return renderer;
}

u32 renderer_is_running(renderer_t* renderer) {
#ifdef SWITCH
    return appletMainLoop() && renderer->running;
#else
    return renderer->running;
#endif
}

void renderer_stop(renderer_t* renderer) {
    renderer->running = false;
}

void renderer_render(renderer_t* renderer) {
    SDL_RenderClear(g_renderer);
    SDL_UpdateTexture(g_texture, NULL, renderer->framebuffer, renderer->width * 4);
    SDL_RenderCopy(g_renderer, g_texture, NULL, NULL);
    SDL_RenderPresent(g_renderer);
}

void renderer_shutdown(renderer_t* renderer) {
    free(renderer->framebuffer);
    free(renderer);

    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);

    SDL_Quit();
}

#endif
