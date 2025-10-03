#include "types.h"

static volatile uint16_t* const VGA = (uint16_t*)0xB8000;
static const int COLS = 80, ROWS = 25;

static void vga_clear(void){
    for (int i = 0; i < COLS*ROWS; ++i)
        VGA[i] = (0x07 << 8) | ' ';
}

static void vga_print_at(int row, int col, const char* s){
    int i = row*COLS + col;
    while (*s)
        VGA[i++] = (0x07 << 8) | (uint8_t)*s++;
}

void _main(const void* mbi, unsigned int magic){
    (void)mbi; (void)magic;
    vga_clear();
    vga_print_at(0, 0, "Hello World from MicrOS");
    for(;;) __asm__ __volatile__("cli; hlt");
}
