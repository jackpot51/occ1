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

void main(void) {
    clear_screen();
    draw_index();
    while (getchar() == 0) {}
    exit();
}
