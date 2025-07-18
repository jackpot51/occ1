#include <stdio.h>
#include <string.h>
#include "common.h"

//TODO: use default FCB (BIOS + 0x5C)?
#define FCB_ADDR 0x3000
struct FCB *fcb;

//TODO: initializers are broke!
#define DATA_ADDR 0x4000
uint8_t *data;
#define DATA_SIZE (31 * 1024) 
// How much data to fill when running out
#define DATA_FILL_EMPTY (1 * 1024)
// How much data to fill when replacing delays
#define DATA_FILL_STREAM (30 * 1024)
// Read from disk if frame delay is at least this number
#define STREAM_FRAMES 2
int fill_res = 0;
int head = 0;
int tail = 0;

//TODO: prevent overflow?
int fill(void) {
    if (fill_res != 0) {
        return fill_res;
    }
    int i = tail;
    if ((i + 128) > DATA_SIZE) {
        i = 0;
    }
    memset(&data[i], 0, 128);
    fill_res = fread(fcb, &data[i]);
    if (fill_res != 0) {
        return fill_res;
    }
    tail = i + 128;
    if (tail >= DATA_SIZE) {
        tail = 0;
    }
    return 0;
}

int remaining(void) {
    if (tail >= head) {
        return tail - head;
    } else {
        return (tail + DATA_SIZE) - head;
    }
}

int take(void) {
    if (head == tail) {
        return -1;
    }
    uint8_t byte = data[head];
    head++;
    while (head >= DATA_SIZE) {
        head -= DATA_SIZE;
    }
    return (int)byte;
}

void main(void) {
    int res;

    printf("setting up buffers\r\n");

    fcb = (struct FCB *)FCB_ADDR;
    printf("fcb at %p\r\n");
    memset(fcb, 0, sizeof(struct FCB));
    //TODO: get the file name from command line?
    fcb->filename[0] = 'S';
    fcb->filename[1] = 'W';
    fcb->filename[2] = '1';
    fcb->filename[3] = ' ';
    fcb->filename[4] = ' ';
    fcb->filename[5] = ' ';
    fcb->filename[6] = ' ';
    fcb->filename[7] = ' ';
    fcb->filetype[0] = 'A';
    fcb->filetype[1] = 'M';
    fcb->filetype[2] = 'V';

    data = (uint8_t *)DATA_ADDR;
    printf("data at %p\r\n", data);
    memset(data, 0, DATA_SIZE);
    fill_res = 0;
    head = 0;
    tail = 0;

    printf("opening file\x1BT\r");
    res = fopen(fcb);
    if (res == 0xFF) {
        printf("fopen failed: %d\x1BT\r\n", res);
        exit();
    }

    clear_screen();
    screen_position(0, 0);
    cursor_position(0, 23);

    // Fill at start
    res = remaining();
    while (res < DATA_FILL_STREAM) {
        res = fill();
        if (res != 0) {
            printf("fill error %d\x1BT\r", res);
            break;
        }
        res = remaining();
        printf("%05d\r", res);
    }

    int off = 5 * 128;
    int i = off;
    uint8_t last = ' ';
    uint8_t * vram = (uint8_t *)VRAM;
    for (;;) {
        res = take();
        if (res < 0) {
            if (fill_res != 0) {
                // End of file
                break;
            }

            // Fill when out of data
            res = remaining();
            while (res < DATA_FILL_EMPTY) {
                res = fill();
                if (res != 0) {
                    printf("fill error %d\x1BT\r", res);
                    break;
                }
                res = remaining();
                printf("%05d\r", res);
            }
        }
        uint8_t byte = (uint8_t)res;
        //TODO: optimize with asm?
        if (byte & 0x80) {
            // Commands
            if (byte & 0x40) {
                // Set X
                byte &= 0x3F;
                i &= 0xFF80;
                i |= (uint16_t)byte;
            } else if (byte & 0x20) {
                // Set Y
                byte &= 0x1F;
                i = off + (((int)byte) << 7);
            } else {
                // Delay
                byte &= 0x1F;
                i = off;
                // If delay is long enough, try to fill instead
                //TODO: get accurate timing using IRQ1
                if (byte < STREAM_FRAMES) {
                    // For debugging
                    res = remaining();
                    printf("%05d\r", res);
                }
                while (byte >= STREAM_FRAMES) {
                    res = remaining();
                    if (res < DATA_FILL_STREAM) {
                        //TODO: use result from fill?
                        fill();
                        res = remaining();
                        printf("%05d\r", res);
                        byte -= STREAM_FRAMES;
                    } else {
                        break;
                    }
                }

                for (; byte > 0; byte--) {
                    // Video is at 15 Hz, so four video frames each osborne frame
                    delay_frame();
                    delay_frame();
                    delay_frame();
                    delay_frame();
                }
            }
        } else if (byte == 0) {
            // End of file
            break;
        } else if (byte & 0xE0) {
            // Normal byte
            vram[i] = byte;
            i += 1;
            last = byte;
        } else {
            // Repeat
            for (; byte > 0; byte--) {
                vram[i] = last;
                i += 1;
            }
        }
    }

    fclose(fcb);
    exit();
}