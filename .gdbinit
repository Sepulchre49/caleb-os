target remote localhost:1234
symbol-file kernel.elf
b kernel/kernel.c:9
alias curs = p get_cursor()
continue