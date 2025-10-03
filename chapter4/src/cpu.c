#include "cpu.h"

void enable_interrupts(void) {
    __asm__ __volatile__("sti");
}

void disable_interrupts(void) {
    __asm__ __volatile__("cli");
}

void halt(void) {
    __asm__ __volatile__("hlt");
}
