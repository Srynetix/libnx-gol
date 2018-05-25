#ifndef GOL_TYPES_FONTEFFECT_H
#define GOL_TYPES_FONTEFFECT_H

#include "types/standard.h"

typedef enum font_effect_type_e {
    FONT_EFFECT_FADE_IN,
    FONT_EFFECT_FADE_OUT,
    FONT_EFFECT_FADE_IN_OUT
} font_effect_type_e;

typedef struct font_effect_t {
    u32 base_time;
    u32 end_time;
    u32 current_time;

    u32 base_delay;
    u32 current_delay;

    font_effect_type_e type;

    bool finished;
} font_effect_t;

#endif // GOL_TYPES_FONTEFFECT_H
