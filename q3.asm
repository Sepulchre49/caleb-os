mov bx, 30 ; load 30 into register bx

cmp bx, 4
jle A
cmp bx, 40
jle B
jmp C


A:
mov al, 'A'
jmp print
B:
mov al, 'B'
jmp print
C:
mov al, 'C'
jmp print

print:
mov ah, 0x0e
int 0x10

jmp $

times 510-($-$$) db 0
dw 0xaa55
