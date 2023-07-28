target remote localhost:1234
symbol-file kernel.elf
b kernel/kernel.c:6
continue