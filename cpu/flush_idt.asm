[global idt_flush]

idt_flush:
    mov eax, [esp+4] ; Address storing lidt (passed from C function)
    lidt [eax]       ; Load lidt from the table constructed in init_idt
    ret