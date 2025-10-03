#include "idt.h"
#include "irq.h"

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

void idt_flush(const struct idt_ptr* idtp_arg) {
    __asm__ __volatile__ ("lidt (%0)" :: "r"(idtp_arg) : "memory");
}

void idt_init_irqs(void) {
    idt_set_gate(0x20, (uintptr_t)irq0,  0x08, 0x8E);
    idt_set_gate(0x21, (uintptr_t)irq1,  0x08, 0x8E);
    idt_set_gate(0x22, (uintptr_t)irq2,  0x08, 0x8E);
    idt_set_gate(0x23, (uintptr_t)irq3,  0x08, 0x8E);
    idt_set_gate(0x24, (uintptr_t)irq4,  0x08, 0x8E);
    idt_set_gate(0x25, (uintptr_t)irq5,  0x08, 0x8E);
    idt_set_gate(0x26, (uintptr_t)irq6,  0x08, 0x8E);
    idt_set_gate(0x27, (uintptr_t)irq7,  0x08, 0x8E);
    idt_set_gate(0x28, (uintptr_t)irq8,  0x08, 0x8E);
    idt_set_gate(0x29, (uintptr_t)irq9,  0x08, 0x8E);
    idt_set_gate(0x2A, (uintptr_t)irq10, 0x08, 0x8E);
    idt_set_gate(0x2B, (uintptr_t)irq11, 0x08, 0x8E);
    idt_set_gate(0x2C, (uintptr_t)irq12, 0x08, 0x8E);
    idt_set_gate(0x2D, (uintptr_t)irq13, 0x08, 0x8E);
    idt_set_gate(0x2E, (uintptr_t)irq14, 0x08, 0x8E);
    idt_set_gate(0x2F, (uintptr_t)irq15, 0x08, 0x8E);
}
