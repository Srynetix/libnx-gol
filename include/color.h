#ifndef GOL_COLOR_H
#define GOL_COLOR_H

#include "types/color.h"

/// Converts red, green, blue, and alpha components to packed RGBA8.
#define RGBA8(r,g,b,a)          (((r)&0xff)|(((g)&0xff)<<8)|(((b)&0xff)<<16)|(((a)&0xff)<<24))

/// Same as \ref RGBA8 except with alpha=0xff.
#define RGBA8_MAXALPHA(r,g,b)   RGBA8(r,g,b,0xff)

/**
 * Construct a color from R, G, B and A components.
 * 
 * @param r Red channel
 * @param g Green channel
 * @param b Blue channel
 * @param a Alpha channel
 * 
 * @returns Color
 */
color_t color_from_rgba(u8 r, u8 g, u8 b, u8 a);
/**
 * Construct a color from R, G and B components.
 * Alpha channel will be set to 255.
 * 
 * @param r Red channel
 * @param g Green channel
 * @param b Blue channel
 * @returns Color
 */
color_t color_from_rgb(u8 r, u8 g, u8 b);

/**
 * Add two colors.
 * 
 * @param a First color
 * @param b Second color
 * @returns Result color
 */
color_t color_add(color_t a, color_t b);
/**
 * Multiply a color with a scalar.
 * 
 * @param color     Color
 * @param scalar    Scalar
 * @returns Result color
 */
color_t color_fmul(color_t color, float scalar);
/**
 * Create a new color with a defined alpha.
 * 
 * @param color Color
 * @param alpha Alpha value
 * @returns Color with alpha
 */
color_t color_with_alpha(color_t color, u8 alpha);

/**
 * Darken a color by an amount.
 * 
 * @param color     Color
 * @param amount    Amount
 * @returns Darkened color
 */
color_t color_darken(color_t color, u8 amount);
/**
 * Premultiplicate alpha on a color.
 * 
 * @param color Color
 * @returns Result color
 */
color_t color_premultiplicate_alpha(color_t color);
/**
 * Mix two colors using alpha blending.
 * 
 * @param src_color Source color
 * @param dst_color Destination color
 * @returns Blended color
 */
color_t color_alpha_blend(color_t src_color, color_t dst_color);

/**
 * Darken a packed color.
 * 
 * @param packed    Packed color
 * @param amount    Amount
 * @return Darkened packed color
 */
u32 color_darken_packed(u32 packed, u8 amount);

/**
 * Pack a color.
 * 
 * @param color Color
 * @returns Packed color
 */
u32 color_pack(color_t color);
/**
 * Unpack a color.
 * 
 * @param packed    Packed color
 * @returns Color
 */
color_t color_unpack(u32 packed);

/**
 * Print a color to the standard console output, for debug.
 * 
 * @param prefix    String prefix
 * @param color     Color
 */
void color_debug_print(const char* prefix, color_t color);

#endif // GOL_COLOR_H
