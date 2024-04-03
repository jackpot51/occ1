#include "common.c"

struct Player {
    int16_t x;
    int16_t y;
    uint8_t c;
    uint8_t chips;
    uint8_t needs_chips;
    uint8_t blues;
    uint8_t reds;
    uint8_t greens;
    uint8_t yellows;
};

/*
void draw_index(void) {
    uint8_t * vram = (uint8_t *)VRAM;
    for (uint16_t i = 0; i < 0x80; i++) {
        uint16_t y = ((i / 16) + 1) * 2;
        uint16_t x = ((i % 16) + 1) * 2;
        vram[y * 128 + x] = (uint8_t)i;

        // Draw index
        if (i < 8) {
            vram[x * 128] = (uint8_t)i + '0';
        }
        if (i < 10) {
            vram[x] = (uint8_t)i + '0';
        } else if (i < 16) {
            vram[x] = (uint8_t)(i - 0xA) + 'A';
        }
    }
}
*/

void draw_level(struct Player * player, char * level) {
    uint8_t * vram = (uint8_t *)VRAM;
    uint16_t x = 0;
    uint16_t y = 0;
    for (uint16_t i = 0; i < 4096; i++) {
        char c = level[i];
        switch (c) {
            case 0:
                return;
            case '\n':
                x = 0;
                y += 1;
                break;
            case '_':
                player->x = x;
                player->y = y;
                vram[y * 128 + x] = player->c;
                x += 1;
                break;
            default:
                vram[y * 128 + x] = c;
                x += 1;
                break;
        }
    }
}

uint8_t move_dirt(int16_t dirt_x, int16_t dirt_y, int16_t dx, int16_t dy) {
    int16_t x = dirt_x + dx;
    if ((x < 0) || (x >= COLS)) return;
    int16_t y = dirt_y + dy;
    if ((y < 0) || (y >= ROWS)) return;

    uint8_t * vram = (uint8_t *)VRAM;
    uint8_t c = vram[y * 128 + x];
    switch (c) {
        case ' ':
            vram[dirt_y * 128 + dirt_x] = ' ';
            vram[y * 128 + x] = 'D';
            return 1;
        case '~':
            vram[dirt_y * 128 + dirt_x] = ' ';
            vram[y * 128 + x] = 'd';
            return 1;
        default:
            return 0;
    }
}

void move_player(struct Player * player, int16_t dx, int16_t dy) {
    int16_t x = player->x + dx;
    if ((x < 0) || (x >= COLS)) return;
    int16_t y = player->y + dy;
    if ((y < 0) || (y >= ROWS)) return;

    uint8_t * vram = (uint8_t *)VRAM;
    uint8_t c = vram[y * 128 + x];
    switch (c) {
        case ' ':
            break;
        case '@':
            // Cheap marker for going to next level
            player->needs_chips = 0;
            break;
        case '$':
            player->chips += 1;
            break;
        case 'H':
            if (player->chips < player->needs_chips) return;
            break;
        case 'b':
            player->blues += 1;
            break;
        case 'B':
            if (player->blues == 0) return;
            player->blues -= 1;
            break;
        case 'r':
            player->reds += 1;
            break;
        case 'R':
            if (player->reds == 0) return;
            player->reds -= 1;
            break;
        case 'g':
            player->greens += 1;
            break;
        case 'G':
            if (player->greens == 0) return;
            // Green keys can open any green locks
            break;
        case 'y':
            player->yellows += 1;
            break;
        case 'Y':
            if (player->yellows == 0) return;
            player->yellows -= 1;
            break;
        case 'd':
            break;
        case 'D':
            if (!move_dirt(x, y, dx, dy)) return;
            break;
        default:
            return;
    }

    vram[player->y * 128 + player->x] = ' ';
    player->x = x;
    player->y = y;
    vram[player->y * 128 + player->x] = player->c;
}

void reset_player(struct Player * player, uint8_t needs_chips) {
    player->x = 0;
    player->y = 0;
    player->c = 0x8C; // underlined plus symbol
    player->chips = 0;
    player->needs_chips = needs_chips;
    player->blues = 0;
    player->reds = 0;
    player->greens = 0;
    player->yellows = 0;
}

void level1(struct Player * player) {
    reset_player(player, 11);
    draw_level(player,
"                 \n"
"                 \n"
"    ##### #####  \n"
"    #   ###   #  \n"
"    # $ #@# $ #  \n"
"  #####G#H#G#####\n"
"  # y B     R y #\n"
"  # $ #b   r# $ #\n"
"  #####$ _ $#####\n"
"  # $ #b   r# $ #\n"
"  #   R  $  B   #\n"
"  ######Y#Y######\n"
"      #  #  #    \n"
"      # $#$ #    \n"
"      #  #g #    \n"
"      #######    \n"
    );
}

void level2(struct Player * player) {
    reset_player(player, 4);
    //TODO: bugs
    draw_level(player,
"                    \n"
"                    \n"
"    #######         \n"
"    #  $  #         \n"
"    #     #         \n"
"    #  #  ##########\n"
"  ###  #   ~~     $#\n"
"  #@H  ##  ~~ DD_  #\n"
"  ###  #   ~~     $#\n"
"    #  #  ##########\n"
"    #     #         \n"
"    #  $  #         \n"
"    #######         \n"
    );
}

void main(void) {
    //TODO: global variables are not initializing properly
    struct Player player = { 0 };

    uint8_t level = 0;
    uint8_t running = 1;
    while(running) {
        if (player.needs_chips == 0) {
            clear_screen();
            level += 1;
            switch(level) {
                case 1:
                    level1(&player);
                    break;
                case 2:
                    level2(&player);
                    break;
                default:
                    puts("Finished all levels\n");
                    running = 0;
                    break;
            }
        }

        char c = getchar();
        switch (c) {
            case 'w':
                move_player(&player, 0, -1);
                break;
            case 'a':
                move_player(&player, -1, 0);
                break;
            case 's':
                move_player(&player, 0, 1);
                break;
            case 'd':
                move_player(&player, 1, 0);
                break;
            case 'l':
                player.needs_chips = 0;
                break;
            case 0x1B:
                running = 0;
                break;
        }
    }

    exit();
}
