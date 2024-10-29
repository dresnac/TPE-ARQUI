GLOBAL syscall

syscall:
    push rbx
    mov rax, rdi
    mov rbx, rsi
    ; push rcx
    ; mov rcx, rdx
    ; pop rdx
    int 80h
    pop rbx
    ret
