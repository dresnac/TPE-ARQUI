GLOBAL syscall

section .text

syscall:

    push rbx
    mov rax, rdi
    mov rbx, rsi
    mov rdi, rdx
    mov rdx, rcx
    mov rcx, rdi
    int 80h
    pop rbx
    ret


sys_read:
    push rdi
    mov rdi, 3
    call syscall
    pop rdi
    ret

sys_write:
    push rdi
    mov rdi, 4
    call syscall
    pop rdi
    ret


sys_clear_screen:
    push rdi
    mov rdi, 4
    call syscall
    pop rdi
    ret