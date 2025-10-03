ENTRY(loader)
OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386)

SECTIONS
{
  . = 1M;                       /* 0x00100000 */

  /* Multiboot header must be in the first 8 KiB */
  .multiboot : { *(.multiboot) }

  .text : {
    *(.text*)
    *(.rodata*)
  }

  .data : {
    KEEP(*( .init_array ))
    KEEP(*(SORT_BY_INIT_PRIORITY( .init_array.* )))
    *(.data*)
  }

  .bss : {
    *(.bss*)
    *(COMMON)
  }

  /* Keep stack after BSS, in its own section */
  .stack (NOLOAD) : {
    *(.stack)
  }

  /DISCARD/ : { *(.fini_array*) *(.comment) }
}
