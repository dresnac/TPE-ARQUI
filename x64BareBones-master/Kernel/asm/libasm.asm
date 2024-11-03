GLOBAL cpuVendor
GLOBAL getKey
GLOBAL Hours
GLOBAL Mins

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


;inc
Hours:
	push rbp
	mov rbp, rsp

	mov rax, 0
	mov al, 0x04
	out 70h, al
	in ax, 71h

	mov rsp, rbp
	pop rbp

	ret

Mins:
	push rbp
	mov rbp, rsp

	mov rax, 0
	mov al, 0x02
	out 70h, al
	in ax, 71h

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

section .rodata

buffer db "Jorge"
