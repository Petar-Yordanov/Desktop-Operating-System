#include "types.h"

static volatile uint16_t* const VGA = (uint16_t*)0xB8000;
static int row = 0;

void clear(void){
    for (int i=0; i<80*25; i++) VGA[i] = (0x07 << 8) | ' ';
    row = 0;
}

void puts(const char* s){
    int col = 0;
    while (*s){
        VGA[row*80+col] = (0x07 << 8) | *s++;
        col++;
    }
    row = (row+1) % 25;
}