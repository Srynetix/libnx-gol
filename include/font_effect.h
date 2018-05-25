#ifndef GOL_FONTEFFECT_H
#define GOL_FONTEFFECT_H

#include "types/standard.h"
#include "types/font.h"
#include "types/font_effect.h"
#include "types/renderer.h"
#include "types/color.h"

font_effect_t* font_effect_create(font_effect_type_e type, u32 base_time, u32 end_time);
void font_effect_reset(font_effect_t* effect);
void font_effect_redefine(font_effect_t* effect, u32 base_time, u32 end_time);
void font_effect_destroy(font_effect_t* effect);
void font_effect_tick(font_effect_t* effect, u32 tick);
bool font_effect_is_finished(font_effect_t* effect);

u32 font_effect_get_elapsed_time(font_effect_t* effect);
u32 font_effect_get_remaining_time(font_effect_t* effect);
u32 font_effect_get_duration(font_effect_t* effect);

void font_render_effect(const char* str, renderer_t* renderer, u32 font_size, u32 pos_x, u32 pos_y, color_t color, font_effect_t* effect);

#endif // GOL_FONTEFFECT_H
