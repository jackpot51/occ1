ld hl, #0xF000
ld de, #0x1000
loop_clear:
ld (hl), #' '
inc hl
dec de
ld a, d
or e
jp nz, loop_clear

ld hl, #0xF080
ld a, #0
ld b, #32
loop0:
inc hl
ld (hl), a
inc hl
inc a
djnz loop0

ld hl, #0xF180
ld b, #32
loop1:
inc hl
ld (hl), a
inc hl
inc a
djnz loop1

ld hl, #0xF280
ld b, #32
loop2:
inc hl
ld (hl), a
inc hl
inc a
djnz loop2

ld hl, #0xF380
ld b, #32
loop3:
inc hl
ld (hl), a
inc hl
inc a
djnz loop3

ld a, #0
out (#0), a
di
halt
.area _DATA (ABS)
