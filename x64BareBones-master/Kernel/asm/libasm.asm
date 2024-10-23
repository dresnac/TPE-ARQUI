GLOBAL cpuVendor
GLOBAL getKey


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