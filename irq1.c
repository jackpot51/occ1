#include "irq1.h"

#pragma codeseg IRQ1

uint8_t read_port(uint16_t port) {
    // Switch to bank 2 for port access
    __asm
        out (#0), a
    __endasm;

    uint8_t data = *((volatile uint8_t *)port);
    
    // Switch to bank 1 for program access
    __asm
        out (#1), a
    __endasm;

    return data;
}

void write_port(uint16_t port, uint8_t data) {
    // Switch to bank 2 for port access
    __asm
        out (#0), a
    __endasm;

    *((volatile uint8_t *)port) = data;
    
    // Switch to bank 1 for program access
    __asm
        out (#1), a
    __endasm;
}

void irq1_override(void) {
    //TODO: restore system after some number of interations
    __asm
        // Save registers
        push af
        push de
        push hl

        // Disable interrupts
        di

        // high part comes from i register
        ld a, i
        ld h, a
        // IRQ1 sends offset 0xF8
        ld l, #0xF8

        // replace IRQ1 handler
        ld de, #_irq1_handler
        ld (hl), e
        inc hl
        ld (hl), d

        // Enable interrupts
        ei

        // Restore registers
        pop hl
        pop de
        pop af
    __endasm;
}

// This handler must be above 16 KiB to be in bank 2
void irq1_handler(void) __naked {
    // 1.28 msec prior to first scan line, this value is magically selected
    // to make things happen. The VSYNC interrupt should be used instead
    // At 4 MHz, this is 5120 cycles
    //TODO: had to adjust loops for mame
    __asm
                                // 19 clocks to get to interrupt handler
        di                      // 4 clocks
        push af                 // 11 clocks
        push de                 // 11 clocks
        push hl                 // 11 clocks

        ld de, #197             // 10 clocks, WAS #196
                                // total non-loop: 66 clocks


    irq1_loop:                  // 24 clocks per iteration, multiply by DE
        dec de                  // 6 clocks
        ld a, d                 // 4 clocks
        or e                    // 4 clocks
        jp nz, irq1_loop        // 10 clocks
                                // total loop: 196 * 24 = 4704 clocks

        out (#1), a             // 11 clocks, Switch to bank 1 for program access
        ld hl, (#_irq1_count)   // 20 clocks
        inc hl                  // 6 clocks
        ld (#_irq1_count), hl   // 16 clocks
        ld hl, (#_irq1_program) // 20 clocks
        jp (hl)                 // 4 clocks, jump to frame program
                                // total non-loop: 77 clocks
                                // total: 66 + 4728 + 77 = 4871 clocks / 4 Mhz = 1.21775 ms

    .globl _irq1_count
    _irq1_count: .word 0

    .globl _irq1_program
    _irq1_program: .word _irq1_ret
    __endasm;
}

void irq1_ret(void) __naked {
    __asm
        out (#0), a             // 11 clocks, Switch to bank 2 for port access
        ld a, (#0x2C00)         // 13 clocks, Clear interrupt
        out (#1), a             // 11 clocks, Switch to bank 1 for program access
        pop hl                  // 10 clocks
        pop de                  // 10 clocks
        pop af                  // 10 clocks
        ei                      // 4 clocks, Enable interrupts
        ret                     // 10 clocks, Return from interrupt, TODO: use reti?
    __endasm;
}
