
GLOBAL _cli
GLOBAL _sti
GLOBAL picMasterMask
GLOBAL picSlaveMask
GLOBAL haltcpu
GLOBAL _hlt

GLOBAL _irq00Handler
GLOBAL _irq01Handler
GLOBAL _irq02Handler
GLOBAL _irq03Handler
GLOBAL _irq04Handler
GLOBAL _irq05Handler

GLOBAL _irq80Handler

GLOBAL _exception0Handler

EXTERN should_take_reg_shot
EXTERN irqDispatcher
EXTERN exceptionDispatcher
EXTERN syscallDispatcher

SECTION .text

%macro pushState 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popState 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro

%macro irqHandlerMaster 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call irqDispatcher

	; signal pic EOI (End of Interrupt)
	mov al, 20h
	out 20h, al

	popState
	iretq
%endmacro



%macro exceptionHandler 1
	pushState

	mov rdi, %1 ; pasaje de parametro
	call exceptionDispatcher

	popState
	iretq
%endmacro


_hlt:
	sti
	hlt
	ret

_cli:
	cli
	ret


_sti:
	sti
	ret

picMasterMask:
	push rbp
    mov rbp, rsp
    mov ax, di
    out	21h,al
    pop rbp
    retn

picSlaveMask:
	push    rbp
    mov     rbp, rsp
    mov     ax, di  ; ax = mascara de 16 bits
    out	0A1h,al
    pop     rbp
    retn


;8254 Timer (Timer Tick)
_irq00Handler:
	irqHandlerMaster 0

;Keyboard
_irq01Handler:
	;irqHandlerMaster 1
	pushState

    mov rdi, 1
    call irqDispatcher

    call should_take_reg_shot
    cmp rax, 1

    jne .keyboard_end
    popState
    pushState
    mov [regs_shot + 8 * 0 ], rax
    mov [regs_shot + 8 * 1 ], rbx
    mov [regs_shot + 8 * 2 ], rcx
    mov [regs_shot + 8 * 3 ], rdx
    mov [regs_shot + 8 * 4 ], rsi
    mov [regs_shot + 8 * 5 ], rdi
    mov [regs_shot + 8 * 6 ], rbp
    mov rax, [rsp + 18 * 8]

    ;Descomentar para ver que hay en la dir apuntada por RSP:
    ;mov rbx, [rsp + 18* 8]
    ;mov rax, [rbx]

    mov [regs_shot + 8 * 7 ], rax            ;rsp
    mov [regs_shot + 8 * 8 ], r8
    mov [regs_shot + 8 * 9 ], r9
    mov [regs_shot + 8 * 10], r10
    mov [regs_shot + 8 * 11], r11
    mov [regs_shot + 8 * 12], r12
    mov [regs_shot + 8 * 13], r13
    mov [regs_shot + 8 * 14], r14
    mov [regs_shot + 8 * 15], r15
    mov rax, [rsp+158]    ; posicion en el stack de la dir. de retorno (valor del rip previo al llamado de la interrupcion)
    mov [regs_shot + 8 * 16], rax

    mov rax, 1
    mov [regs_shot_available], rax          ; tenemos un snapshot de los registros

.keyboard_end:
    ; signal pic EOI (End of Interrupt)
    mov al, 20h
    out 20h, al

    popState
    iretq

;Cascade pic never called
_irq02Handler:
	irqHandlerMaster 2

;Serial Port 2 and 4
_irq03Handler:
	irqHandlerMaster 3

;Serial Port 1 and 3
_irq04Handler:
	irqHandlerMaster 4

;USB
_irq05Handler:
	irqHandlerMaster 5

_irq80Handler:
	; push rbx
	; push rdi
	; push rsi
	; mov rdi, rax
	; mov rsi, rbx
	; push rdx      ;swap
	; mov rdx, rcx
	; pop rcx

	; call syscallDispatcher

	; pop rsi
	; pop rdi
	; pop rbx

	; push rax
	; mov al, 20h
	; out 20h, al
	; pop rax
	;iretq
	push rdi
	push rsi
	push rdx
	push rcx

	mov rdi, 1
	mov rsi, 1
	mov rdx, buffer
	mov rcx, 5

	; int 80h
	call syscallDispatcher

	pop rcx
	pop rdx
	pop rsi
	pop rdi

	;push rax
	;mov al, 20h
	;out 20h, al
	;pop rax

	iretq

;Zero Division Exception
_exception0Handler:
	exceptionHandler 0

haltcpu:
	cli
	hlt
	ret



SECTION .bss
	aux resq 1

section .rodata
	buffer db "Jorge"
section .data
 	regs_shot dq 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ; 17 zeros
	regs_shot_available dq 0 ; flag para saber si hay un regs_shot disponible
    exception_regs dq 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ; 18 zeros

