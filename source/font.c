#include "font.h"

#include <string.h>
#include <stdio.h>

#define FONT_WIDTH  5
#define FONT_HEIGHT 6

const s32 FONT[] = {
    0x1297a526, // A
    0x0e949d27, // B
    0x0c908526, // C
    0x0e94a527, // D
    0x0085e170  // E
};

u32 font_fn_get_char_data_idx(char c) {
    char maj_min = 'A';
    char maj_max = 'Z';
    char min_min = 'a';
    char min_max = 'z';

    // Maj
    if (c >= maj_min && c <= maj_max) {
        return c - maj_min;
    }

    // Min
    if (c >= min_min && c <= min_max) {
        return 26 + c - min_min;
    }

    return -1;
}

void font_fn_render_char(char c, renderer_t* renderer, u32 font_size, u32 pos_x, u32 pos_y, u32 color) {
    u32* buf = renderer->framebuffer;
    u32 buf_width = renderer->width;
    u32 data_idx = font_fn_get_char_data_idx(c);
    
    if (data_idx == -1)
        return;

    u32 data = FONT[data_idx];

    for (u32 j = 0; j < FONT_HEIGHT * font_size; ++j) {
        for (u32 i = 0; i < FONT_WIDTH * font_size; ++i) {
            u32 cell_idx = pos_y * buf_width + pos_x + (i + j * buf_width);
            u32 k = (i / font_size) + (j / font_size) * FONT_WIDTH;

            u8 pxl = (data >> k) & 1;
            if (pxl == 1) {
                buf[cell_idx] = color;
            }
        }
    }
}

void font_render(const char* str, renderer_t* renderer, u32 font_size, u32 pos_x, u32 pos_y, u32 color) {
    u32 str_len = strlen(str);

    for (u32 c = 0; c < str_len; ++c) {
        u32 curr_x = pos_x + (c * ((FONT_WIDTH * font_size) + (1 * font_size))); 
        font_fn_render_char(str[c], renderer, font_size, curr_x, pos_y, color);
    }
}
