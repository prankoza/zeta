[BITS 16]
[ORG 0x7C00]

start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    mov si, msg_stage1
    call print

    mov ah, 0x00
    mov dl, 0x80
    int 0x13

    mov ax, 0x0000
    mov es, ax
    mov bx, 0x8000

    mov ah, 0x02
    mov al, 1
    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, 0x80
    int 0x13

    jc disk_error

    jmp 0x0000:0x8000

disk_error:
    mov si, msg_error
    call print
    cli
    hlt

print:
    lodsb
    or al, al
    jz .done
    mov ah, 0x0E
    mov bh, 0x00
    int 0x10
    jmp print
.done:
    ret

msg_stage1 db "Stage 1: loading Stage 2...", 13, 10, 0
msg_error  db "Disk read error!", 13, 10, 0

times 510 - ($ - $$) db 0
dw 0xAA55