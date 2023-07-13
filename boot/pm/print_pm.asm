[bits 32] ; needs to be set to bits 32 because the bin/raw format generates code for 16 bit architecture

VIDEO_MEMORY equ 0xb8000 ; MMIO location for VGA
WHITE_ON_BLACK equ 0x0f

; Prints a null terminated string pointed to by EBX
print_string_pm:
  pusha
  mov edx, VIDEO_MEMORY

print_string_pm_loop:
  mov al, [ebx]          ; character to print
  mov ah, WHITE_ON_BLACK ; color attribute

  cmp al, 0 ; check if we're at null terminator
  je print_string_pm_done

  mov [edx], ax ; Load current character into MMIO array

  add ebx, 1 ; string index
  add edx, 2 ; each VGA index is 2 bytes long (1 for character, 1 for color)

  jmp print_string_pm_loop

print_string_pm_done:
  popa
  ret
