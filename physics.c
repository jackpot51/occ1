#include <stdio.h>
#include "common.h"

#define BOX_LEFT 0
#define BOX_RIGHT 51
#define BOX_TOP 2
#define BOX_BOTTOM 23

struct Ball {
    char c;
    int16_t x;
    int16_t y;
    int16_t vx;
    int16_t vy;
    int16_t ax;
    int16_t ay;
};

#define BALLS 3

void draw_char(char c, int16_t x, int16_t y) {
    if (x >= 0 && y >= 0) {
        uint8_t * vram = (uint8_t *)(VRAM + y * 128 + x);
        *vram = c;
    }
}

//TODO: support wrap and newline?
void draw_string(char * s, int16_t x, int16_t y) {
    char c;
    while (c = *s++) {
        draw_char(c, x++, y);
    }
}

void main(void) {
    clear_screen();

    draw_string("CP/M Physics", 0, 0);

    struct Ball balls[BALLS];

    // Initialize balls
    for (int i = 0; i < BALLS; i++) {
        struct Ball * ball = &balls[i];
        ball->c = 'o';
        ball->x = 0;
        ball->y = 0;
        ball->vx = 0;
        ball->vy = 0;
        ball->ax = 0;
        ball->ay = (1 << 8) / 16;
    }

    balls[0].c = 'o';
    balls[0].x = (4 << 8);
    balls[0].y = (4 << 8);
    balls[0].vx = (1 << 8);

    balls[1].c = 'O';
    balls[1].x = (8 << 8);
    balls[1].y = (8 << 8);
    balls[1].vx = -(1 << 8);

    balls[2].c = '0';
    balls[2].x = (12 << 8);
    balls[2].y = (12 << 8);
    balls[2].vx = (1 << 8);

    while (1) {
        // Clear old balls
        for (int i = 0; i < BALLS; i++) {
            struct Ball * ball = &balls[i];

            draw_char(' ', (ball->x >> 8), (ball->y >> 8));
        }

        // Update and draw new balls
        for (int i = 0; i < BALLS; i++) {
            struct Ball * ball = &balls[i];

            // Calculate new ball position
            ball->x += ball->vx;
            ball->y += ball->vy;

            // Bounce ball off walls
            if (ball->x <= (BOX_LEFT << 8) || ball->x >= (BOX_RIGHT << 8)) {
                ball->vx = -ball->vx;
                ball->x += ball->vx;
            }
            if (ball->y <= (BOX_TOP << 8) || ball->y >= (BOX_BOTTOM << 8)) {
                ball->vy = -ball->vy;
                ball->y += ball->vy;
            }

            // Calculate new ball velocity
            ball->vx += ball->ax;
            ball->vy += ball->ay;

            // Print new ball
            draw_char(ball->c, (ball->x >> 8), (ball->y >> 8));
        }

        char c = getchar();
        if (c == 'q' || c == 0x1B) {
            break;
        } else if (c != 0) {
            draw_char(c, 13, 0);
        }

        delay_frame();
    }

    clear_screen();

    exit();
}
