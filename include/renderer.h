#ifndef GOL_RENDERER_H
#define GOL_RENDERER_H

#include "types.h"

void renderer_init();

u32* renderer_get_framebuffer(u32* out_width, u32* out_height);
u32 renderer_is_running();
void renderer_stop();

void renderer_render();
void renderer_shutdown();

#endif // GOL_RENDERER_H
