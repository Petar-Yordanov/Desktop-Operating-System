.PHONY: all build run

all: build bin run

build: boot.bin

bin: boot.bin

boot.bin: boot.asm
	nasm -f bin ./boot.asm -o ./boot.bin

run: boot.bin
	qemu-system-x86_64 -drive file=./boot.bin,format=raw,if=ide
