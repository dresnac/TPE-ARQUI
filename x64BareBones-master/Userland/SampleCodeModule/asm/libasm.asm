GLOBAL syscall

section .text

syscall:
    push rbp
    mov rbp, rsp
    push rbx
    push r12
    push r13
    push r15

    mov rax, rdi
    mov rbx, rsi
    push rcx     ;swap
    mov rcx, rdx
    pop rdx
    int 80h

    pop r15
    pop r13
    pop r12
    pop rbx
    mov rsp, rbp
    pop rbp
    ret
