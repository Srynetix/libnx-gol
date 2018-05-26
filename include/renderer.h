#ifndef GOL_RENDERER_H
#define GOL_RENDERER_H

#include "types/standard.h"
#include "types/renderer.h"

/**
 * Initialize a renderer.
 * 
 * @returns Renderer
 */
renderer_t* renderer_init();

/**
 * Check if a renderer is running.
 * 
 * @param renderer  Renderer
 * @returns Running?
 */
bool renderer_is_running(renderer_t* renderer);

/**
 * Stop a renderer.
 * 
 * @param renderer  Renderer
 */
void renderer_stop(renderer_t* renderer);

/**
 * Start the renderer render pass.
 * 
 * @param renderer  Renderer
 */
void renderer_render(renderer_t* renderer);

/**
 * Stop the renderer.
 * 
 * @param renderer  Renderer
 */
void renderer_shutdown(renderer_t* renderer);

#endif // GOL_RENDERER_H
