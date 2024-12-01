#include <stdint.h>

uint8_t read_port(uint16_t port);
void write_port(uint16_t port, uint8_t data);

void irq1_override(void);
extern uint16_t irq1_count;
extern uint16_t irq1_program;
