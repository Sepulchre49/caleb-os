[org 0x7c00]

mov [BOOT_DRIVE], dl ; BIOS stores our boot drive in dl, best to save this for later use

; Debug info for segment offsets
;mov dx, cs
;call print_hex
;call print_line
;mov dx, ds
;call print_hex
;call print_line
;mov dx, es
;call print_hex
;call print_line

mov bp, 0x8000
mov sp, bp

mov bx, 0x9000 ; address to store disk data to
mov dh, 5 ; 5 sectors
mov dl, [BOOT_DRIVE]
call disk_load

mov dx, [0x9000]
call print_hex
call print_line

mov dx, [0x9000 + 512]
call print_hex
call print_line

jmp $

%include "disk_load.asm"
%include "print_string.asm"
%include "print_hex.asm"

BOOT_DRIVE: db 0

times 510-($-$$) db 0
dw 0xaa55

; qemu needs an HDD to be at least 3kb to properly read it.
times 256 dw 0xf00d
times 256 dw 0xface
times 256 dw 0xf00d
times 256 dw 0xface
times 256 dw 0xf00d
