#ifndef GOL_TYPES_RENDERER_H
#define GOL_TYPES_RENDERER_H

#include "types/standard.h"

/**
 * Renderer
 */
typedef struct renderer_t {
    /// Framebuffer
    u32* framebuffer;

    /// Renderer width
    u32 width;
    /// Renderer height
    u32 height;

    /// Is the renderer running?
    bool running;
} renderer_t;

#endif // GOL_TYPES_RENDERER_H
