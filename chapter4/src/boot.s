[BITS 32]
GLOBAL loader          ; entry point
GLOBAL isr_stub
EXTERN _main

; -------- Multiboot header (must be in first 8KiB) --------
SECTION .multiboot
align 4
MAGIC    equ 0x1BADB002
FLAGS    equ 0x00000003
CHECKSUM equ -(MAGIC + FLAGS)
dd MAGIC
dd FLAGS
dd CHECKSUM

; -------- Code --------
SECTION .text
loader:
    cli

    ; Disable NMI
    in   al, 0x70
    or   al, 0x80
    out  0x70, al

    ; Mask PIC
    mov  al, 0xFF
    out  0x21, al
    out  0xA1, al

    ; Setup 16 KiB stack (aligned to 16 bytes)
    mov  esp, stack_top
    and  esp, 0xFFFFFFF0

    ; Save GRUB regs (eax=magic, ebx=mbi)
    push ebx
    push eax

    ; Restore + pass args to _main(mbi, magic)
    pop eax        ; magic
    pop ebx        ; mbi
    push eax       ; arg2
    push ebx       ; arg1
    call _main

.hang:
    cli
    hlt
    jmp .hang

; Simple ISR stub if you need to install IDT
isr_stub:
    cli
.stub_hang:
    hlt
    jmp .stub_hang

; -------- Stack --------
SECTION .stack nobits
align 16
stack_bottom:
    resb 16384
stack_top:

; Tell the linker the stack does NOT need to be executable
SECTION .note.GNU-stack noalloc noexec nowrite
