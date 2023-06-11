%include "print_string.asm"

print_hex:
  pusha
  mov cl, 3 ; Loop counter and value by which to right-shift dx
  loop:
    mov ax, dx
    shr ax, cl ; Shift bytes
    and ax, 0x000f ; isolate current hex digit
    call hex_to_ascii
    ; Calculate offset manually
    mov bx, HEX_OUT + 5
    sub bx, cx
    ; Store the character in array
    mov [bx], al
    ; dec cl and loop
    dec cx
    cmp cx, 0
    jge loop

return_hex:
  mov bx, HEX_OUT
  call print_string
  popa
  ret

hex_to_ascii:
  cmp al, 10 ; values 0-9, add 48
  jge letter ; values a-f, add 55
  add al, 48
  ret

  letter:
  add al, 55
  ret

HEX_OUT: db '0x0000', 0
