#include <stdint.h>
#include "isr.h"
#include "idt.h"
#include "vga.h"

ISR_NOERR(0,  "#DE Divide Error")
ISR_NOERR(1,  "#DB Debug")
ISR_NOERR(2,  "NMI Interrupt")
ISR_NOERR(3,  "#BP Breakpoint")
ISR_NOERR(4,  "#OF Overflow")
ISR_NOERR(5,  "#BR Bound Range Exceeded")
ISR_NOERR(6,  "#UD Invalid Opcode")
ISR_NOERR(7,  "#NM Device Not Available")
ISR_ERR  (8,  "#DF Double Fault")
ISR_NOERR(9,  "Reserved/Old x87 Segment Overrun (9)")
ISR_ERR  (10, "#TS Invalid TSS")
ISR_ERR  (11, "#NP Segment Not Present")
ISR_ERR  (12, "#SS Stack-Segment Fault")
ISR_ERR  (13, "#GP General Protection")
ISR_ERR  (14, "#PF Page Fault")
ISR_NOERR(15, "Reserved (15)")
ISR_NOERR(16, "#MF x87 Floating-Point Error")
ISR_ERR  (17, "#AC Alignment Check")
ISR_NOERR(18, "#MC Machine Check")
ISR_NOERR(19, "#XM SIMD Floating-Point")
/* 20..31 reserved: make them safe no-err */
ISR_NOERR(20, "Reserved (20)")
ISR_NOERR(21, "Reserved (21)")
ISR_NOERR(22, "Reserved (22)")
ISR_NOERR(23, "Reserved (23)")
ISR_NOERR(24, "Reserved (24)")
ISR_NOERR(25, "Reserved (25)")
ISR_NOERR(26, "Reserved (26)")
ISR_NOERR(27, "Reserved (27)")
ISR_NOERR(28, "Reserved (28)")
ISR_NOERR(29, "Reserved (29)")
ISR_NOERR(30, "Reserved (30)")
ISR_NOERR(31, "Reserved (31)")

static const void* isr_func[32] = {
    isr_0,  isr_1,  isr_2,  isr_3,  isr_4,  isr_5,  isr_6,  isr_7,
    isr_8,  isr_9, isr_10, isr_11, isr_12, isr_13, isr_14, isr_15,
    isr_16, isr_17, isr_18, isr_19, isr_20, isr_21, isr_22, isr_23,
    isr_24, isr_25, isr_26, isr_27, isr_28, isr_29, isr_30, isr_31
};

void isr_init(void){
    for (int vec = 0; vec < 32; vec++){
        if (isr_func[vec])
            idt_set_gate(vec, (uint32_t)isr_func[vec], KERNEL_CS, IDT_FLAGS_INT_KRN);
    }
}