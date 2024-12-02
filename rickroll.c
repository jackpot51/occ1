#include <string.h>
#include "common.h"
#include "irq1.h"
#include "notes.h"

#define FRAME10
//#define FRAME11
#define FRAME12
//#define FRAME13
#define FRAME14
//#define FRAME15
#define FRAME16
//#define FRAME17
#define FRAME18
//#define FRAME19
#define FRAME20
//#define FRAME21
#define FRAME22
//#define FRAME23
#define FRAME24
//#define FRAME25
#define FRAME26
//#define FRAME27
#define FRAME28
//#define FRAME29
#define FRAME30

#ifdef FRAME10
void frame10(void) __naked {
    __asm
    #include "occ1/build/frame-10.asm"
    jp _irq1_ret
    __endasm;
}
#endif

#ifdef FRAME11
void frame11(void) __naked {
    __asm
    #include "occ1/build/frame-11.asm"
    jp _irq1_ret
    __endasm;
}
#endif

#ifdef FRAME12
void frame12(void) __naked {
    __asm
    #include "occ1/build/frame-12.asm"
    jp _irq1_ret
    __endasm;
}
#endif

#ifdef FRAME13
void frame13(void) __naked {
    __asm
    #include "occ1/build/frame-13.asm"
    jp _irq1_ret
    __endasm;
}
#endif

#ifdef FRAME14
void frame14(void) __naked {
    __asm
    #include "occ1/build/frame-14.asm"
    jp _irq1_ret
    __endasm;
}
#endif

#ifdef FRAME15
void frame15(void) __naked {
    __asm
    #include "occ1/build/frame-15.asm"
    jp _irq1_ret
    __endasm;
}
#endif

#ifdef FRAME16
void frame16(void) __naked {
    __asm
    #include "occ1/build/frame-16.asm"
    jp _irq1_ret
    __endasm;
}
#endif

#ifdef FRAME17
void frame17(void) __naked {
    __asm
    #include "occ1/build/frame-17.asm"
    jp _irq1_ret
    __endasm;
}
#endif

#ifdef FRAME18
void frame18(void) __naked {
    __asm
    #include "occ1/build/frame-18.asm"
    jp _irq1_ret
    __endasm;
}
#endif

#ifdef FRAME19
void frame19(void) __naked {
    __asm
    #include "occ1/build/frame-19.asm"
    jp _irq1_ret
    __endasm;
}
#endif

#ifdef FRAME20
void frame20(void) __naked {
    __asm
    #include "occ1/build/frame-20.asm"
    jp _irq1_ret
    __endasm;
}
#endif

#ifdef FRAME21
void frame21(void) __naked {
    __asm
    #include "occ1/build/frame-21.asm"
    jp _irq1_ret
    __endasm;
}
#endif

#ifdef FRAME22
void frame22(void) __naked {
    __asm
    #include "occ1/build/frame-22.asm"
    jp _irq1_ret
    __endasm;
}
#endif

#ifdef FRAME23
void frame23(void) __naked {
    __asm
    #include "occ1/build/frame-23.asm"
    jp _irq1_ret
    __endasm;
}
#endif

#ifdef FRAME24
void frame24(void) __naked {
    __asm
    #include "occ1/build/frame-24.asm"
    jp _irq1_ret
    __endasm;
}
#endif

#ifdef FRAME25
void frame25(void) __naked {
    __asm
    #include "occ1/build/frame-25.asm"
    jp _irq1_ret
    __endasm;
}
#endif

#ifdef FRAME26
void frame26(void) __naked {
    __asm
    #include "occ1/build/frame-26.asm"
    jp _irq1_ret
    __endasm;
}
#endif

#ifdef FRAME27
void frame27(void) __naked {
    __asm
    #include "occ1/build/frame-27.asm"
    jp _irq1_ret
    __endasm;
}
#endif

#ifdef FRAME28
void frame28(void) __naked {
    __asm
    #include "occ1/build/frame-28.asm"
    jp _irq1_ret
    __endasm;
}
#endif

#ifdef FRAME29
void frame29(void) __naked {
    __asm
    #include "occ1/build/frame-29.asm"
    jp _irq1_ret
    __endasm;
}
#endif

