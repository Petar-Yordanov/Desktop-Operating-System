#ifndef ISR_H
#define ISR_H

#include "types.h"
#include "vga.h"

#define KERNEL_CS 0x08

#define IDT_FLAG_GATE32   0x0E
#define IDT_FLAG_PRESENT  0x80
#define IDT_FLAG_DPL0     0x00
#define IDT_FLAGS_INT_KRN (IDT_FLAG_PRESENT | IDT_FLAG_DPL0 | IDT_FLAG_GATE32)

enum {
    VEC_DE = 0,   /* #DE Divide Error */
    VEC_DB = 1,   /* #DB Debug */
    VEC_NMI= 2,   /* NMI */
    VEC_BP = 3,   /* #BP Breakpoint */
    VEC_OF = 4,   /* #OF Overflow */
    VEC_BR = 5,   /* #BR BOUND Range Exceeded */
    VEC_UD = 6,   /* #UD Invalid Opcode */
    VEC_NM = 7,   /* #NM Device Not Available */
    VEC_DF = 8,   /* #DF Double Fault (err=0) */
    VEC_OLD_X87 = 9,  /* Coprocessor Segment Overrun (obsolete) */

    VEC_TS = 10,  /* #TS Invalid TSS */
    VEC_NP = 11,  /* #NP Segment Not Present */
    VEC_SS = 12,  /* #SS Stack-Segment Fault */
    VEC_GP = 13,  /* #GP General Protection */
    VEC_PF = 14,  /* #PF Page Fault */
    VEC_RES15 = 15, /* reserved */

    VEC_MF = 16,  /* #MF x87 FPU Floating-Point Error */
    VEC_AC = 17,  /* #AC Alignment Check */
    VEC_MC = 18,  /* #MC Machine Check */
    VEC_XM = 19,  /* #XM SIMD Floating-Point */

    /* 20..31: reserved */
    VEC_VE = 20,
    VEC_CP = 21,
    VEC_22 = 22,
    VEC_23 = 23,
    VEC_24 = 24,
    VEC_25 = 25,
    VEC_26 = 26,
    VEC_27 = 27,
    VEC_28 = 28,
    VEC_29 = 29,
    VEC_30 = 30,
    VEC_31 = 31
};

struct interrupt_frame {
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
};

void isr_init(void);


#define ISR_NOERR(n, name) \
__attribute__((interrupt)) \
static void isr_##n(struct interrupt_frame* frame){ (void)frame; \
    puts(name); puts("\n"); \
    if ((n)==VEC_BP) return; /* let #BP continue */ \
    for(;;) __asm__ __volatile__("hlt"); }

#define ISR_ERR(n, name) \
__attribute__((interrupt)) \
static void isr_##n(struct interrupt_frame* frame, uint32_t err){ \
    (void)frame; (void)err; \
    puts(name); puts("\n"); \
    for(;;) __asm__ __volatile__("hlt"); }

#endif
