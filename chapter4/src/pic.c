#include "pic.h"
#include "io.h"

static inline uint8_t _get_mask(uint16_t data_port) {
    return inb(data_port);
}
static inline void _set_mask(uint16_t data_port, uint8_t val) {
    outb(data_port, val);
    io_wait();
}

void pic_remap(uint8_t offset1, uint8_t offset2) {
    uint8_t m1 = inb(PIC1_DATA);
    uint8_t m2 = inb(PIC2_DATA);

    outb(PIC1_CMD, PIC_ICW1_INIT | PIC_ICW1_ICW4); io_wait();
    outb(PIC2_CMD, PIC_ICW1_INIT | PIC_ICW1_ICW4); io_wait();

    outb(PIC1_DATA, offset1); io_wait();
    outb(PIC2_DATA, offset2); io_wait();

    outb(PIC1_DATA, 0x04); io_wait();
    outb(PIC2_DATA, 0x02); io_wait();

    outb(PIC1_DATA, PIC_ICW4_8086); io_wait();
    outb(PIC2_DATA, PIC_ICW4_8086); io_wait();

    outb(PIC1_DATA, m1); io_wait();
    outb(PIC2_DATA, m2); io_wait();
}

void pic_set_mask(uint8_t irq_line) {
    uint16_t port = (irq_line < 8) ? PIC1_DATA : PIC2_DATA;
    if (irq_line >= 8) irq_line -= 8;
    uint8_t mask = _get_mask(port) | (uint8_t)(1u << irq_line);
    _set_mask(port, mask);
}

void pic_clear_mask(uint8_t irq_line) {
    uint16_t port = (irq_line < 8) ? PIC1_DATA : PIC2_DATA;
    if (irq_line >= 8) irq_line -= 8;
    uint8_t mask = _get_mask(port) & (uint8_t)~(1u << irq_line);
    _set_mask(port, mask);
}

void pic_send_eoi(int irq) {
    if (irq >= 8) outb(PIC2_CMD, PIC_EOI);
    outb(PIC1_CMD, PIC_EOI);
}

void pic_init(void) {
    pic_remap(0x20, 0x28);

    outb(PIC1_DATA, 0xFF); io_wait();
    outb(PIC2_DATA, 0xFF); io_wait();

    pic_clear_mask(0);
}
