#include "common.h"
#include "irq1.h"
#include "notes.h"

void character_map(void) {
    uint8_t * vram = (uint8_t *)0xF000;
    for (uint16_t i = 0; i < 0x80; i++) {
        uint16_t y = (i / 16) * 2 + 1;
        uint16_t x = (i % 16) * 2 + 18;
        vram[y * 128 + x] = (uint8_t)i;
    }
}

void frame1(void) __naked {
    __asm
    #include "occ1/build/frame-10.asm"
    jp _irq1_ret
    __endasm;
}

void frame2(void) __naked {
    __asm
    #include "occ1/build/frame-13.asm"
    jp _irq1_ret
    __endasm;
}

void frame3(void) __naked {
    __asm
    #include "occ1/build/frame-16.asm"
    jp _irq1_ret
    __endasm;
}

void frame4(void) __naked {
    __asm
    #include "occ1/build/frame-18.asm"
    jp _irq1_ret
    __endasm;
}

void frame5(void) __naked {
    __asm
    #include "occ1/build/frame-21.asm"
    jp _irq1_ret
    __endasm;
}

void frame6(void) __naked {
    __asm
    #include "occ1/build/frame-24.asm"
    jp _irq1_ret
    __endasm;
}

void frame7(void) __naked {
    __asm
    #include "occ1/build/frame-27.asm"
    jp _irq1_ret
    __endasm;
}

void frame8(void) __naked {
    __asm
    #include "occ1/build/frame-30.asm"
    jp _irq1_ret
    __endasm;
}

#define VIDEO_PIA_PORT_B_DATA 0x2C02
#define VIDEO_PIA_PORT_B_CONTROL 0x2C03

// This handler must be above 16 KiB to be in bank 2
void bell(uint8_t on) {
    // Disable interrupts and switch to bank 2 for port access
    __asm
    di
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

    // Switch to bank 1 for program access and enable interrupts
    __asm
    out (#1), a
    ei
    __endasm;
}

void main(void) {
    clear_screen();

    // Disable interrupts
    __asm__("di");

    //character_map();

    //TODO: restore system after some number of interations
    irq1_override();

    uint16_t last_count = 0;
    uint16_t last_frame = 0xFFFF;
    uint16_t half_period_loops = 0;
    while(1) {
        uint16_t count = irq1_count;
        if (count != last_count) {
            last_count = count;
            // 18 interrupts is about 3.33 FPS (300 ms per frame)
            uint16_t frame = (count / 18) % 8;
            if (frame != last_frame) {
                last_frame = frame;
                switch (frame) {
                    case 0:
                        irq1_program = (uint16_t)frame1;
                        break;
                    case 1:
                        irq1_program = (uint16_t)frame2;
                        break;
                    case 2:
                        irq1_program = (uint16_t)frame3;
                        break;
                    case 3:
                        irq1_program = (uint16_t)frame4;
                        break;
                    case 4:
                        irq1_program = (uint16_t)frame5;
                        break;
                    case 5:
                        irq1_program = (uint16_t)frame6;
                        break;
                    case 6:
                        irq1_program = (uint16_t)frame7;
                        break;
                    case 7:
                        irq1_program = (uint16_t)frame8;
                        break;
                }
            }

            //TODO: more efficient representation
            #define BPM 114
            #define QUARTER (3600 / BPM)
            #define QUARTER_DOT (QUARTER + EIGHTH)
            #define HALF (QUARTER * 2)
            #define EIGHTH (QUARTER / 2)
            #define SIXTEENTH (EIGHTH / 2)
            // 1
            #define N1 QUARTER_DOT
            #define N2 (N1 + QUARTER_DOT)
            #define N3 (N2 + QUARTER)
            // 2
            #define N4 (N3 + QUARTER_DOT)
            #define N5 (N4 + QUARTER_DOT)
            #define N6 (N5 + SIXTEENTH)
            #define N7 (N6 + SIXTEENTH)
            #define N8 (N7 + EIGHTH)
            // 3
            #define N9 (N8 + QUARTER_DOT)
            #define N10 (N9 + QUARTER_DOT)
            #define N11 (N10 + QUARTER)
            // 4
            #define N12 (N11 + QUARTER_DOT)
            #define N13 (N12 + QUARTER)
            #define N14 (N13 + SIXTEENTH)
            #define N15 (N14 + SIXTEENTH)
            #define N16 (N15 + SIXTEENTH)
            #define N17 (N16 + EIGHTH)
            #define N18 (N17 + SIXTEENTH)
            // We adjust the notes slightly for audibility
            #define NOTE(frequency) half_period_loops = (LOOPS_PER_S / (frequency * 2))
            uint16_t note = count % N18;
            if (note < N1) {
                NOTE(Db4);
            } else if (note < N2) {
                NOTE(Eb4);
            } else if (note < N3) {
                NOTE(Ab3);
            } else if (note < N4) {
                NOTE(Eb4);
            } else if (note < N5) {
                NOTE(F4);
            } else if (note < N6) {
                NOTE(Ab4);
            } else if (note < N7) {
                NOTE(Gb4);
            } else if (note < N8) {
                NOTE(F4);
            } else if (note < N9) {
                NOTE(Db4);
            } else if (note < N10) {
                NOTE(Eb4);
            } else if (note < N11) {
                NOTE(Ab3);
            } else if (note < N12) {
                NOTE(Ab3);
            } else if (note < N13) {
                half_period_loops = 0;
            } else if (note < N14) {
                NOTE(Ab2);
            } else if (note < N15) {
                NOTE(Ab2);
            } else if (note < N16) {
                NOTE(Bb2);
            } else if (note < N17) {
                NOTE(Db4);
            } else if (note < N18) {
                NOTE(Db3);
            } else {
                half_period_loops = 0;
            }
        }

        if (half_period_loops > 0) {
            // Play bell
            bell(1);
            delay_loops(half_period_loops);
            bell(0);
            delay_loops(half_period_loops);
        }
    }
}
