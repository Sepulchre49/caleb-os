mov ah, 0x0e

; Attempt 1
mov bx, msg1 + 0x7c00
call print_string
mov al, [the_secret] ; this will not work properly because offset is not set
int 0x10
mov bx, nl_cr + 0x7c00
call print_string

; Attempt 2
mov bx, 0x7c0
mov ds, bx ; set the data segment address indirectly
mov bx, msg2
call print_string
mov al, [the_secret] ; should print X now
int 0x10
mov bx, nl_cr
call print_string

; Attempt 3
mov bx, msg3
call print_string
mov al, [es:the_secret] ; uses es segment as offset instead of ds, new notation
int 0x10
mov bx, nl_cr
call print_string

; Attempt 4
mov bx, msg4
call print_string
mov bx, 0x7c0
mov es, bx
mov al, [es:the_secret] ; now this will be double offsetted, should not print
int 0x10
mov bx, nl_cr
call print_string

jmp $

%include "print_string.asm"

the_secret:
  db "X"
msg1:
  db "First attempt", 0
msg2:
  db "Second attempt", 0
msg3:
  db "Third attempt", 0
msg4:
  db "Fourth attempt", 0
nl_cr:
  dw 0x0a0d

times 510-($-$$) db 0
dw 0xaa55
