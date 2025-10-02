#include "idt.h"

void idt_init(void) {
    idtp.limit = sizeof(idt) - 1;
    idtp.base  = (uint32_t)&idt;

    for (int i = 0; i < 256; ++i)
        idt_set_gate(i, 0, 0, 0);

    idt_flush(&idtp);
}

void idt_set_gate(int num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_low = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;

    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags; // 0x8E = present, ring 0, 32-bit gate
}

void idt_flush(const struct idt_ptr* idtp_arg)
{
    __asm__ __volatile__ ("lidt (%0)" :: "r"(idtp_arg) : "memory");
}