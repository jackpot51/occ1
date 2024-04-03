#pragma codeseg START

void main(void);

void start(void) __naked {
    __asm
    ld sp, #0x8000  // Set stack pointer to 32 KiB
    jp _main        // Jump to main function
    __endasm;
}
