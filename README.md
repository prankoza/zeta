# Zeta Framework System

A custom operating system kernel and bootloader written in C and assembly.

## Status

- Stage 1 bootloader (MBR, 512 bytes)
- Stage 2 bootloader (protected mode, GDT, A20)
- 32-bit kernel in C (VGA output)
- Long mode (64-bit) — in progress

## Build

```bash
-- nasm -f bin stage1.asm -o stage1.bin
-- nasm -f bin stage2.asm -o stage2.bin
-- nasm -f elf32 kernel_entry.asm -o kernel_entry.o
-- gcc -m32 -ffreestanding -nostdlib -c kernel.c -o kernel.o
-- ld -m elf_i386 -T linker.ld -o kernel.bin kernel_entry.o kernel.o
-- cat stage1.bin stage2.bin kernel.bin > zeta.img
```

## Run
```bash
qemu-system-x86_64 -drive format=raw,file=zeta.img
```

---

Made by [prankoza](https://github.com/prankoza)
