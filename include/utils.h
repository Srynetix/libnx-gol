#ifndef GOL_UTILS_H
#define GOL_UTILS_H

#include "types.h"

u32 mod_u32(u32 a, u32 b);
u32 min_u32(u32 a, u32 b);
u32 max_u32(u32 a, u32 b);
u32 clamp_u32(u32 value, u32 min, u32 max);

u8 checked_sub_u8(u8 a, u8 amount);

#endif // GOL_UTILS_H
