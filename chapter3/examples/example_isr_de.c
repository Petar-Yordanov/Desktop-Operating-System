#include "types.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "vga.h"

volatile unsigned denom = 0;
volatile unsigned numer = 123;
volatile unsigned sink;

static void trigger_de(void) {
    sink = numer / denom;
}

void _main(const void* mbi, unsigned int magic){
    (void)mbi; (void)magic;
    clear();
    puts("NecrOS starting...\n");

    gdt_init();
    puts("GDT installed\n");

    idt_init();
    puts("IDT installed\n");

    isr_init();
    puts("ISRs installed\n");

    puts("Triggering handlers...\n");
    puts("Testing #DE");  trigger_de();

    for(;;) asm volatile("hlt");
}
