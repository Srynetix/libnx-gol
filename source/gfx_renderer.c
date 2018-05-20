#ifdef SWITCH

#include "renderer.h"

u32 renderer_width;
u32 renderer_height;

u32* g_framebuffer;
BOOL g_running;

void renderer_init() {
    g_running = TRUE;

    renderer_width = 1280;
    renderer_height = 720;

    gfxInitDefault();

    g_framebuffer = (u32*) gfxGetFramebuffer((u32*)&renderer_width, (u32*)&renderer_height);
}

u32* renderer_get_framebuffer(u32* out_width, u32* out_height) {
    if (out_width) *out_width = renderer_width;
    if (out_height) *out_height = renderer_height;

    return g_framebuffer;
}

u32 renderer_is_running() {
    return appletMainLoop() && g_running;
}

void renderer_stop() {
    g_running = FALSE;
}

void renderer_render() {
    gfxFlushBuffers();
    gfxSwapBuffers();
    gfxWaitForVsync();
}

void renderer_shutdown() {
    gfxExit();
}

#endif
