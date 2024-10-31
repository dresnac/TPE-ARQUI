#ifndef SYSCALLDISPATCHER_H
#define SYSCALLDISPATCHER_H

#include <stddef.h>

void syscallDispatcher(int id, unsigned int fd, const char * buffer, size_t count);

typedef struct {
	uint64_t r15, r14, r13, r12, r11, r10, r9, r8, rsi, rdi, rbp, rdx, rcx, rbx, rax;
} pushed_registers;

#endif