#ifdef FRAME30
void frame30(void) __naked {
    __asm
    #include "occ1/build/frame-30.asm"
    jp _irq1_ret
    __endasm;
}
#endif

void nops(void) __naked {
    __asm
    #include "nop.asm"
    __endasm;
}

void memset_screen(char c) {
    uint8_t * vram = (uint8_t *)VRAM;
    memset(vram, c, ROWS * 128);
}

/*
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
*/

void main(void) {
    clear_screen();

    memset_screen(0x16);

    //TODO: restore system after some number of interations
    irq1_override();

    uint16_t last_count = 0;
    uint16_t last_frame = 0xFFFF;
    uint16_t half_period_loops = 0;
    while(1) {
        uint16_t count = irq1_count;
        if (count != last_count) {
            last_count = count;
            // 6 interrupts is about 10 FPS (100 ms per frame)
            uint16_t frame = (count / 6) % 20;
            if (frame != last_frame) {
                last_frame = frame;
                switch (frame) {
                    #ifdef FRAME10
                    case 0:
                        irq1_program = (uint16_t)frame10;
                        break;
                    #endif
                    
                    #ifdef FRAME11
                    case 1:
                        irq1_program = (uint16_t)frame11;
                        break;
                    #endif
                    
                    #ifdef FRAME12
                    case 2:
                        irq1_program = (uint16_t)frame12;
                        break;
                    #endif
                    
                    #ifdef FRAME13
                    case 3:
                        irq1_program = (uint16_t)frame13;
                        break;
                    #endif
                    
                    #ifdef FRAME14
                    case 4:
                        irq1_program = (uint16_t)frame14;
                        break;
                    #endif
                    
                    #ifdef FRAME15
                    case 5:
                        irq1_program = (uint16_t)frame15;
                        break;
                    #endif
                    
                    #ifdef FRAME16
                    case 6:
                        irq1_program = (uint16_t)frame16;
                        break;
                    #endif
                    
                    #ifdef FRAME17
                    case 7:
                        irq1_program = (uint16_t)frame17;
                        break;
                    #endif
                    
                    #ifdef FRAME18
                    case 8:
                        irq1_program = (uint16_t)frame18;
                        break;
                    #endif
                    
                    #ifdef FRAME19
                    case 9:
                        irq1_program = (uint16_t)frame19;
                        break;
                    #endif
                    
                    #ifdef FRAME20
                    case 10:
                        irq1_program = (uint16_t)frame20;
                        break;
                    #endif
                    
                    #ifdef FRAME21
                    case 11:
                        irq1_program = (uint16_t)frame21;
                        break;
                    #endif
                    
                    #ifdef FRAME22
                    case 12:
                        irq1_program = (uint16_t)frame22;
                        break;
                    #endif
                    
                    #ifdef FRAME23
                    case 13:
                        irq1_program = (uint16_t)frame23;
                        break;
                    #endif
                    
                    #ifdef FRAME24
                    case 14:
                        irq1_program = (uint16_t)frame24;
                        break;
                    #endif
                    
                    #ifdef FRAME25
                    case 15:
                        irq1_program = (uint16_t)frame25;
                        break;
                    #endif
                    
                    #ifdef FRAME26
                    case 16:
                        irq1_program = (uint16_t)frame26;
                        break;
                    #endif
                    
                    #ifdef FRAME27
                    case 17:
                        irq1_program = (uint16_t)frame27;
                        break;
                    #endif
                    
                    #ifdef FRAME28
                    case 18:
                        irq1_program = (uint16_t)frame28;
                        break;
                    #endif
                    
                    #ifdef FRAME29
                    case 19:
                        irq1_program = (uint16_t)frame29;
                        break;
                    #endif
                    
                    #ifdef FRAME30
                    case 20:
                        irq1_program = (uint16_t)frame30;
                        break;
                    #endif
                }
            }

            /*TODO: is it realistic to have sound?
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
            */
        }

        /*
        if (half_period_loops > 0) {
            // Play bell
            bell(1);
            delay_loops(half_period_loops);
            bell(0);
            delay_loops(half_period_loops);
        }
        */

        __asm
        halt
        __endasm;
    }
}
