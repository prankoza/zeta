# Zeta Framework System

A custom operating system kernel and bootloader written in C and assembly.

## Status

- ✅ Stage 1 bootloader (MBR, 512 bytes)
- ✅ Stage 2 bootloader (protected mode, GDT, A20)
- ✅ 32-bit kernel in C (VGA output)
- ✅ IDT (Interrupt Descriptor Table)
- ⏳ Timer and keyboard — in progress
- ⏳ Long mode (64-bit) — planned

## Requirements

- `nasm`
- `gcc` with `-m32` support (`gcc-multilib` on Debian/Ubuntu)
- `ld` with `elf_i386` support (`binutils`)
- `qemu-system-x86_64`

## Build

```bash
# Bootloader
nasm -f bin stage1.asm -o stage1.bin
nasm -f bin stage2.asm -o stage2.bin
```

```bash
# Kernel entry (assembly)
nasm -f elf32 kernel_entry.asm -o kernel_entry.o
nasm -f elf32 isr.asm -o isr.o
```

```bash
# Kernel (C)
gcc -m32 -ffreestanding -nostdlib -c vga.c -o vga.o
gcc -m32 -ffreestanding -nostdlib -c idt.c -o idt.o
gcc -m32 -ffreestanding -nostdlib -c kernel.c -o kernel.o
```

```bash
# Link
ld -m elf_i386 -T linker.ld -o kernel.bin kernel_entry.o kernel.o vga.o idt.o isr.o
```

```bash
# Create disk image
cat stage1.bin stage2.bin kernel.bin > zeta.img
dd if=/dev/zero bs=512 count=20 >> zeta.img
```

## Run
```bash
qemu-system-x86_64 -drive format=raw,file=zeta.img
```
---

Made by [prankoza](https://github.com/prankoza)
