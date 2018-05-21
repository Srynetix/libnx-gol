#ifndef GOL_RENDERER_H
#define GOL_RENDERER_H

#include "types.h"

typedef struct renderer_t {
    u32* framebuffer;

    u32 width;
    u32 height;

    bool running;
} renderer_t;

renderer_t* renderer_init();

u32 renderer_is_running(renderer_t* renderer);
void renderer_stop(renderer_t* renderer);

void renderer_render(renderer_t* renderer);
void renderer_shutdown(renderer_t* renderer);

#endif // GOL_RENDERER_H
