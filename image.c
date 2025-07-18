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

/*
void left(void) __naked {
    __asm
    #include "build/image-left.asm"
    jp _irq1_ret
    __endasm;
}

void middle(void) __naked {
    __asm
    #include "build/image-middle.asm"
    jp _irq1_ret
    __endasm;
}
*/

void right(void) __naked {
    __asm
    #include "build/image-right.asm"
    jp _irq1_ret
    __endasm;
}

void nops(void) __naked {
    __asm
    #include "nop.asm"
    __endasm;
}

void main(void) {
    clear_screen();

    printf("Wait for the disk to spin down, then press any key\r\n");
    printf("to begin the bitmap image demo.\r\n");
    printf("\r\n");
    printf("The system will have to be reset afterwards.\r\n");
    while (getchar() == 0) {
        __asm
        halt
        __endasm;
    }

    // The osborne image must have VRAM set to 0x16 (full block)
    memset_screen(0x16);

    cursor_position(0, 22);
    printf("01234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567");
    cursor_position(0, 23);
    printf("0         1         2         3         4         5         6         7         8         9        10        11        12      ");

    irq1_program = (uint16_t)right;
    irq1_override();

    uint16_t last_count = 0;
    uint8_t pa_data = read_port(VIDEO_PIA_PORT_A_DATA);
    int8_t x = -10;
    int8_t dx = 1;
    while(1) {
        uint16_t count = irq1_count;
        if (count != last_count) {
            last_count = count;

            /*
            switch (count % 3) {
                case 0:
                    irq1_program = (uint16_t)left;
                    break;
                case 1:
                    irq1_program = (uint16_t)middle;
                    break;
                case 2:
                    irq1_program = (uint16_t)right;
                    break;
            }
            */

            // Panning for testing, at 10Hz
            /*
            if (count % 6 == 0) {
                if (x <= -29) {
                    x = -29;
                    dx = 1;
                } else if (x >= 23) {
                    x = 23;
                    dx = -1;
                }
                x += dx;
                
                // Set X offset, preserving density bit
                write_port(VIDEO_PIA_PORT_A_DATA, (x << 1) | pa_data & 1);
            }
            */
        }

        __asm
            halt
        __endasm;
    }
}
