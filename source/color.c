#include "color.h"

#include "utils.h"

color_t color_from_rgba(u8 r, u8 g, u8 b, u8 a) {
    color_t color = {
        .r = r,
        .g = g,
        .b = b,
        .a = a
    };

    return color;
}

color_t color_from_rgb(u8 r, u8 g, u8 b) {
    return color_from_rgba(r, g, b, 255);
}

color_t color_darken(color_t color, u8 amount) {
    color.r = checked_sub_u8(color.r, amount);
    color.g = checked_sub_u8(color.g, amount);
    color.b = checked_sub_u8(color.b, amount);

    return color;
}

u32 color_darken_packed(u32 packed, u8 amount) {
    color_t color = color_darken(
        color_unpack(packed), amount
    );

    return color_pack(color);
}

u32 color_pack(color_t color) {
    return RGBA8(color.r, color.g, color.b, color.a);
}

color_t color_unpack(u32 packed) {
    u8 r = (packed & 0x000000ff);
    u8 g = (packed & 0x0000ff00) >> 8;
    u8 b = (packed & 0x00ff0000) >> 16;
    u8 a = (packed & 0xff000000) >> 24;

    return color_from_rgba(r, g, b, a);
}
