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

void main(void) {
    //delay_ms(1000);
    //return;

    clear_screen();

    puts("CP/M Physics");

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
        ball->ay = (1 << 8) / 8;
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

    for(int frame = 0; frame < FRAMERATE * 10; frame++) {
        // Clear old balls
        for (int i = 0; i < BALLS; i++) {
            struct Ball * ball = &balls[i];

            cursor_position((ball->x >> 8), (ball->y >> 8));
            putchar(' ');
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
            cursor_position((ball->x >> 8), (ball->y >> 8));
            putchar(ball->c);
        }

        cursor_position(13, 0);

        char c = getchar();
        if (c == 'q') {
            break;
        }

        delay_frame();
    }

    clear_screen();

    exit();
}
