#ifndef SWITCH

#include <SDL2/SDL.h>

#include "renderer.h"

static u32 g_renderer_width;
static u32 g_renderer_height;

static u32* g_framebuffer;
static bool g_running;

static SDL_Window* g_window;
static SDL_Renderer* g_renderer;
static SDL_Texture* g_texture;

void renderer_init() {
    g_running = true;

    g_renderer_width = 1280;
    g_renderer_height = 720;

    SDL_Init(SDL_INIT_EVERYTHING);
    g_window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, g_renderer_width, g_renderer_height, SDL_WINDOW_SHOWN);
    g_renderer = SDL_CreateRenderer(g_window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    g_texture = SDL_CreateTexture(g_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, g_renderer_width, g_renderer_height);

    g_framebuffer = (u32*) malloc(g_renderer_width * g_renderer_height * sizeof(u32));

    SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
}

u32* renderer_get_framebuffer(u32* out_width, u32* out_height) {
    if (out_width) *out_width = g_renderer_width;
    if (out_height) *out_height = g_renderer_height;

    return g_framebuffer;
}

u32 renderer_is_running() {
#ifdef SWITCH
    return appletMainLoop() && g_running;
#else
    return g_running;
#endif
}

void renderer_stop() {
    g_running = false;
}

void renderer_render() {
    SDL_RenderClear(g_renderer);
    SDL_UpdateTexture(g_texture, NULL, g_framebuffer, g_renderer_width * 4);
    SDL_RenderCopy(g_renderer, g_texture, NULL, NULL);
    SDL_RenderPresent(g_renderer);
}

void renderer_shutdown() {
    free(g_framebuffer);

    SDL_DestroyRenderer(g_renderer);
    SDL_DestroyWindow(g_window);

    SDL_Quit();
}

#endif
