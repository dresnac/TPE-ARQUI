#ifndef SYSCALLDISPATCHER_H
#define SYSCALLDISPATCHER_H

#include <stddef.h>



typedef struct {
	uint64_t r15, r14, r13, r12, r11, r10, r9, r8, rsi, rdi, rbp, rdx, rcx, rbx, rax;
} pushed_registers;

void empty(pushed_registers * regs);
void read(pushed_registers * regs);
void write(pushed_registers * regs);
void clear_screen(pushed_registers * regs);
void time(pushed_registers * regs);

void syscallDispatcher(pushed_registers * regs);

#endif