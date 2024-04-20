#include "common.h"
#include "irq1.h"

void image(void) __naked {
    __asm
    #include "occ1/program.asm"
    jp _irq1_ret
    __endasm;
}

void main(void) {
    clear_screen();

    irq1_program = (uint16_t)image;
    irq1_override();

    while(1) {}
}
