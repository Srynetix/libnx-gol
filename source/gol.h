#ifndef GOL_H
#define GOL_H

#include "types.h"

#define GOL_CELL_DEAD	0
#define GOL_CELL_ALIVE	1

/**
 * Game of Life structure
 */
typedef struct gol_t {
    /// Back buffer
    u8* back_buf;
    /// Front buffer
    u8* front_buf;
    /// Life buffer
    u8* life_buf;

    /// Grid width
    u32 grid_width;
    /// Grid height
    u32 grid_height;
    /// Grid size (width * height)
    u32 grid_sz;

    /// Cell size
    u32 cell_size;
    /// Cell alive color
    u32 cell_alive_color;
    /// Cell dead color
    u32 cell_dead_color;

    /// Is the game stopped?
    BOOL stopped;
} gol_t;


/**
 * Initialize Game of Life.
 * 
 * @param grid_width    Grid width
 * @param grid_height   Grid height
 * @param cell_size     Cell size
 * @param alive_color   Alive cell color
 * 
 * @return Game of Life instance
 */
gol_t* gol_init(u32 grid_width, u32 grid_height, u32 cell_size, u32 initial_chance, u32 alive_color);

/**
 * Shutdown Game of Life.
 * 
 * Free all resources.
 * 
 * @param game  Game
 */
void gol_shutdown(gol_t* game);

/**
 * Randomize cell states.
 * 
 * @param game      Game
 * @param chance    Random chance (between 0 and 100)
 */
void gol_randomize(gol_t* game, u8 chance);

/**
 * Revive cells at a position, with a diameter.
 * 
 * @param game      Game
 * @param pos_x     X coordinate
 * @param pos_y     Y coordinate
 * @param diam_x    X diameter
 * @param diam_y    Y diameter
 */
void gol_revive_cells_at_position(gol_t* game, u32 pos_x, u32 pos_y, u32 diam_x, u32 diam_y);

/**
 * Pause game
 * 
 * @param game  Game
 */
void gol_pause(gol_t* game);

/**
 * Resume game
 * 
 * @param game  Game
 */
void gol_resume(gol_t* game);

/**
 * Perform one game step.
 * 
 * @param game  Game
 */
void gol_tick(gol_t* game);

/**
 * Render the game in a render buffer.
 * 
 * @param game          Game
 * @param render_buf    Render buffer
 * @param render_width  Render width
 */
void gol_render(gol_t* game, u32* render_buf, u32 render_width);

/**
 * Swap buffers.
 * 
 * @param game  Game
 */
void gol_swap_buffers(gol_t* game);

#endif // GOL_H
