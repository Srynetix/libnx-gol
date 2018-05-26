#ifndef GOL_TYPES_COLOR_H
#define GOL_TYPES_COLOR_H

#include "types/standard.h"

/**
 * Simple RGBA color type.
 */
typedef struct color_t {
    /// Red channel
    u8 r;
    
    /// Green channel
    u8 g;
    
    /// Blue channel
    u8 b;
    
    /// Alpha channel
    u8 a;
} color_t;

#endif // GOL_TYPES_COLOR_H
