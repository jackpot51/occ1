ld hl, #0xFFFF
ld (hl), #'H'
ld (hl), #'E'
ld (hl), #'L'
ld (hl), #'L'
ld (hl), #'O'
ld (hl), #' '
ld (hl), #'W'
ld (hl), #'O'
ld (hl), #'R'
ld (hl), #'L'
ld (hl), #'D'
ld (hl), #'\n'
ld a, #0
out (#0), a
di
halt
.area _DATA (ABS)