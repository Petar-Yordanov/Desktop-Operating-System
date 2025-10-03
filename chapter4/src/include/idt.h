#ifndef IDT_H
#define IDT_H

#include "types.h"

struct idt_entry {
    uint16_t base_low;
    uint16_t sel;
    uint8_t  always0;
    uint8_t  flags;
    uint16_t base_high;
} __attribute__((packed));

struct idt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

static struct idt_entry idt[256];
static struct idt_ptr idtp;

void idt_init(void);
void idt_set_gate(int num, uint32_t base, uint16_t sel, uint8_t flags);
void idt_flush(const struct idt_ptr* idtp);

#endif