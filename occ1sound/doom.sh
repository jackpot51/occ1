#!/usr/bin/env bash

set -ex

cargo build --release

function note {
    target/release/occ1sound $1 $2
}

C2=65
Db2=69
D2=73
E2=82
F2=87
G2=98
A2=110
Bb2=117
B2=123

C3=130
Db3=139
D3=147
Eb3=156
E3=165
F3=175
G3=196
Ab3=208
A3=220
B3=247

C4=262
Db4=277
D4=294
E4=330
F4=349
G4=392
A4=440
B4=494

C5=523
D5=587
E5=659
F5=698
G5=784
A5=880
B5=988

BPM=240
QUARTER=$((60000 / $BPM))
HALF=$(($QUARTER * 2))
EIGHTH=$(($QUARTER / 2))
SIXTEENTH=$(($EIGHTH / 2))

note $E2 $EIGHTH
note $E2 $EIGHTH
note $E3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $D3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $C3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $Bb2 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $B2 $EIGHTH
note $C3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $E3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $D3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $C3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $Bb2 $HALF

note $E2 $EIGHTH
note $E2 $EIGHTH
note $E3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $D3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $C3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $Bb2 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $B2 $EIGHTH
note $C3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $E3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $D3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH

note $B3 $SIXTEENTH
note $G3 $SIXTEENTH
note $E3 $SIXTEENTH
note $G3 $SIXTEENTH
note $B3 $SIXTEENTH
note $G3 $SIXTEENTH
note $B3 $SIXTEENTH
note $E4 $SIXTEENTH
note $B3 $SIXTEENTH
note $G3 $SIXTEENTH
note $B3 $SIXTEENTH
note $G3 $SIXTEENTH
note $B3 $SIXTEENTH
note $E4 $SIXTEENTH
note $G4 $SIXTEENTH
note $B4 $SIXTEENTH

note $A2 $EIGHTH
note $A2 $EIGHTH
note $A3 $EIGHTH

note $A2 $EIGHTH
note $A2 $EIGHTH
note $G3 $EIGHTH

note $A2 $EIGHTH
note $A2 $EIGHTH
note $F3 $EIGHTH

note $A2 $EIGHTH
note $A2 $EIGHTH
note $Eb3 $EIGHTH

note $A2 $EIGHTH
note $A2 $EIGHTH
note $E3 $EIGHTH
note $F3 $EIGHTH

note $A2 $EIGHTH
note $A2 $EIGHTH
note $A3 $EIGHTH

note $A2 $EIGHTH
note $A2 $EIGHTH
note $G3 $EIGHTH

note $A2 $EIGHTH
note $A2 $EIGHTH
note $F3 $EIGHTH

note $A2 $EIGHTH
note $A2 $EIGHTH
note $Eb3 $HALF

note $A2 $EIGHTH
note $A2 $EIGHTH
note $A3 $EIGHTH

note $A2 $EIGHTH
note $A2 $EIGHTH
note $G3 $EIGHTH

note $A2 $EIGHTH
note $A2 $EIGHTH
note $F3 $EIGHTH

note $A2 $EIGHTH
note $A2 $EIGHTH
note $Eb3 $EIGHTH

note $A2 $EIGHTH
note $A2 $EIGHTH
note $E3 $EIGHTH
note $F3 $EIGHTH

note $A2 $EIGHTH
note $A2 $EIGHTH
note $A3 $EIGHTH

note $A2 $EIGHTH
note $A2 $EIGHTH
note $G3 $EIGHTH

note $A2 $EIGHTH
note $A2 $EIGHTH

note $A4 $SIXTEENTH
note $E4 $SIXTEENTH
note $E4 $SIXTEENTH
note $A4 $SIXTEENTH
note $E4 $SIXTEENTH
note $C4 $SIXTEENTH
note $E4 $SIXTEENTH
note $A4 $SIXTEENTH
note $C5 $SIXTEENTH
note $A4 $SIXTEENTH
note $E4 $SIXTEENTH
note $A4 $SIXTEENTH
note $E4 $SIXTEENTH
note $A4 $SIXTEENTH
note $E4 $SIXTEENTH
note $C4 $SIXTEENTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $E3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $D3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $C3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $Bb2 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $B2 $EIGHTH
note $C3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $E3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $D3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $C3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $Bb2 $HALF

note $E2 $EIGHTH
note $E2 $EIGHTH
note $E3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $D3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $C3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $Bb2 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $B2 $EIGHTH
note $C3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $E3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $D3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $C3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $Bb2 $HALF

note $Db3 $EIGHTH
note $Db3 $EIGHTH
note $Db4 $EIGHTH

note $Db3 $EIGHTH
note $Db3 $EIGHTH
note $B3 $EIGHTH

note $Db3 $EIGHTH
note $Db3 $EIGHTH
note $A3 $EIGHTH

note $Db3 $EIGHTH
note $Db3 $EIGHTH
note $G3 $EIGHTH

note $Db3 $EIGHTH
note $Db3 $EIGHTH
note $Ab3 $EIGHTH
note $A3 $EIGHTH

note $B2 $EIGHTH
note $B2 $EIGHTH
note $B3 $EIGHTH

note $B2 $EIGHTH
note $B2 $EIGHTH
note $A3 $EIGHTH

note $B2 $EIGHTH
note $B2 $EIGHTH
note $G3 $EIGHTH

note $A2 $EIGHTH
note $A2 $EIGHTH
note $F3 $HALF

note $E2 $EIGHTH
note $E2 $EIGHTH
note $E3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $D3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $C3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $Bb2 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $B2 $EIGHTH
note $C3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $E3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH
note $D3 $EIGHTH

note $E2 $EIGHTH
note $E2 $EIGHTH

note $G4 $SIXTEENTH
note $B4 $SIXTEENTH
note $E4 $SIXTEENTH
note $B3 $SIXTEENTH
note $G4 $SIXTEENTH
note $E4 $SIXTEENTH
note $B4 $SIXTEENTH
note $G4 $SIXTEENTH
note $B4 $SIXTEENTH
note $G4 $SIXTEENTH
note $E4 $SIXTEENTH
note $B3 $SIXTEENTH
note $G4 $SIXTEENTH
note $B4 $SIXTEENTH
note $E5 $SIXTEENTH
note $G5 $SIXTEENTH
