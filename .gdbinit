target remote localhost:1234
symbol-file kernel.elf
b idt_set_gate
alias cursor = p get_cursor()
continue