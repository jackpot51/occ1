#include <stdint.h>

void main(void);

void __at(0x100) start(void) __naked {
    __asm
    ld sp, #0x4000  // Set stack pointer to 16 KiB
    jp _main        // Jump to main function
    __endasm;
}

uint16_t bdos(uint8_t func, uint16_t param) __naked {
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

char getchar(void) {
    return bdos(6, 0xFF);
}

void putchar(char c) {
    bdos(6, c);
}

void puts(const char * s) {
    char c;
    while(c = *s++) {
        putchar(c);
    }
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

// OSBORNE 1: 4 MHz, runs delay loop in 24 clocks
// Run emulator at 4 Mhz and 6 clocks per instruction to match!
#define CLOCKS_PER_S 4000000
#define CLOCKS_PER_LOOP 24
#define LOOPS_PER_S (CLOCKS_PER_S / CLOCKS_PER_LOOP)
#define FRAMERATE 60
#define LOOPS_PER_FRAME (LOOPS_PER_S / FRAMERATE)

void delay_frame(void) __naked {
    __asm
        push de
        push af

        ld de, #LOOPS_PER_FRAME
    loop:           // Clocks per instruction: http://www.z80.info/z80time.txt
        dec de      // 6 clocks
        ld a, d     // 4 clocks
        or e        // 4 clocks
        jp nz, loop // 10 clocks
                    // 24 clocks total

        pop af
        pop de
        ret
    __endasm;
}
