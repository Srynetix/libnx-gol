#ifndef GOL_FONT_H
#define GOL_FONT_H

#include "types.h"
#include "renderer.h"

// Fonts (5x6)

void font_render(const char* str, renderer_t* renderer, u32 font_size, u32 pos_x, u32 pos_y, u32 color);

#endif // GOL_FONT_H
