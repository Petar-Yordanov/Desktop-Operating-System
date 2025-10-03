#include "pit.h"
#include "io.h"
#include "pic.h"
#include "irq.h"
#include "cpu.h"

static volatile uint64_t g_ticks = 0;

static void pit_irq_handler(void) { g_ticks++; }

uint64_t pit_ticks(void) { return g_ticks; }

void pit_init(uint32_t hz) {
    if (hz == 0) hz = 100;
    if (hz > PIT_INPUT_HZ) hz = PIT_INPUT_HZ;

    uint32_t div = PIT_INPUT_HZ / hz;
    if (div == 0) div = 1;
    if (div > 0xFFFF) div = 0xFFFF;

    outb(PIT_CMD, 0x36);
    outb(PIT_CH0, (uint8_t)(div & 0xFF));
    outb(PIT_CH0, (uint8_t)(div >> 8));

    irq_init_handler(0, pit_irq_handler);
}

void sleep_ms(uint32_t ms) {
    uint64_t target = pit_ticks() + ms;
    while (pit_ticks() < target) {
        halt();
    }
}