[global idt_flush]

idt_flush:
    mov eax, [esp+4] ; Address to store lidt at (passed from C function)
    lidt [eax]       ; Store idt pointer in memory address stored in eax
    ret