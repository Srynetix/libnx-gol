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
    0x1e10bc2f, // E
    0x0210bc2f, // F
    0x0c94b42e, // G
    0x1294bd29, // H
    0x08421084, // I
    0x0c94210f, // J
    0x12928ca9, // K
    0x1e108421, // L
    0x2318d771, // M
    0x1294b569, // N
    0x0c94a526, // O
    0x0210bd2f, // P
    0x2c9ac62e, // Q
    0x12949d27, // R
    0x1e843c2f, // S
    0x0842108f, // T
    0x0c94a529, // U
    0x08a8c631, // V
    0x155ac631, // W
    0x22a22a31, // X
    0x08422a31, // Y
    0x1e11110f  // Z
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
