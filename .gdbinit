target remote localhost:1234
symbol-file kernel.elf
b kernel/kernel.c:7 if i == 23
b kernel/kernel.c:9
alias cursor = p get_cursor()
continue