target remote localhost:1234
symbol-file kernel.elf
b kernel/kernel.c:12
b isr_handler
alias cursor = p get_cursor()
continue