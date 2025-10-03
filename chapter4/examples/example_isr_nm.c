#include "types.h"
#include "gdt.h"
#include "idt.h"
#include "isr.h"
#include "vga.h"

static void trigger_nm(void) {
    __asm__ __volatile__(
        "mov %%cr0, %%eax\n\t"
        "or  $0x8, %%eax\n\t"
        "mov %%eax, %%cr0\n\t"
        "fninit\n\t"
        :
        :
        : "eax", "memory"
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
    puts("Testing #NM");  trigger_nm();

    for(;;) asm volatile("hlt");
}
