GLOBAL syscall

section .text

syscall:

    push rbx
    mov rax, rdi
    mov rbx, rsi
    mov rcx, rdx
    int 80h
    pop rbx
    ret
