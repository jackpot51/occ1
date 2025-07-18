#include <stdio.h>
#include "common.h"
#include "notes.h"

#pragma codeseg BEEP

#define VIDEO_PIA_PORT_B_DATA 0x2C02
#define VIDEO_PIA_PORT_B_CONTROL 0x2C03

void bell(uint8_t on) {
    // Switch to bank 2 for port access
    __asm
        out (#0), a
    __endasm;

    uint8_t * control = (uint8_t *)VIDEO_PIA_PORT_B_CONTROL;
    *control = 4;

    uint8_t * data = (uint8_t *)VIDEO_PIA_PORT_B_DATA;
    if (on) {
        *data |= 0x20;
    } else {
        *data &= 0xDF;
    }
    
    // Switch to bank 1 for program access
    __asm
        out (#1), a
    __endasm;
}

void note(uint16_t half_period_loops, int32_t total_loops) {
    while(total_loops > 0) {
        bell(1);
        delay_loops(half_period_loops);
        total_loops -= half_period_loops;
        bell(0);
        delay_loops(half_period_loops);
        total_loops -= half_period_loops;
    }
}

#define NOTE(hz, ms)  { \
    puts(#hz " \r"); \
    note(((LOOPS_PER_S / hz) / 2L), ((LOOPS_PER_S * ms) / 1000L)); \
}

#define BPM 240L
#define QUARTER (60000L / BPM)
#define HALF (QUARTER * 2L)
#define EIGHTH (QUARTER / 2L)
#define SIXTEENTH (EIGHTH / 2L)

void main() {
    puts(
        "##           #           #               #\r\n"
        "######     #####       #####    #       ##\r\n"
        "######### ########   ######## ####    ####\r\n"
        "### ##### ###  #### ####  ### #####  #####\r\n"
        "###   ### ###   ### ###   ### ############\r\n"
        "###   ### ###   ### ###   ### ### #### ###\r\n"
        "###   ### ###   ### ###   ### ###  ##  ###\r\n"
        "###   ### ###   ### ###   ### ###      ###\r\n"
        "###  ###  #### #### #### #### ###      ###\r\n"
        "### ###    ######     ######   ##      ###\r\n"
        "#####        ##         ##      #      ###\r\n"
        "###                                    ###\r\n"
        "#                                        #\r\n"
    );

    // Disable interrupts
    __asm
        di
    __endasm;

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(E3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(D3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(C3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(Bb2, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(B2, EIGHTH);
    NOTE(C3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(E3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(D3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(C3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(Bb2, HALF);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(E3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(D3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(C3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(Bb2, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(B2, EIGHTH);
    NOTE(C3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(E3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(D3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);

    NOTE(B3, SIXTEENTH);
    NOTE(G3, SIXTEENTH);
    NOTE(E3, SIXTEENTH);
    NOTE(G3, SIXTEENTH);
    NOTE(B3, SIXTEENTH);
    NOTE(G3, SIXTEENTH);
    NOTE(B3, SIXTEENTH);
    NOTE(E4, SIXTEENTH);
    NOTE(B3, SIXTEENTH);
    NOTE(G3, SIXTEENTH);
    NOTE(B3, SIXTEENTH);
    NOTE(G3, SIXTEENTH);
    NOTE(B3, SIXTEENTH);
    NOTE(E4, SIXTEENTH);
    NOTE(G4, SIXTEENTH);
    NOTE(B4, SIXTEENTH);

    NOTE(A2, EIGHTH);
    NOTE(A2, EIGHTH);
    NOTE(A3, EIGHTH);

    NOTE(A2, EIGHTH);
    NOTE(A2, EIGHTH);
    NOTE(G3, EIGHTH);

    NOTE(A2, EIGHTH);
    NOTE(A2, EIGHTH);
    NOTE(F3, EIGHTH);

    NOTE(A2, EIGHTH);
    NOTE(A2, EIGHTH);
    NOTE(Eb3, EIGHTH);

    NOTE(A2, EIGHTH);
    NOTE(A2, EIGHTH);
    NOTE(E3, EIGHTH);
    NOTE(F3, EIGHTH);

    NOTE(A2, EIGHTH);
    NOTE(A2, EIGHTH);
    NOTE(A3, EIGHTH);

    NOTE(A2, EIGHTH);
    NOTE(A2, EIGHTH);
    NOTE(G3, EIGHTH);

    NOTE(A2, EIGHTH);
    NOTE(A2, EIGHTH);
    NOTE(F3, EIGHTH);

    NOTE(A2, EIGHTH);
    NOTE(A2, EIGHTH);
    NOTE(Eb3, HALF);

    NOTE(A2, EIGHTH);
    NOTE(A2, EIGHTH);
    NOTE(A3, EIGHTH);

    NOTE(A2, EIGHTH);
    NOTE(A2, EIGHTH);
    NOTE(G3, EIGHTH);

    NOTE(A2, EIGHTH);
    NOTE(A2, EIGHTH);
    NOTE(F3, EIGHTH);

    NOTE(A2, EIGHTH);
    NOTE(A2, EIGHTH);
    NOTE(Eb3, EIGHTH);

    NOTE(A2, EIGHTH);
    NOTE(A2, EIGHTH);
    NOTE(E3, EIGHTH);
    NOTE(F3, EIGHTH);

    NOTE(A2, EIGHTH);
    NOTE(A2, EIGHTH);
    NOTE(A3, EIGHTH);

    NOTE(A2, EIGHTH);
    NOTE(A2, EIGHTH);
    NOTE(G3, EIGHTH);

    NOTE(A2, EIGHTH);
    NOTE(A2, EIGHTH);

    NOTE(A4, SIXTEENTH);
    NOTE(E4, SIXTEENTH);
    NOTE(E4, SIXTEENTH);
    NOTE(A4, SIXTEENTH);
    NOTE(E4, SIXTEENTH);
    NOTE(C4, SIXTEENTH);
    NOTE(E4, SIXTEENTH);
    NOTE(A4, SIXTEENTH);
    NOTE(C5, SIXTEENTH);
    NOTE(A4, SIXTEENTH);
    NOTE(E4, SIXTEENTH);
    NOTE(A4, SIXTEENTH);
    NOTE(E4, SIXTEENTH);
    NOTE(A4, SIXTEENTH);
    NOTE(E4, SIXTEENTH);
    NOTE(C4, SIXTEENTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(E3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(D3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(C3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(Bb2, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(B2, EIGHTH);
    NOTE(C3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(E3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(D3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(C3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(Bb2, HALF);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(E3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(D3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(C3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(Bb2, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(B2, EIGHTH);
    NOTE(C3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(E3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(D3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(C3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(Bb2, HALF);

    NOTE(Db3, EIGHTH);
    NOTE(Db3, EIGHTH);
    NOTE(Db4, EIGHTH);

    NOTE(Db3, EIGHTH);
    NOTE(Db3, EIGHTH);
    NOTE(B3, EIGHTH);

    NOTE(Db3, EIGHTH);
    NOTE(Db3, EIGHTH);
    NOTE(A3, EIGHTH);

    NOTE(Db3, EIGHTH);
    NOTE(Db3, EIGHTH);
    NOTE(G3, EIGHTH);

    NOTE(Db3, EIGHTH);
    NOTE(Db3, EIGHTH);
    NOTE(Ab3, EIGHTH);
    NOTE(A3, EIGHTH);

    NOTE(B2, EIGHTH);
    NOTE(B2, EIGHTH);
    NOTE(B3, EIGHTH);

    NOTE(B2, EIGHTH);
    NOTE(B2, EIGHTH);
    NOTE(A3, EIGHTH);

    NOTE(B2, EIGHTH);
    NOTE(B2, EIGHTH);
    NOTE(G3, EIGHTH);

    NOTE(A2, EIGHTH);
    NOTE(A2, EIGHTH);
    NOTE(F3, HALF);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(E3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(D3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(C3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(Bb2, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(B2, EIGHTH);
    NOTE(C3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(E3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);
    NOTE(D3, EIGHTH);

    NOTE(E2, EIGHTH);
    NOTE(E2, EIGHTH);

    NOTE(G4, SIXTEENTH);
    NOTE(B4, SIXTEENTH);
    NOTE(E4, SIXTEENTH);
    NOTE(B3, SIXTEENTH);
    NOTE(G4, SIXTEENTH);
    NOTE(E4, SIXTEENTH);
    NOTE(B4, SIXTEENTH);
    NOTE(G4, SIXTEENTH);
    NOTE(B4, SIXTEENTH);
    NOTE(G4, SIXTEENTH);
    NOTE(E4, SIXTEENTH);
    NOTE(B3, SIXTEENTH);
    NOTE(G4, SIXTEENTH);
    NOTE(B4, SIXTEENTH);
    NOTE(E5, SIXTEENTH);
    NOTE(G5, SIXTEENTH);

    // Enable interrupts
    __asm
        ei
    __endasm;

    exit();
}
