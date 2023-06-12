; Load DH sectors to ES:BX from drive DL
disk_load:
  push dx

  mov ah, 0x02 ; read sector interrupt routine
  mov al, dh   ; disk #, provided by BOOT_DISK
  mov ch, 0x00 ; cylinder 0
  mov dh, 0x00 ; head 0
  mov cl, 0x02 ; sector 2

  int 0x13 ; read disk

  jc flag_set

  pop dx
  cmp dh, al ; check if # of sectors actually read (AL) = number of sectors requested (DH)
  jne sector_count
  ret


flag_set:
  shr ax, 8
  mov dx, ax
  mov bx, error_msgA
  call print_string
  call print_line
  mov bx, flag_value_msg
  call print_string
  call print_hex
  call print_line
  jmp $

sector_count:
  mov bx, error_msgB
  call print_string
  jmp $

error_msgA:
  db 'Error reading from the disk: flag set', 0
error_msgB:
  db 'Error reading from the disk: too few enough sectors read', 0
flag_value_msg:
  db 'The value of the carry flag is ', 0
