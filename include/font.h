#ifndef GOL_FONT_H
#define GOL_FONT_H

#include "types/standard.h"
#include "types/renderer.h"
#include "types/color.h"
#include "types/font.h"

/**
 * Render text using font.
 * 
 * @param str       String to render
 * @param renderer  Renderer
 * @param font_size Font size scale
 * @param pos_x     X position
 * @param pos_y     Y position
 * @param color     Font color
 */
void font_render(const char* str, renderer_t* renderer, u32 font_size, u32 pos_x, u32 pos_y, color_t color);

/**
 * Render a character.
 * 
 * @param c         Character
 * @param renderer  Renderer
 * @param font_size Font size scale
 * @param pos_x     X position
 * @param pos_y     Y position
 * @param color     Font color
 */
void font_render_char(char c, renderer_t* renderer, u32 font_size, u32 pos_x, u32 pos_y, color_t color);

#endif // GOL_FONT_H
