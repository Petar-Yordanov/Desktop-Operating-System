#ifndef IRQ_H
#define IRQ_H

#include "types.h"

typedef void (*irq_handler_t)(void);

void irq_init_handler(int irq_number_0_to_15, irq_handler_t handler);
void irq_deinit_handler(int irq_number_0_to_15);

void irq_dispatch(uint32_t irq);

/* 16 IRQ entry points */
void irq0(void);  void irq1(void);  void irq2(void);  void irq3(void);
void irq4(void);  void irq5(void);  void irq6(void);  void irq7(void);
void irq8(void);  void irq9(void);  void irq10(void); void irq11(void);
void irq12(void); void irq13(void); void irq14(void); void irq15(void);

#endif
