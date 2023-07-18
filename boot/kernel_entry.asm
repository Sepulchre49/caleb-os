; Ensures jumping to the correct entry point of the kernel
[bits 32]      ; By this point, we're in 32 bit protected mode
[extern main]  ; Declare that we're referencing an external symbol 'main'

call main ; invoke main() in our C kernel
jmp $     ; Hang forever when returning from the kernel
