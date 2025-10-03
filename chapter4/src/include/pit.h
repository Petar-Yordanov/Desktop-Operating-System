#ifndef PIT_H
#define PIT_H

#include "types.h"

#define PIT_CH0       0x40
#define PIT_CMD       0x43
#define PIT_INPUT_HZ  1193182u

void pit_init(uint32_t hz);
uint64_t pit_ticks(void);
void sleep_ms(uint32_t ms);

#endif