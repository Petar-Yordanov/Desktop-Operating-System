#include "types.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "vga.h"
#include "pic.h"
#include "pit.h"
#include "cpu.h"

void _main(const void* mbi, unsigned int magic){
    (void)mbi; (void)magic;
    clear();
    puts("MicrOS starting...\n");

    gdt_init();
    puts("GDT initialized\n");

    idt_init();
    puts("IDT initialized\n");

    isr_init();
    puts("ISRs initialized\n");

    idt_init_irqs();
    puts("IDT IRQ gates initialized\n");

    pic_init();
    puts("PIC initialized\n");

    pit_init(1000);
    puts("PIT initialized\n");

    enable_interrupts();
    puts("Interrupts enabled\n");

    for (;;) {
        sleep_ms(1000);
        puts("tick\n");
    }

    uint64_t last = pit_ticks();
    for (;;) {
        uint64_t t = pit_ticks();
        if (t - last >= 1000) {
            last = t;
            puts("tick\n");
        }
        halt();
    }
}
