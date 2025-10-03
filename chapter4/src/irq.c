#include "irq.h"
#include "pic.h"

static irq_handler_t handlers[16] = {0};

void irq_init_handler(int n, irq_handler_t h) {
    if (n >= 0 && n < 16) handlers[n] = h;
}
void irq_deinit_handler(int n) {
    if (n >= 0 && n < 16) handlers[n] = 0;
}

void irq_dispatch(uint32_t irq) {
    if (irq < 16 && handlers[irq]) {
        handlers[irq]();
    }

    pic_send_eoi((int)irq);
}

#define KDATA_SEL 0x10
#define STR_(x) #x
#define STR(x) STR_(x)

#define GEN_IRQ_STUB(N)                                                     \
__attribute__((naked)) void irq##N(void) {                                  \
    __asm__ __volatile__(                                                   \
        "mov %%ds, %%ax\n\t"                                                \
        "pushl %%eax\n\t"                                                   \
        "mov %%es, %%ax\n\t"                                                \
        "pushl %%eax\n\t"                                                   \
        "mov %%fs, %%ax\n\t"                                                \
        "pushl %%eax\n\t"                                                   \
        "mov %%gs, %%ax\n\t"                                                \
        "pushl %%eax\n\t"                                                   \
        "pusha\n\t"                                                         \
        "mov $" STR(KDATA_SEL) ", %%ax\n\t"                                 \
        "mov %%ax, %%ds\n\t"                                                \
        "mov %%ax, %%es\n\t"                                                \
        "push $" #N "\n\t"                                                  \
        "call irq_dispatch\n\t"                                             \
        "add $4, %%esp\n\t"                                                 \
        "popa\n\t"                                                          \
        "popl %%eax\n\t"                                                    \
        "mov %%ax, %%gs\n\t"                                                \
        "popl %%eax\n\t"                                                    \
        "mov %%ax, %%fs\n\t"                                                \
        "popl %%eax\n\t"                                                    \
        "mov %%ax, %%es\n\t"                                                \
        "popl %%eax\n\t"                                                    \
        "mov %%ax, %%ds\n\t"                                                \
        "iretl\n\t"                                                         \
        : : : "eax","ecx","edx","ebx","ebp","esi","edi","memory"            \
    );                                                                      \
}

GEN_IRQ_STUB(0)  GEN_IRQ_STUB(1)  GEN_IRQ_STUB(2)  GEN_IRQ_STUB(3)
GEN_IRQ_STUB(4)  GEN_IRQ_STUB(5)  GEN_IRQ_STUB(6)  GEN_IRQ_STUB(7)
GEN_IRQ_STUB(8)  GEN_IRQ_STUB(9)  GEN_IRQ_STUB(10) GEN_IRQ_STUB(11)
GEN_IRQ_STUB(12) GEN_IRQ_STUB(13) GEN_IRQ_STUB(14) GEN_IRQ_STUB(15)
