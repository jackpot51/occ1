#include <stdio.h>

#include "irq1.h"

void main(void) {
    for (;;) {
        // Disable interrupts
        __asm
            di
        __endasm;

        for (int row = 0; row < 8; row++) {
            uint8_t data = read_port(0x2200 | (1 << row));
            for (int col = 0; col < 8; col++) {
                if ((data & (1 << col)) == 0) {
                    printf("%d, %d\r\n", row, col);
                }
            }
        }

        // Enable interrupts
        __asm
            ei
        __endasm;
    }
}