ld hl, #0xF000
ld (hl), #'A'
inc hl
ld (hl), #'B'
inc hl
ld (hl), #'C'
inc hl
ld (hl), #'D'
inc hl
ld (hl), #'E'
inc hl
ld (hl), #'F'
inc hl
ld (hl), #'G'
inc hl
ld (hl), #'H'
inc hl
ld (hl), #'I'
inc hl
ld (hl), #'J'
inc hl
ld (hl), #'K'
inc hl
ld (hl), #'L'
inc hl
ld (hl), #'M'
inc hl
ld (hl), #'N'
inc hl
ld (hl), #'O'
inc hl
ld (hl), #'P'
inc hl
ld (hl), #'Q'
inc hl
ld (hl), #'R'
inc hl
ld (hl), #'S'
inc hl
ld (hl), #'T'
inc hl
ld (hl), #'U'
inc hl
ld (hl), #'V'
inc hl
ld (hl), #'W'
inc hl
ld (hl), #'X'
inc hl
ld (hl), #'Y'
inc hl
ld (hl), #'Z'
inc hl
ld (hl), #'a'
inc hl
ld (hl), #'b'
inc hl
ld (hl), #'c'
inc hl
ld (hl), #'d'
inc hl
ld (hl), #'e'
inc hl
ld (hl), #'f'
inc hl
ld (hl), #'g'
inc hl
ld (hl), #'h'
inc hl
ld (hl), #'i'
inc hl
ld (hl), #'j'
inc hl
ld (hl), #'k'
inc hl
ld (hl), #'l'
inc hl
ld (hl), #'m'
inc hl
ld (hl), #'n'
inc hl
ld (hl), #'o'
inc hl
ld (hl), #'p'
inc hl
ld (hl), #'q'
inc hl
ld (hl), #'r'
inc hl
ld (hl), #'s'
inc hl
ld (hl), #'t'
inc hl
ld (hl), #'u'
inc hl
ld (hl), #'v'
inc hl
ld (hl), #'w'
inc hl
ld (hl), #'x'
inc hl
ld (hl), #'y'
inc hl
ld (hl), #'z'
inc hl
ld a, #0
out (#0), a
di
halt
.area _DATA (ABS)