GLOBAL cpuVendor
GLOBAL getKey
GLOBAL pruebaSysDispatcher

EXTERN syscallDispatcher
EXTERN _irq80Handler

section .text
	
cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid


	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret


getKey:
    mov rax, 0
.cicle: 
    in al, 64h
    and al, 0x01
    je .cicle
    in al, 60h

    ret

pruebaSysDispatcher:

	push rdi
	push rsi
	push rdx
	push rcx

	mov rdi, 4
	mov rsi, 1
	mov rdx, buffer
	mov rcx, 5

	;call _irq80Handler
	int 80h

	call _irq80Handler

	pop rcx
	pop rdx
	pop rsi
	pop rdi

	ret

section .rodata

buffer db "Jorge"
