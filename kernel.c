#include <stdint.h>

#define VGA_BUFFER 0xB8000
#define VGA_WIDTH  80
#define VGA_HEIGHT 25

static uint16_t* vga = (uint16_t*)VGA_BUFFER;
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

void kernel_main(void) {
    vga_clear();
    vga_print("Zeta Framework System v0.2\n");
    vga_print("32-bit kernel loaded successfully!\n");
    vga_print("Written in C, running in protected mode.\n");
    vga_print("\n");
    vga_print("Next: memory management, interrupts, drivers.\n");

    while (1) {
        __asm__ volatile ("hlt");
    }
}