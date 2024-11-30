#include <stdint.h>

#define COLS 52
#define ROWS 24
#define VRAM 0xF000

void exit(void);
int getchar(void);
int putchar(char c);
void clear_screen(void);
void cursor_position(uint8_t x, uint8_t y);

// OSBORNE 1: 4 MHz, runs delay loop in 24 clocks
// Run emulator at 4 Mhz and 6 clocks per instruction to match!
#define CLOCKS_PER_S 4000000
#define CLOCKS_PER_LOOP 24
#define LOOPS_PER_S (CLOCKS_PER_S / CLOCKS_PER_LOOP)
#define FRAMERATE 60
#define LOOPS_PER_FRAME (LOOPS_PER_S / FRAMERATE)
#define LOOPS_PER_MS (LOOPS_PER_S / 1000)

void delay_loops(uint16_t loops) __sdcccall(0);
void delay_frame(void);
void delay_ms(void);
