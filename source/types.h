#ifndef GOL_TYPES_H
#define GOL_TYPES_H

#define BOOL    unsigned char
#define TRUE    1
#define FALSE   0

#ifdef SWITCH
    #include <switch.h>
#else
    typedef unsigned int    u32;
    typedef int             s32;
    typedef unsigned char   u8;

    /// Converts red, green, blue, and alpha components to packed RGBA8.
    #define RGBA8(r,g,b,a)          (((r)&0xff)|(((g)&0xff)<<8)|(((b)&0xff)<<16)|(((a)&0xff)<<24))

    /// Same as \ref RGBA8 except with alpha=0xff.
    #define RGBA8_MAXALPHA(r,g,b)   RGBA8(r,g,b,0xff)
#endif // SWITCH

#include <SDL2/SDL.h>

#endif // GOL_TYPES_H
