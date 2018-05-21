#ifndef GOL_COLOR_H
#define GOL_COLOR_H

/// Converts red, green, blue, and alpha components to packed RGBA8.
#define RGBA8(r,g,b,a)          (((r)&0xff)|(((g)&0xff)<<8)|(((b)&0xff)<<16)|(((a)&0xff)<<24))

/// Same as \ref RGBA8 except with alpha=0xff.
#define RGBA8_MAXALPHA(r,g,b)   RGBA8(r,g,b,0xff)

#include "types.h"

typedef struct color_t {
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} color_t;

color_t color_from_rgba(u8 r, u8 g, u8 b, u8 a);
color_t color_from_rgb(u8 r, u8 g, u8 b);

color_t color_darken(color_t color, u8 amount);
u32 color_darken_packed(u32 packed, u8 amount);

u32 color_pack(color_t color);
color_t color_unpack(u32 packed);

#endif // GOL_COLOR_H
