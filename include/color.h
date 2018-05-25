#ifndef GOL_COLOR_H
#define GOL_COLOR_H

#include "types/color.h"

/// Converts red, green, blue, and alpha components to packed RGBA8.
#define RGBA8(r,g,b,a)          (((r)&0xff)|(((g)&0xff)<<8)|(((b)&0xff)<<16)|(((a)&0xff)<<24))

/// Same as \ref RGBA8 except with alpha=0xff.
#define RGBA8_MAXALPHA(r,g,b)   RGBA8(r,g,b,0xff)

color_t color_from_rgba(u8 r, u8 g, u8 b, u8 a);
color_t color_from_rgb(u8 r, u8 g, u8 b);

color_t color_add(color_t a, color_t b);
color_t color_fmul(color_t color, float scalar);
color_t color_with_alpha(color_t color, u8 alpha);

color_t color_darken(color_t color, u8 amount);
color_t color_premultiplicate_alpha(color_t color);
color_t color_alpha_blend(color_t src_color, color_t dst_color);

u32 color_darken_packed(u32 packed, u8 amount);

u32 color_pack(color_t color);
color_t color_unpack(u32 packed);

void color_debug_print(const char* prefix, color_t color);

#endif // GOL_COLOR_H
