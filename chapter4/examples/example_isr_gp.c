#include "types.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "vga.h"

static void trigger_gp(void) {
    __asm__ __volatile__(
        "mov $0x23, %%ax\n\t"
        "mov %%ax, %%ds\n\t"
        :
        :
        : "ax", "memory"
    );
}

void _main(const void* mbi, unsigned int magic){
    (void)mbi; (void)magic;
    clear();
    puts("MicrOS starting...\n");

    gdt_init();
    puts("GDT installed\n");

    idt_init();
    puts("IDT installed\n");

    isr_init();
    puts("ISRs installed\n");

    puts("Triggering handlers...\n");
    puts("Testing #GP");  trigger_gp();

    for(;;) asm volatile("hlt");
}
