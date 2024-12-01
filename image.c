#include <stdio.h>
#include <string.h>
#include "common.h"
#include "irq1.h"

#define VIDEO_PIA_PORT_A_DATA 0x2C00
#define VIDEO_PIA_PORT_A_CONTROL 0x2C01

void memset_screen(char c) {
    uint8_t * vram = (uint8_t *)VRAM;
    memset(vram, c, ROWS * 128);
}

void osborne(void) __naked {
    __asm
    #include "build/osborne.asm"
    jp _irq1_ret
    __endasm;
}

void redox(void) __naked {
    __asm
    #include "build/redox.asm"
    jp _irq1_ret
    __endasm;
}

void main(void) {
    uint8_t pa_data = read_port(VIDEO_PIA_PORT_A_DATA);

    clear_screen();

    // The osborne image must have VRAM set to 0x16 (full block)
    memset_screen(0x16);

    cursor_position(0, 22);
    printf("01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567");
    cursor_position(0, 23);
    printf("0         1         2         3         4         5         6         7         8         9        10        11        12      ");

    irq1_program = (uint16_t)osborne;
    irq1_override();

    uint16_t last_count = 0;
    int8_t x = 0;
    int8_t dx = 1;
    while(1) {
        uint16_t count = irq1_count;
        if (count != last_count) {
            last_count = count;

            if (count % 2 == 0) {
                irq1_program = (uint16_t)osborne;
            } else {
                irq1_program = (uint16_t)redox;
            }

            /* Panning for testing
            if (count % 4 == 0) {
                if (x <= -40) {
                    x = -40;
                    dx = 1;
                } else if (x >= 20) {
                    x = 20;
                    dx = -1;
                }
                x += dx;
                
                // Set X offset, preserving density bit
                write_port(VIDEO_PIA_PORT_A_DATA, (x << 1) | pa_data & 1);
            }
            */
        }
    }
}
