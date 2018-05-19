#ifndef GOL_H
#define GOL_H

#include <switch.h>

#define GOL_CELL_DEAD	0
#define GOL_CELL_ALIVE	1

typedef struct gol_t {
    u8* back_buf;
    u8* front_buf;
    u8* life_buf;

    u32 grid_width;
    u32 grid_height;
    u32 grid_sz;

    u32 cell_size;
    u32 cell_alive_color;
    u32 cell_dead_color;

    bool stopped;
} gol_t;


gol_t* gol_init(u32 grid_width, u32 grid_height, u32 cell_size, u32 initial_chance, u32 alive_color);
void gol_shutdown(gol_t* game);
void gol_randomize(gol_t* game, u8 chance);

void gol_make_cell_alive(gol_t* game, u32 cell_idx);
u32 gol_screenpos_to_cell(gol_t* game, u32 pos_x, u32 pos_y);

void gol_pause(gol_t* game);
void gol_resume(gol_t* game);

void gol_tick(gol_t* game);
void gol_render(gol_t* game, u32* render_buf, u32 render_width);

#endif // GOL_H
