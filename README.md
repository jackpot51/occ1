# occ1
Osbourne 1 Demos

Mame must be installed from https://launchpad.net/~c.falco/+archive/ubuntu/mame

- beep.com plays the DOOM episode 1 mission 1 theme on the bell. I don't know how this will sound on the real hardware, please try to get a recording. The bell has a fixed frequency of 1560 KHz, so this program layers on lower frequencies on top of that by rapidly toggling the bell, which gives a messy sound but should have a distinguishable melody.

- game.com is a port of the first two levels of Chip's Challenge. Use WASD to move, collect lowercase keys (bgry) to unlock uppercase doors (BGRY). Collect all the chips ($) on the map to unlock the socket (H). You can push dirt blocks (D) into water (~), then walk on the sunken dirt block (d) to turn it into ground. Reach the portal (@) to move to the next level, or press the L key to skip. Once all levels are finished or skipped, the game exits.

- image.com shows the Redox OS logo next to a character map. The characters required to draw this do not exist, and the Osborne 1 only has character graphics, so how does it work? It races the beam with very precise timing to ensure that the characters are swapped out exactly when the beam is about to draw the next line. This allows for the selection of individual lines from each character in the character map. A complex program finds the best matching lines from any character in the character set, then generates an assembly program that swaps out characters exactly when the beam has passed that line. That program is then hooked into the VSYNC IRQ, and this is not reversed at this time, so the system must be powered off afterwards.

- physics.com has three balls that move according to gravity and bounce. This was a program I used for testing my delay loop accuracy. Press q to exit.
