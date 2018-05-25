#ifndef GOL_RENDERER_H
#define GOL_RENDERER_H

#include "types/standard.h"
#include "types/renderer.h"

renderer_t* renderer_init();

u32 renderer_is_running(renderer_t* renderer);
void renderer_stop(renderer_t* renderer);

void renderer_render(renderer_t* renderer);
void renderer_shutdown(renderer_t* renderer);

#endif // GOL_RENDERER_H
