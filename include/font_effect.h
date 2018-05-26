#ifndef GOL_FONTEFFECT_H
#define GOL_FONTEFFECT_H

#include "types/standard.h"
#include "types/font.h"
#include "types/font_effect.h"
#include "types/renderer.h"
#include "types/color.h"

/**
 * Create a new font effect.
 * 
 * @param type      Font effect type
 * @param base_time Base time
 * @param end_time  End time
 */
font_effect_t* font_effect_create(font_effect_type_e type, u32 base_time, u32 end_time);
/**
 * Reset a font effect time.
 * 
 * @param effect    Effect
 */
void font_effect_reset(font_effect_t* effect);
/**
 * Redefine a font effect with a new time.
 * 
 * @param effect    Effect
 * @param base_time Base time
 * @param end_time  End time
 */
void font_effect_redefine(font_effect_t* effect, u32 base_time, u32 end_time);
/**
 * Destroy a font effect.
 * 
 * @param effect    Effect
 */
void font_effect_destroy(font_effect_t* effect);
/**
 * Tick a font effect.
 * 
 * @param effect    Effect
 * @param tick      Tick value
 */
void font_effect_tick(font_effect_t* effect, u32 tick);

/**
 * Check if a font effect is finished.
 * 
 * @param effect    Effect
 * @returns Finished?
 */
bool font_effect_is_finished(font_effect_t* effect);
/**
 * Get a font effect elapsed time.
 * 
 * @param effect    Effect
 * @returns Elapsed time
 */
u32 font_effect_get_elapsed_time(font_effect_t* effect);
/**
 * Get a font effect remaining time.
 * 
 * @param effect    Effect
 * @returns Remaining time
 */
u32 font_effect_get_remaining_time(font_effect_t* effect);
/**
 * Get a font effect duration.
 * 
 * @param effect    Effect
 * @returns Duration
 */
u32 font_effect_get_duration(font_effect_t* effect);

/**
 * Render text using a font effect.
 * 
 * @param str       String to render
 * @param renderer  Renderer
 * @param font_size Font size scale
 * @param pos_x     X position
 * @param pos_y     Y position
 * @param color     Font color
 * @param effect    Font effect
 */
void font_render_effect(const char* str, renderer_t* renderer, u32 font_size, u32 pos_x, u32 pos_y, color_t color, font_effect_t* effect);

#endif // GOL_FONTEFFECT_H
