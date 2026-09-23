#include "vga.h"

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