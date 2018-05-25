#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "font.h"
#include "utils.h"
#include "color.h"

// Limits

const s32 PUNCT_FIRST_MIN = 33;
const s32 PUNCT_FIRST_MAX = 47;
const s32 NUMBERS_MIN = 48;
const s32 NUMBERS_MAX = 57;
const s32 PUNCT_SECND_MIN = 58;
const s32 PUNCT_SECND_MAX = 64;
const s32 MAJ_LETTERS_MIN = 65;
const s32 MAJ_LETTERS_MAX = 90;
const s32 PUNCT_THIRD_MIN = 91;
const s32 PUNCT_THIRD_MAX = 96;
const s32 MIN_LETTERS_MIN = 97;
const s32 MIN_LETTERS_MAX = 122;
const s32 PUNCT_FOURT_MIN = 123;
const s32 PUNCT_FOURT_MAX = 126;

// 33 - 47
const s32 PUNCT_FIRST[] = {
    0x00000000, // !
    0x00000000, // "
    0x00000000, // #
    0x00000000, // $
    0x00000000, // %
    0x00000000, // &
    0x00000000, // '
    0x00000000, // (
    0x00000000, // )
    0x00000000, // *
    0x00023880, // +
    0x00000000, // ,
    0x00003800, // -
    0x00000000, // .
    0x00000000, // /
};

// 48 - 57
const s32 NUMBERS[] = {
    0x00000000, // 0
    0x00000000, // 1
    0x00000000, // 2
    0x00000000, // 3
    0x00000000, // 4
    0x00000000, // 5
    0x00000000, // 6
    0x00000000, // 7
    0x00000000, // 8
    0x00000000  // 9
};

// 58 - 64
const s32 PUNCT_SECND[] = {
    0x00000000, // :
    0x00000000, // ;
    0x00000000, // <
    0x00000000, // =
    0x00000000, // >
    0x00000000, // ?
    0x00000000  // @
};

// 65 - 90
const s32 MAJ_LETTERS[] = {
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

// 91 - 96
const s32 PUNCT_THIRD[] = {
    0x00000000, // [
    0x00000000, // <Backspace>
    0x00000000, // ]
    0x00000000, // ^
    0x00000000, // _
    0x00000000, // `
};

// 97 - 122
const s32 MIN_LETTERS[] = {
    0x00000000, // a
    0x00000000, // b
    0x00000000, // c
    0x00000000, // d
    0x00000000, // e
    0x00000000, // f
    0x00000000, // g
    0x00000000, // h
    0x00000000, // i
    0x00000000, // j
    0x00000000, // k
    0x00000000, // l
    0x00000000, // m
    0x00000000, // n
    0x00000000, // o
    0x00000000, // p
    0x00000000, // q
    0x00000000, // r
    0x00000000, // s
    0x00000000, // t
    0x00000000, // u
    0x00000000, // v
    0x00000000, // w
    0x00000000, // x
    0x00000000, // y
    0x00000000  // z
};

// 123 - 126
const s32 PUNCT_FOURT[] = {
    0x00000000, // {
    0x00000000, // |
    0x00000000, // }
    0x00000000  // ~
};

u32 font_fn_get_char_data(char c) {
    // Punct first
    if (c >= PUNCT_FIRST_MIN && c <= PUNCT_FIRST_MAX) {
        return PUNCT_FIRST[c - PUNCT_FIRST_MIN];
    }

    // Number
    if (c >= NUMBERS_MIN && c <= NUMBERS_MAX) {
        return NUMBERS[c - NUMBERS_MIN];
    }

    // Punct second
    if (c >= PUNCT_SECND_MIN && c <= PUNCT_SECND_MAX) {
        return PUNCT_SECND[c - PUNCT_SECND_MIN];
    }

    // Maj letter
    if (c >= MAJ_LETTERS_MIN && c <= MAJ_LETTERS_MAX) {
        return MAJ_LETTERS[c - MAJ_LETTERS_MIN];
    }

    // Punct third
    if (c >= PUNCT_THIRD_MIN && c <= PUNCT_THIRD_MIN) {
        return PUNCT_THIRD[c - PUNCT_THIRD_MIN];
    }

    // Min letter
    if (c >= MIN_LETTERS_MIN && c <= MIN_LETTERS_MAX) {
        return MIN_LETTERS[c - MIN_LETTERS_MIN];
    }

    // Punct fourth
    if (c >= PUNCT_FOURT_MIN && c <= PUNCT_FOURT_MAX) {
        return PUNCT_FOURT[c - PUNCT_FOURT_MIN];
    }

    return 0;
}

void font_render_char(char c, renderer_t* renderer, u32 font_size, u32 pos_x, u32 pos_y, color_t color) {
    u32* buf = renderer->framebuffer;
    u32 buf_width = renderer->width;
    u32 data = font_fn_get_char_data(c);
    
    if (data == 0)
        return;

    for (u32 j = 0; j < FONT_HEIGHT * font_size; ++j) {
        for (u32 i = 0; i < FONT_WIDTH * font_size; ++i) {
            u32 cell_idx = pos_y * buf_width + pos_x + (i + j * buf_width);
            u32 k = (i / font_size) + (j / font_size) * FONT_WIDTH;

            u8 pxl = (data >> k) & 1;
            if (pxl == 1) {
                // Check for alpha blending
                color_t existing_color = color_unpack(buf[cell_idx]);
                color_t blended_color = color_alpha_blend(color, existing_color);
                buf[cell_idx] = color_pack(blended_color);
            }
        }
    }
}

void font_render(const char* str, renderer_t* renderer, u32 font_size, u32 pos_x, u32 pos_y, color_t color) {
    u32 str_len = strlen(str);

    for (u32 c = 0; c < str_len; ++c) {
        u32 curr_x = pos_x + (c * ((FONT_WIDTH * font_size) + (1 * font_size))); 
        font_render_char(str[c], renderer, font_size, curr_x, pos_y, color);
    }
}
