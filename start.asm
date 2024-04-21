.area _HEADER (ABS)
.org 0x100
.globl _main
ld sp, #0xC800  ; Set stack pointer to 50 KiB
call _main      ; Call main function
rst 0           ; Exit program
