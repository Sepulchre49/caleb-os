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

print_line:
  pusha
  mov bx, nlcr
  call print_string
  ; Debug code, trying to figure out why nlcr isn't printing correctly when %include'd to a driver file
  ;mov dx, nlcr 
  ;call print_hex ; debug address of nlcr
  ;call print_string
  popa
  ret

nlcr:
  dw 0x0a0d, 0 ; newline, carraige return, followed by a null terminator
