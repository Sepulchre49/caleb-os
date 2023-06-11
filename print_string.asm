print_string:
  pusha
  mov ah, 0x0e
  string_loop:
    mov al, [bx]
    add bx, 1
    cmp al, 0
    je return
    int 0x10
    jmp string_loop
  return:
  popa
  ret
