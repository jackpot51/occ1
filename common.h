#include <stdint.h>

/* CONSOLE FUNCTIONS */

#define COLS 52
#define ROWS 24
#define VRAM 0xF000

void exit(void);
int getchar(void);
int putchar(char c);
void clear_screen(void);
void cursor_position(uint8_t x, uint8_t y);
void screen_position(uint8_t x, uint8_t y);

/* FILE FUNCTIONS */

struct FCB {
    uint8_t drive;
    uint8_t filename[8];
    uint8_t filetype[3];
    uint8_t extent;
    uint8_t s1;
    uint8_t s2;
    uint8_t rec_count;
    uint8_t rec_map[16];
    uint8_t current_rec;
    uint8_t rand_acc_rec[3];
};

int fopen(struct FCB * fcb);
int fclose(struct FCB * fcb);
int fread(struct FCB * fcb, uint8_t buf[128]);

/* TIMING FUNCTIONS */

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

