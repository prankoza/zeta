#include "idt.h"
#include "vga.h"

#define IDT_ENTRIES 256

static idt_entry_t idt[IDT_ENTRIES];
static idt_ptr_t   idt_ptr;

extern void isr0(void);
extern void isr1(void);
extern void isr2(void);

static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_low  = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].selector  = sel;
    idt[num].always0   = 0;
    idt[num].flags     = flags;
}

void idt_init(void) {
    idt_ptr.limit = sizeof(idt_entry_t) * IDT_ENTRIES - 1;
    idt_ptr.base  = (uint32_t)&idt;

    for (int i = 0; i < IDT_ENTRIES; i++) {
        idt_set_gate(i, 0, 0, 0);
    }

    idt_set_gate(0, (uint32_t)isr0, 0x08, 0x8E);
    idt_set_gate(1, (uint32_t)isr1, 0x08, 0x8E);
    idt_set_gate(2, (uint32_t)isr2, 0x08, 0x8E);

    __asm__ volatile ("lidt (%0)" : : "r" (&idt_ptr));
}

void isr_handler(uint32_t* regs) {
    uint32_t int_no = regs[0];  // номер прерывания

    if (int_no == 0) {
        // Деление на ноль
        vga_print("EXCEPTION: Division by zero!\n");
        while (1);
    } else {
        vga_print("EXCEPTION: Unknown\n");
        while (1);
    }
}