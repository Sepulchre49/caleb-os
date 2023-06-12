[bits 16]
switch_to_pm:
  cli ; Disables interrupts
  lgdt [gdt_descriptor]

  mov eax, cr0 ; Mask first bit of cr0,
  or eax, 0x1  ; which sets us in protected mode
  mov cr0, eax

  jmp CODE_SEG:init_pm ; Flush pipelined instructions

[bits 32]
; Initialize all registers and stack in protected mode
init_pm:
  mov ax, DATA_SEG
  mov ds, ax ; old segments are meaningless
  mov ss, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  mov ebp, 0x90000 ; Update stack pointer, should be top of free space
  mov esp, ebp

  call BEGIN_PM
