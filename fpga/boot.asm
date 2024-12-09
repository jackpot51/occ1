ld hl, #0xF000
ld (hl), #'H'
inc hl
ld (hl), #'E'
inc hl
ld (hl), #'L'
inc hl
ld (hl), #'L'
inc hl
ld (hl), #'O'
inc hl
ld (hl), #' '
inc hl
ld (hl), #'W'
inc hl
ld (hl), #'O'
inc hl
ld (hl), #'R'
inc hl
ld (hl), #'L'
inc hl
ld (hl), #'D'
inc hl
ld (hl), #'\n'
ld a, #0
out (#0), a
di
halt
.area _DATA (ABS)