#ifdef IO_H
#define IO_H

#include "types.h"

uint8_t inb(uint16_t);
void outb(uint16_t, uint8_t);
void io_wait(void);

#endif IO_H