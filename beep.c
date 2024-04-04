#include "common.h"

#define VIDEO_PIA_PORT_B_DATA 0x2C02
#define VIDEO_PIA_PORT_B_CONTROL 0x2C03

void bell(uint8_t on) {
    uint8_t * control = (uint8_t *)VIDEO_PIA_PORT_B_CONTROL;
    *control = 4;

    uint8_t * data = (uint8_t *)VIDEO_PIA_PORT_B_DATA;
    if (on) {
        *data |= 0x20;
    } else {
        *data &= 0xDF;
    }
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

#define NOTE(hz, ms) note((LOOPS_PER_S / hz) / 2, (LOOPS_PER_S * ms) / 1000)

#define C2 65
#define Db2 69
#define D2 73
#define E2 82
#define F2 87
#define G2 98
#define A2 110
#define Bb2 117
#define B2 123

#define C3 130
#define Db3 139
#define D3 147
#define Eb3 156
#define E3 165
#define F3 175
#define G3 196
#define Ab3 208
#define A3 220
#define B3 247

#define C4 262
#define Db4 277
#define D4 294
#define E4 330
#define F4 349
#define G4 392
#define A4 440
#define B4 494

#define C5 523
#define D5 587
#define E5 659
#define F5 698
#define G5 784
#define A5 880
#define B5 988

#define BPM 240
#define QUARTER (60000 / BPM)
#define HALF (QUARTER * 2)
#define EIGHTH (QUARTER / 2)
#define SIXTEENTH (EIGHTH / 2)


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

    // Disable interrupts and switch to bank 2 for port access
    __asm
        di
        out (#0), a
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

    // Switch to bank 1 for program access and enable interrupts
    __asm
        out (#1), a
        ei
    __endasm;

    exit();
}
