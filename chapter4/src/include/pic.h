#ifndef PIC_H
#define PIC_H

#include "types.h"

// PIC I/O ports
#define PIC1_CMD  0x20
#define PIC1_DATA 0x21
#define PIC2_CMD  0xA0
#define PIC2_DATA 0xA1

// ICW/OCW bits
#define PIC_ICW1_INIT  0x10
#define PIC_ICW1_ICW4  0x01
#define PIC_ICW4_8086  0x01
#define PIC_EOI        0x20

void pic_remap(uint8_t offset1, uint8_t offset2);
void pic_set_mask(uint8_t irq_line);
void pic_clear_mask(uint8_t irq_line);
void pic_send_eoi(int irq);
void pic_init(void);

#endif