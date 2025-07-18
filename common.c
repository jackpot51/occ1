#include "common.h"

uint16_t bdos(uint8_t func, uint16_t param) __naked __sdcccall(0) {
    // Use parameters
    func;
    param;

    __asm
        push iy
        ld iy, #4
        add iy, sp
        push ix
        // HL not saved as it is return value
        push de
        push bc
        push af

        ld c, (iy)   // func
        ld e,1(iy)  // param (low)
        ld d,2(iy)  // param (high)
        call 5        // Call BDOS

        pop af
        pop bc
        pop de
        // HL not restored as it is return value
        pop ix
        pop iy
        ret
    __endasm;
}

void exit(void) {
    bdos(0, 0);
}

int getchar(void) {
    return (int)bdos(6, 0xFF);
}

int putchar(char c) {
    bdos(6, c);
    return (int)c;
}

void clear_screen(void){
    putchar(0x1A);
}

void cursor_position(uint8_t x, uint8_t y) {
    // Position cursor
    putchar(0x1B);
    putchar('=');
    //TODO: ensure y <= 80
    putchar(y + 32);
    //TODO: ensure x <= 80
    putchar(x + 32);
}

void screen_position(uint8_t x, uint8_t y) {
    // Position cursor
    putchar(0x1B);
    putchar('S');
    //TODO: ensure y <= 80
    putchar(y + 32);
    //TODO: ensure x <= 80
    putchar(x + 32);
}

int fopen(struct FCB * fcb) {
    return (int)bdos(15, (uint16_t)fcb);
}

int fclose(struct FCB * fcb) {
    return (int)bdos(16, (uint16_t)fcb);
}

int fread(struct FCB * fcb, uint8_t buf[128]) {
    // Set DMA address
    bdos(26, (uint16_t)buf);
    // Read next record
    return (int)bdos(20, (uint16_t)fcb);
}

void delay_loops(uint16_t loops) __naked __sdcccall(0) {
    // Use parameters
    loops;

    //TODO: reduce instruction counts and adjust loops for wrapper instructions
    __asm
        push iy                 // 15 clocks
        ld iy, #4               // 14 clocks
        add iy, sp              // 15 clocks
        push de                 // 11 clocks
        push af                 // 11 clocks

        ld e, (iy)              // 19 clocks, loops (low)
        ld d,1(iy)              // 19 clocks, loops (high)
                                // 104 clocks total

    delay_loops_loop:           // Clocks per instruction: http://www.z80.info/z80time.txt
        dec de                  // 6 clocks
        ld a, d                 // 4 clocks
        or e                    // 4 clocks
        jp nz, delay_loops_loop // 10 clocks
                                // 24 clocks total

        pop af                  // 10 cycles
        pop de                  // 10 cycles
        pop iy                  // 14 cycles
        ret                     // 10 cycles
                                // 44 cycles total
                                // total non-loop cycles: 148, or 6.167 loops
    __endasm;
}

void delay_frame(void) __naked {
    __asm
        push de
        push af

        ld de, #LOOPS_PER_FRAME
    delay_frame_loop:           // Clocks per instruction: http://www.z80.info/z80time.txt
        dec de                  // 6 clocks
        ld a, d                 // 4 clocks
        or e                    // 4 clocks
        jp nz, delay_frame_loop // 10 clocks
                                // 24 clocks total

        pop af
        pop de
        ret
    __endasm;
}

void delay_ms(void) __naked {
    __asm
        push de
        push af

        ld de, #LOOPS_PER_MS
    delay_ms_loop:           // Clocks per instruction: http://www.z80.info/z80time.txt
        dec de               // 6 clocks
        ld a, d              // 4 clocks
        or e                 // 4 clocks
        jp nz, delay_ms_loop // 10 clocks
                             // 24 clocks total

        pop af
        pop de
        ret
    __endasm;
}
