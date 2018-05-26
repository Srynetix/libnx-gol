#ifndef GOL_UTILS_H
#define GOL_UTILS_H

#include "types/standard.h"

/**
 * Modulo on unsigned 32-bit values.
 * 
 * @param a First value
 * @param b Second value
 * @returns Modulo
 */
u32 mod_u32(u32 a, u32 b);
/**
 * Get min on unsigned 32-bit values.
 * 
 * @param a First value
 * @param b Second value
 * @param Min value
 */
u32 min_u32(u32 a, u32 b);
/**
 * Get max on unsigned 32-bit values.
 * 
 * @param a First value
 * @param b Second value
 * @returns Max value
 */
u32 max_u32(u32 a, u32 b);
/**
 * Clamp an unsigned 32-bit value between a min and max value.
 * 
 * @param value Value
 * @param min   Min value
 * @param max   Max value
 * @returns Clamped value
 */
u32 clamp_u32(u32 value, u32 min, u32 max);

/**
 * Get min on unsigned 8-bit values.
 * 
 * @param a First value
 * @param b Second value
 * @returns Min value
 */
u8 min_u8(u8 a, u8 b);
/**
 * Get max on unsigned 8-bit values.
 * 
 * @param a First value
 * @param b Second value
 * @returns Max value
 */
u8 max_u8(u8 a, u8 b);
/**
 * Clamp an unsigned 8-bit value between a min and max value.
 * 
 * @param value Value
 * @param min   Min value
 * @param max   Max value
 * @returns Clamped value
 */
u8 clamp_u8(u8 value, u8 min, u8 max);

/**
 * Subtract an amount from a value.
 * Result will be clamped to 0.
 * 
 * @param a         Value
 * @param amount    Amount
 * @returns Result value
 */
u8 checked_sub_u8(u8 a, u8 amount);
/**
 * Add an amount to a value.
 * Result will be clamped to 255.
 * 
 * @param a         Value
 * @param amount    Amount
 * @returns Result value
 */
u8 checked_add_u8(u8 a, u8 amount);
/**
 * Multiply a value with a scalar.
 * Result will be clamped to 255.
 * 
 * @param a         Value
 * @param scalar    Scalar
 * @returns Result value
 */
u8 checked_fmul_u8(u8 a, float scalar);

#endif // GOL_UTILS_H
