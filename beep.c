#include "common.h"

#pragma codeseg SHADOW

#define VIDEO_PIA_PORT_B_DATA 0x2C02
#define VIDEO_PIA_PORT_B_CONTROL 0x2C03

void bell(uint8_t on) {
    // Disable interrupts and switch to bank 1 for port access
    __asm
        di
        out (#1), a
    __endasm;

    uint8_t * control = (uint8_t *)VIDEO_PIA_PORT_B_CONTROL;
    *control = 4;

    uint8_t * data = (uint8_t *)VIDEO_PIA_PORT_B_DATA;
    if (on) {
        *data |= 0x20;
    } else {
        *data &= 0xDF;
    }

    // Switch to bank 0 for program access and enable interrupts
    __asm
        out (#0), a
        ei
    __endasm;
}

void main() {
    puts("BELL ON\r\n");

    bell(1);
    for(int i = 0; i < 1000; i++) {
        delay_frame();
    }
    bell(0);

    puts("BELL OFF\r\n");
    exit();
}
