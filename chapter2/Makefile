CC      = gcc
AS      = nasm
LD      = ld
ISO     = MicrOS.iso

CFLAGS  = -m32 -ffreestanding -fno-builtin -fno-stack-protector \
          -O2 -Wall -Wextra \
          -mno-80387 -msoft-float -mno-sse -mno-sse2 -mno-mmx
ASFLAGS = -f elf32
LDFLAGS = -melf_i386

SRCDIR  = src
OBJDIR  = build

SRCS_C  = $(wildcard $(SRCDIR)/*.c)
SRCS_S  = $(wildcard $(SRCDIR)/*.s)

OBJS    = $(SRCS_S:$(SRCDIR)/%.s=$(OBJDIR)/%.o) \
          $(SRCS_C:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# ensure boot.o links first (entry code)
OBJS    := $(OBJDIR)/boot.o $(filter-out $(OBJDIR)/boot.o,$(OBJS))

iso: $(ISO)

$(ISO): kernel.bin iso/boot/grub/grub.cfg
	cp kernel.bin iso/boot/
	grub-mkrescue -o $(ISO) iso

run-grub: $(ISO)
	qemu-system-i386 -cdrom $(ISO) -no-reboot -no-shutdown -serial stdio -net none

.PHONY: all run clean

all: kernel.bin

kernel.bin: linker.ld $(OBJS)
	$(LD) $(LDFLAGS) -T linker.ld -o $@ $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.s | $(OBJDIR)
	$(AS) $(ASFLAGS) $< -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

run: kernel.bin
	qemu-system-i386 -kernel kernel.bin -no-reboot -no-shutdown -net none -serial stdio

clean:
	rm -f kernel.bin
	rm -rf $(OBJDIR)
