<!-- vim: set colorcolumn=52: -->
<!-- vim: set textwidth=52: -->

# Script for Reborne demo

## Laws of the Demo

- A demo should be long and detailed: procedurally
  generate everything, compress the heck out of it,
  and add tons of filler!
- A demo should push the machine to its limits (and
  inexplicably beyond): use deception, misdirection,
  and slight of hand!

## Techniques

### Racing the beam

**Use character swapping technique to emulate bitmap
graphics**

This technique involves hooking the IRQ1 handler and
carefully timing when the beam scans the first line,
then swapping out the characters before it scans the
next line. By choosing the right characters for each
line, specific pixel patterns can be chosen that
provide something like bitmap graphics at 60 frames
per second. This is limited mianly by how many
instructions the CPU can execute between lines,
which is exactly 256 cycles. Using `ld (hl), #0xXX`
and `inc hl`, this is 14 cycles per byte, which is
17 characters that can be swapped per line. This
provides a resolution of approximately 136 pixels.
In the future, optimizations could push this to the
full 52 character width of the screen, as not all
bytes have to be changed on each line. Additionally,
the dim bit could be used to provide more depth.

### Taming the bell

**Toggle the nominally 1560Hz bell on and off to
make "music"**

The bell, when turned on, generates a square wave
with a frequency of 1560Hz by toggling every five
scanlines. This frequency cannot be changed in
software, but modulating it on and off at the right
frequency does give an audible pitch, as pitch is
equal to rhythm. Noticeable melodies can be
produced, though they will always have a tone of
1560Hz beneath them. When paired with an IRQ1 hook,
there will also be a tone at 60Hz as the bell cannot
be toggled while the CPU is busy filling in the
video RAM. It may be possible to compose music using
only notes that are multiples of 60Hz to provide as
much constructive interference with these two drones
as possible.

## Scenes

### Scene 1: Intro

A nice intro screen to the demo, ASCII art of the
name (REBORNE), and a description of the Osborne 1's
capabilities.  Approach this as a magician, which
means trying to downplay the abilities that will be
showcased later.


