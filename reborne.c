#include "common.h"

void draw_index(void) {
    uint8_t * vram = (uint8_t *)VRAM;
    for (uint16_t i = 0; i < 0x80; i++) {
        uint16_t y = ((i / 16) + 1) * 2;
        uint16_t x = ((i % 16) + 1) * 2;
        vram[y * 128 + x] = (uint8_t)i;

        // Draw index
        if (i < 8) {
            vram[x * 128] = (uint8_t)i + '0';
        }
        if (i < 10) {
            vram[x] = (uint8_t)i + '0';
        } else if (i < 16) {
            vram[x] = (uint8_t)(i - 0xA) + 'A';
        }
    }
}

#define VEC_END 0x00
#define VEC_CHAR 0x01
#define VEC_ADD_X 0x02
#define VEC_SUB_X 0x03
#define VEC_ADD_Y 0x04
#define VEC_SUB_Y 0x05
#define VEC_ADD_X_ADD_Y 0x06
#define VEC_ADD_X_SUB_Y 0x07
#define VEC_SUB_X_ADD_Y 0x08
#define VEC_SUB_X_SUB_Y 0x09

void draw_vector(uint8_t x, uint8_t y, int8_t * data) {
    // Start with filled block
    uint8_t c = 0x16;
    // Get initial vram pointer based on parameters
    uint8_t * vram = (uint8_t *)(VRAM + ((uint16_t)y) * 128 + x);
    while(1) {
        int8_t command = *data++;
        switch (command) {
            case VEC_END:
                *vram = c;
                return;
            case VEC_CHAR:
                c = *data++;
                break;
            case VEC_ADD_X:
                for (command = *data++; command > 0; command--) {
                    *vram = c;
                    vram++;
                }
                break;
            case VEC_SUB_X:
                for (command = *data++; command > 0; command--) {
                    *vram = c;
                    vram--;
                }
                break;
            case VEC_ADD_Y:
                for (command = *data++; command > 0; command--) {
                    *vram = c;
                    vram+=128;
                }
                break;
            case VEC_SUB_Y:
                for (command = *data++; command > 0; command--) {
                    *vram = c;
                    vram-=128;
                }
                break;
            case VEC_ADD_X_ADD_Y:
                for (command = *data++; command > 0; command--) {
                    *vram = c;
                    vram+=129;
                }
                break;
            case VEC_ADD_X_SUB_Y:
                for (command = *data++; command > 0; command--) {
                    *vram = c;
                    vram-=127;
                }
                break;
            case VEC_SUB_X_ADD_Y:
                for (command = *data++; command > 0; command--) {
                    *vram = c;
                    vram+=127;
                }
                break;
            case VEC_SUB_X_SUB_Y:
                for (command = *data++; command > 0; command--) {
                    *vram = c;
                    vram-=129;
                }
                break;
        }
    }
}

void draw_border(void) {
    uint8_t data[] = {
        VEC_CHAR, '#',
        VEC_ADD_X, 51,
        VEC_ADD_Y, 23,
        VEC_SUB_X, 51,
        VEC_SUB_Y, 22,
        VEC_END
    };
    draw_vector(0, 0, data);
}

void draw_r(uint8_t x, uint8_t y, char c) {
    //TODO: reduce encoding to one command per byte?
    uint8_t data[] = {
        VEC_CHAR, c,
        VEC_ADD_Y, 6,
        VEC_SUB_Y, 6,
        VEC_ADD_X, 2,
        VEC_ADD_X_ADD_Y, 1,
        VEC_ADD_Y, 1,
        VEC_SUB_X_ADD_Y, 1,
        VEC_SUB_X, 1,
        VEC_ADD_X, 1,
        VEC_ADD_X_ADD_Y, 1,
        VEC_ADD_Y, 2,
        VEC_END
    };
    draw_vector(x, y, data);
}

void draw_e(uint8_t x, uint8_t y, char c) {
    //TODO: reduce encoding to one command per byte?
    uint8_t data[] = {
        VEC_CHAR, c,
        VEC_ADD_X, 3,
        VEC_SUB_X, 3,
        VEC_ADD_Y, 3,
        VEC_ADD_X, 2,
        VEC_SUB_X, 2,
        VEC_ADD_Y, 3,
        VEC_ADD_X, 3,
        VEC_END
    };
    draw_vector(x, y, data);
}

void draw_b(uint8_t x, uint8_t y, char c) {
    //TODO: reduce encoding to one command per byte?
    uint8_t data[] = {
        VEC_CHAR, c,
        VEC_ADD_Y, 6,
        VEC_SUB_Y, 6,
        VEC_ADD_X, 2,
        VEC_ADD_X_ADD_Y, 1,
        VEC_ADD_Y, 1,
        VEC_SUB_X_ADD_Y, 1,
        VEC_SUB_X, 1,
        VEC_ADD_X, 1,
        VEC_ADD_X_ADD_Y, 1,
        VEC_ADD_Y, 1,
        VEC_SUB_X_ADD_Y, 1,
        VEC_SUB_X, 1,
        VEC_END
    };
    draw_vector(x, y, data);
}

void draw_o(uint8_t x, uint8_t y, char c) {
    // Add one to x to avoid painting top left corner
    x++;
    //TODO: reduce encoding to one command per byte?
    uint8_t data[] = {
        VEC_CHAR, c,
        VEC_ADD_X, 1,
        VEC_ADD_X_ADD_Y, 1,
        VEC_ADD_Y, 4,
        VEC_SUB_X_ADD_Y, 1,
        VEC_SUB_X, 1,
        VEC_SUB_X_SUB_Y, 1,
        VEC_SUB_Y, 4,
        VEC_END
    };
    draw_vector(x, y, data);
}

void draw_n(uint8_t x, uint8_t y, char c) {
    //TODO: reduce encoding to one command per byte?
    uint8_t data[] = {
        VEC_CHAR, c,
        VEC_ADD_Y, 6,
        VEC_SUB_Y, 5,
        VEC_ADD_X_ADD_Y, 3,
        VEC_ADD_Y, 2,
        VEC_SUB_Y, 6,
        VEC_END
    };
    draw_vector(x, y, data);
}

void draw_logo(int8_t offset, char c) {
    draw_r(6, 8 - offset, c);
    draw_e(12, 8 + offset, c);
    draw_b(18, 8 - offset, c);
    draw_o(24, 8 + offset, c);
    draw_r(30, 8 - offset, c);
    draw_n(36, 8 + offset, c);
    draw_e(42, 8 - offset, c);
}

void main(void) {
    clear_screen();

    //draw_index();

    draw_border();
    int8_t offset = 0;
    int8_t doffset = 1;
    while(1) {
        draw_logo(offset, ' ');
        offset+=doffset;
        draw_logo(offset, 0x16);
        if (offset >= 6 || offset <= -6) {
            doffset = -doffset;
        }
        for (uint8_t ms = 0; ms < 16; ms++) {
            delay_ms();
        }
        if (getchar()) {
            break;
        }
    }

    clear_screen();

    exit();
}
