#ifndef GOL_TYPES_RENDERER_H
#define GOL_TYPES_RENDERER_H

#include "types/standard.h"

typedef struct renderer_t {
    u32* framebuffer;

    u32 width;
    u32 height;

    bool running;
} renderer_t;

#endif // GOL_TYPES_RENDERER_H
