.module start
.globl _main

.area _START (ABS)
.org 0x100
start:
    ld sp, #0xC800  ; Set stack pointer to 50 KiB
    call _main      ; Call main function
    rst 0           ; Exit program

.area _CODE
.area _DATA
