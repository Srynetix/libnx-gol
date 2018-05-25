#include <stdio.h>

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

color_t color_with_alpha(color_t color, u8 alpha) {
    return color_from_rgba(color.r, color.g, color.b, alpha);
}

color_t color_darken(color_t color, u8 amount) {
    color.r = checked_sub_u8(color.r, amount);
    color.g = checked_sub_u8(color.g, amount);
    color.b = checked_sub_u8(color.b, amount);

    return color;
}

color_t color_add(color_t a, color_t b) {
    return color_from_rgba(
        checked_add_u8(a.r, b.r),
        checked_add_u8(a.g, b.g),
        checked_add_u8(a.b, b.b),
        checked_add_u8(a.a, b.a)
    );
}

color_t color_fmul(color_t color, float scalar) {
    return color_from_rgba(
        checked_fmul_u8(color.r, scalar),
        checked_fmul_u8(color.g, scalar),
        checked_fmul_u8(color.b, scalar),
        checked_fmul_u8(color.a, scalar)
    );
}

u32 color_darken_packed(u32 packed, u8 amount) {
    color_t color = color_darken(
        color_unpack(packed), amount
    );

    return color_pack(color);
}

color_t color_premultiplicate_alpha(color_t color) {
    u8 a = color.a;
    return color_from_rgba(color.r * a / 255.f, color.g * a / 255.f, color.b * a / 255.f, a);
}

color_t color_alpha_blend(color_t src_color, color_t dst_color) {
    color_t ca = color_premultiplicate_alpha(src_color);
    color_t cb = color_premultiplicate_alpha(dst_color);

    u8 fa = src_color.a;
    u8 fb = dst_color.a;
    float fa_neg = 1 - (fa / 255.f);

    u8 fo = fa + fb * fa_neg;

    color_t co = color_add(ca, color_fmul(cb, fa_neg));

    // Set output alpha
    co.a = fo;

    return co;
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

void color_debug_print(const char* prefix, color_t color) {
    printf("%s: %d/%d/%d/%d\n", prefix, color.r, color.g, color.b, color.a);
}
