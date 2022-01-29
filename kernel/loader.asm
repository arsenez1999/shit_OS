extern kernel_main

global _start:function (_start.end - _start)

section .bss
align 16
stack_bootom:
    resb 1024*16
stack_top:

section .text
_start:
    mov esp, stack_top
    call kernel_main
    
    cli
.hang:
    hlt
    jmp .hang
.end: