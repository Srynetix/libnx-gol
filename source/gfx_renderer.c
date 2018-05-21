#ifdef SWITCH

#include <stdlib.h>

#include "renderer.h"

renderer_t* renderer_init() {
    renderer_t* renderer = (renderer_t*) malloc(sizeof(renderer_t));

    renderer->running = true;
    gfxInitDefault();

    renderer->framebuffer = (u32*) gfxGetFramebuffer((u32*)&renderer->width, (u32*)&renderer->height);

    return renderer;
}

u32 renderer_is_running(renderer_t* renderer) {
    return appletMainLoop() && renderer->running;
}

void renderer_stop(renderer_t* renderer) {
    renderer->running = false;
}

void renderer_render(renderer_t* renderer) {
    gfxFlushBuffers();
    gfxSwapBuffers();
    gfxWaitForVsync();
}

void renderer_shutdown(renderer_t* renderer) {
    free(renderer);
    
    gfxExit();
}

#endif
