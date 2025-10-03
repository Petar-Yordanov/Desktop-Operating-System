#include "types.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "vga.h"

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
    puts("Testing #UD");  __asm__ __volatile__("ud2");

    for(;;) asm volatile("hlt");
}
