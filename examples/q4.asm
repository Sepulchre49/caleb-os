[org 0x7c00]

mov bx, HELLO_MSG
call print_string

call print_newline

mov bx, GOODBYE_MSG
call print_string

call print_newline

mov bx, HEX_OUTPUT
call print_string

call print_newline

jmp $

%include "print_string.asm"

HELLO_MSG:
  db 'Hello, world!', 0

GOODBYE_MSG:
  db 'Goodbye!', 0

HEX_OUTPUT:
  db '0x0000', 0

print_newline:
  pusha
  mov ah, 0x0e ; teletype output
  mov al, 0xa ; newline char
  int 0x10
  mov al, 0xd ; carriage return
  int 0x10
  popa
  ret

times 510-($-$$) db 0
dw 0xaa55
