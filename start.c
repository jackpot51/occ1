#pragma codeseg START

void main(void);

void start(void) __naked {
    __asm
    ld sp, #0xC800  // Set stack pointer to 50 KiB
    jp _main        // Jump to main function
    __endasm;
}
