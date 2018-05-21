#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gol.h"
#include "utils.h"
#include "color.h"

#define GOL_MAX_CHANCE	100
#define GOL_MAX_LIFE	200

void gol_swap_buffers(gol_t* game) {
    memcpy(game->front_buf, game->back_buf, game->grid_sz * sizeof(u8));
}

u32 gol_fn_is_alive(gol_t* game, u32 cell_idx) {
    u8 *buf = game->front_buf;
    u32 mod_idx = mod_u32(cell_idx, game->grid_sz);

    return buf[mod_idx] == GOL_CELL_ALIVE;
}

u32 gol_fn_get_status_color(gol_t* game, u8 status) {
    switch (status) {
        case GOL_CELL_ALIVE:
            return game->cell_alive_color;
        default:
            return game->cell_dead_color;
    }
}

u8 gol_fn_count_neighbors(gol_t* game, u32 cell_idx) {
    u8 count = 0;

    u32 width = game->grid_width;

    if (gol_fn_is_alive(game, cell_idx + 1)) count++;
    if (gol_fn_is_alive(game, cell_idx - 1)) count++;
    if (gol_fn_is_alive(game, cell_idx + width)) count++;
    if (gol_fn_is_alive(game, cell_idx - width)) count++;
    if (gol_fn_is_alive(game, cell_idx + 1 + width)) count++;
    if (gol_fn_is_alive(game, cell_idx + 1 - width)) count++;
    if (gol_fn_is_alive(game, cell_idx - 1 + width)) count++;
    if (gol_fn_is_alive(game, cell_idx - 1 - width)) count++;

    return count;
}

u32 gol_fn_screenpos_to_cell(gol_t* game, u32 pos_x, u32 pos_y) {
    u32 cell_x = clamp_u32((u32)(pos_x / game->cell_size), 0, game->grid_width);
    u32 cell_y = clamp_u32((u32)(pos_y / game->cell_size), 0, game->grid_height);

    return cell_x + cell_y * game->grid_width;
}

void gol_fn_render_cell(gol_t* game, u32 cell_idx, renderer_t* renderer) {
    u32* render_buf = renderer->framebuffer;
    u32 render_width = renderer->width;

    u32 cell_x = cell_idx % game->grid_width;
    u32 cell_y = (u32)(cell_idx / game->grid_width);
    u32 cursor = (cell_x * game->cell_size) + (cell_y * game->cell_size * render_width);

    u8 status = game->back_buf[cell_idx];
    u8 life = game->life_buf[cell_idx];
    u32 color = gol_fn_get_status_color(game, status);

    if (status == GOL_CELL_ALIVE) {
        color = color_darken_packed(color, life);
    }

    for (u32 l = 0; l < game->cell_size; ++l) {
        for (u32 m = 0; m < game->cell_size; ++m) {
            render_buf[cursor + l + (m * render_width)] = color;
        }
    }
}

void gol_fn_revive_cell(gol_t* game, u32 cell_idx) {
    game->back_buf[cell_idx] = GOL_CELL_ALIVE;
    game->life_buf[cell_idx] = 0;
}

void gol_revive_cells_at_position(gol_t* game, u32 pos_x, u32 pos_y, u32 diam_x, u32 diam_y) {
    u32 cell_idx = gol_fn_screenpos_to_cell(game, pos_x, pos_y);
    gol_fn_revive_cell(game, cell_idx);

    s32 radius_x = (s32)(diam_x / 2);
    s32 radius_y = (s32)(diam_y / 2);

    // Draw circle
    for (s32 y = -radius_y; y <= radius_y; ++y) {
        for (s32 x = -radius_x; x <= radius_x; ++x) {
            if (x * x + y * y <= radius_x * radius_y) {
                u32 curr_x = pos_x + x;
                u32 curr_y = pos_y + y;

                u32 curr_cell_idx = gol_fn_screenpos_to_cell(game, curr_x, curr_y);
                gol_fn_revive_cell(game, curr_cell_idx);
            }
        }
    }
}

void gol_pause(gol_t* game) {
    game->stopped = true;
}

void gol_resume(gol_t* game) {
    game->stopped = false;
}

gol_t* gol_init(u32 grid_width, u32 grid_height, u32 cell_size, u32 initial_chance, u32 alive_color) {
    gol_t* game = (gol_t*) malloc(sizeof(gol_t));
    u32 sz = grid_width * grid_height;

    game->grid_width = grid_width;
    game->grid_height = grid_height;
    game->grid_sz = grid_width * grid_height;

    game->cell_size = cell_size;
    game->cell_alive_color = alive_color;
    game->cell_dead_color = RGBA8_MAXALPHA(0, 0, 0);

    game->back_buf = (u8*) malloc(sizeof(u8) * sz);
    game->front_buf = (u8*) malloc(sizeof(u8) * sz);
    game->life_buf = (u8*) malloc(sizeof(u8) * sz);

    game->stopped = false;
    
    // Clear life buffer
    memset(game->life_buf, 0, sz * sizeof(u8));

    gol_randomize(game, initial_chance);
    gol_swap_buffers(game);

    return game;
}

void gol_randomize(gol_t* game, u8 chance) {
    for (u32 i = 0; i < game->grid_sz; ++i) {
        game->back_buf[i] = (rand() % GOL_MAX_CHANCE) < chance ? GOL_CELL_ALIVE : GOL_CELL_DEAD;
        game->life_buf[i] = 0;
    }
}

void gol_tick(gol_t* game) {
    if (game->stopped)
        return;

    for (u32 idx = 0; idx < game->grid_sz; ++idx) {
        u8 neighbors = gol_fn_count_neighbors(game, idx);
        u8 old_state = game->back_buf[idx];
        u8 new_state = old_state;

        if (neighbors == 3) {
            new_state = GOL_CELL_ALIVE;
        } else if (neighbors < 2 || neighbors > 3) {
            new_state = GOL_CELL_DEAD;
        }

        if (new_state != old_state) {
            game->back_buf[idx] = new_state;
            game->life_buf[idx] = 0;
        } else {
            u8 old_life = game->life_buf[idx];
            u8 new_life = old_life + 1 > GOL_MAX_LIFE ? GOL_MAX_LIFE : old_life + 1;
            game->life_buf[idx] = new_life;
        }
    }

    gol_swap_buffers(game);
}

void gol_render(gol_t* game, renderer_t* renderer) {
    for (u32 idx = 0; idx < game->grid_sz; ++idx) {
        gol_fn_render_cell(game, idx, renderer);
    }
}

void gol_shutdown(gol_t* game) {
    free(game->back_buf);
    free(game->front_buf);

    free(game);
}
