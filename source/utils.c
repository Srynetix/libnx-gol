#include "utils.h"

u32 mod_u32(u32 a, u32 b) {
    return (a % b + b) % b;
}

u32 min_u32(u32 a, u32 b) {
    return a < b ? a : b;
}

u32 max_u32(u32 a, u32 b) {
    return a > b ? a : b;
}

u32 clamp_u32(u32 value, u32 min, u32 max) {
    return min_u32(max_u32(value, min), max);
}

u8 checked_sub_u8(u8 a, u8 amount) {
    return amount > a ? 0 : a - amount;
}
