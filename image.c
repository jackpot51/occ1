#include "common.h"

void main(void) {
    clear_screen();

    // Disable interrupts
    __asm__("di");

    uint8_t * vram = (uint8_t *)0xF000;

    for (uint16_t i = 0; i < 0x80; i++) {
        uint16_t y = (i / 16) * 2 + 1;
        uint16_t x = (i % 16) * 2 + 16;
        vram[y * 128 + x] = (uint8_t)i;
    }

    //TODO: restore system after some number of interations
    __asm
        // high part comes from i register
        ld a, i
        ld h, a
        // IRQ1 sends offset 0xF8
        ld l, #0xF8

        // replace IRQ1 handler
        ld de, #irq1
        ld (hl), e
        inc hl
        ld (hl), d
        ld c, (hl)
        inc hl
        ld b, (hl)
        dec hl

    idleloop:
        ei
        halt
        jp idleloop
    __endasm;

    // 1.28 msec prior to first scan line, this value is magically selected
    // to make things happen. The VSYNC interrupt should be used instead
    // At 4 MHz, this is 5120 cycles
    __asm
    irq1:               // 19 clocks to get to interrupt handler
        di              // 4 clocks
        push af         // 11 clocks
        push de         // 11 clocks
        push hl         // 11 clocks

        ld de, #210     // 10 clocks
    irq1loop:           // 24 clocks per iteration, multiply by DE
        dec de          // 6 clocks
        ld a, d         // 4 clocks
        or e            // 4 clocks
        jp nz, irq1loop // 10 clocks

        ld de, #0       // 10 clocks (nop)
        nop             // 4 clocks

    // Program for beam racing image generation
    #include "occ1/program.asm"

        //TODO ld a, (#0x2C00) // Clear interrupt

        pop hl          // 10 clocks
        pop de          // 10 clocks
        pop af          // 10 clocks
        ei              // Enable interrupts
        ret             // Return from interrupt
    __endasm;

    // Wait for key
    while (!getchar()) {}

    clear_screen();
    exit();
}
