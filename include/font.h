#ifndef GOL_FONT_H
#define GOL_FONT_H

#include "types/standard.h"
#include "types/renderer.h"
#include "types/color.h"
#include "types/font.h"

void font_render(const char* str, renderer_t* renderer, u32 font_size, u32 pos_x, u32 pos_y, color_t color);
void font_render_char(char c, renderer_t* renderer, u32 font_size, u32 pos_x, u32 pos_y, color_t color);

#endif // GOL_FONT_H
