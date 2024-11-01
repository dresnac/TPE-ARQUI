GLOBAL syscall

section .text

syscall:

    push rbx
    mov rax, rdi
    mov rbx, rsi
    mov rdi, rdx
    mov rdx, rcx
    mov rcx, rdi
    ;nose como hago como hacer para mandar los 4 params
    
    int 80h
    pop rbx
    ret
