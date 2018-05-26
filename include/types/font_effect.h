#ifndef GOL_TYPES_FONTEFFECT_H
#define GOL_TYPES_FONTEFFECT_H

#include "types/standard.h"

/**
 * Font effect types.
 */
typedef enum font_effect_type_e {
    /// Fade-in effect
    FONT_EFFECT_FADE_IN,

    /// Fade-out effect
    FONT_EFFECT_FADE_OUT,

    /// Fade-in-out effect
    FONT_EFFECT_FADE_IN_OUT
} font_effect_type_e;

/**
 * Font effect.
 */
typedef struct font_effect_t {
    /// Initial time
    u32 base_time;
    /// End time
    u32 end_time;
    /// Current time
    u32 current_time;

    /// Base delay for delayed start
    u32 base_delay;
    /// Current delay for delayed start
    u32 current_delay;

    /// Effect type
    font_effect_type_e type;

    /// Is the effect finished?
    bool finished;
} font_effect_t;

#endif // GOL_TYPES_FONTEFFECT_H
