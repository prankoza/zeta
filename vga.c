#include "vga.h"

#define VGA_BUFFER 0xB8000
#define VGA_WIDTH  80
#define VGA_HEIGHT 25

static unsigned short* vga = (unsigned short*)VGA_BUFFER;
static int cursor = 0;

void vga_clear(void) {
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        vga[i] = 0x0F20;
    }
    cursor = 0;
}

void vga_print(const char* str) {
    while (*str) {
        if (*str == '\n') {
            cursor += VGA_WIDTH - (cursor % VGA_WIDTH);
        } else {
            vga[cursor++] = (0x0F << 8) | *str;
        }
        str++;
    }
}