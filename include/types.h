#ifndef GOL_TYPES_H
#define GOL_TYPES_H

#ifdef SWITCH
    #include <switch.h>
#else
    #include <stddef.h>
    #include <stdbool.h>
    #include <stdint.h>

    typedef uint8_t u8;       ///<   8-bit unsigned integer.
    typedef uint16_t u16;     ///<  16-bit unsigned integer.
    typedef uint32_t u32;     ///<  32-bit unsigned integer.
    typedef uint64_t u64;     ///<  64-bit unsigned integer.
    typedef __uint128_t u128; ///< 128-bit unsigned integer.

    typedef int8_t s8;       ///<   8-bit signed integer.
    typedef int16_t s16;     ///<  16-bit signed integer.
    typedef int32_t s32;     ///<  32-bit signed integer.
    typedef int64_t s64;     ///<  64-bit signed integer.
    typedef __int128_t s128; ///< 128-bit unsigned integer.

    typedef volatile u8 vu8;     ///<   8-bit volatile unsigned integer.
    typedef volatile u16 vu16;   ///<  16-bit volatile unsigned integer.
    typedef volatile u32 vu32;   ///<  32-bit volatile unsigned integer.
    typedef volatile u64 vu64;   ///<  64-bit volatile unsigned integer.
    typedef volatile u128 vu128; ///< 128-bit volatile unsigned integer.

    typedef volatile s8 vs8;     ///<   8-bit volatile signed integer.
    typedef volatile s16 vs16;   ///<  16-bit volatile signed integer.
    typedef volatile s32 vs32;   ///<  32-bit volatile signed integer.
    typedef volatile s64 vs64;   ///<  64-bit volatile signed integer.
    typedef volatile s128 vs128; ///< 128-bit volatile signed integer.

    /// Converts red, green, blue, and alpha components to packed RGBA8.
    #define RGBA8(r,g,b,a)          (((r)&0xff)|(((g)&0xff)<<8)|(((b)&0xff)<<16)|(((a)&0xff)<<24))

    /// Same as \ref RGBA8 except with alpha=0xff.
    #define RGBA8_MAXALPHA(r,g,b)   RGBA8(r,g,b,0xff)
#endif // SWITCH

#include <SDL2/SDL.h>

#endif // GOL_TYPES_H
