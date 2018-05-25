#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "font_effect.h"
#include "font.h"
#include "utils.h"

font_effect_t* font_effect_create(font_effect_type_e type, u32 base_time, u32 end_time) {
    font_effect_t* effect = (font_effect_t*) malloc(sizeof(font_effect_t));

    effect->base_time = base_time;
    effect->end_time = end_time;
    effect->current_time = base_time;

    effect->base_delay = 0;
    effect->current_delay = 0;

    effect->type = type;
    effect->finished = false;

    return effect;
}

void font_effect_reset(font_effect_t* effect) {
    effect->current_time = effect->base_time;
    effect->finished = false;
}

void font_effect_redefine(font_effect_t* effect, u32 base_time, u32 end_time) {
    effect->base_time = base_time;
    effect->end_time = end_time;
    effect->current_time = base_time;
    effect->finished = false;
}

void font_effect_destroy(font_effect_t* effect) {
    free(effect);
}

void font_effect_tick(font_effect_t* effect, u32 tick) {
    effect->current_time = clamp_u32(
        effect->current_time + tick,
        effect->base_time,
        effect->end_time
    );

    if (effect->current_time == effect->end_time) {
        effect->finished = true;
    }
}

bool font_effect_is_finished(font_effect_t* effect) {
    return effect->finished;
}

u32 font_effect_get_elapsed_time(font_effect_t* effect) {
    return effect->current_time - effect->base_time;
}

u32 font_effect_get_remaining_time(font_effect_t* effect) {
    return effect->end_time - effect->current_time;
}

u32 font_effect_get_duration(font_effect_t* effect) {
    return effect->end_time - effect->base_time;
}

void font_render_effect(const char* str, renderer_t* renderer, u32 font_size, u32 pos_x, u32 pos_y, color_t color, font_effect_t* effect) {
    // Calculate opacity value
    u32 duration = font_effect_get_duration(effect);
    u32 elapsed_time = font_effect_get_elapsed_time(effect);

    float ratio = elapsed_time / (float)duration;
    u8 current_alpha = 0;

    if (effect->type == FONT_EFFECT_FADE_IN) {
        current_alpha = 255 * ratio;
    } else if (effect->type == FONT_EFFECT_FADE_OUT) {
        current_alpha = 255 - 255 * ratio;
    } else if (effect->type == FONT_EFFECT_FADE_IN_OUT) {
        if (ratio < 0.5f) {
            current_alpha = 255 * (2 * ratio);
        } else {
            current_alpha = 255 - 255 * 2 * (ratio - 0.5);
        }
    }

    color.a = current_alpha;

    u32 str_len = strlen(str);

    for (u32 c = 0; c < str_len; ++c) {
        u32 curr_x = pos_x + (c * ((FONT_WIDTH * font_size) + (1 * font_size))); 
        font_render_char(str[c], renderer, font_size, curr_x, pos_y, color);
    }
}
