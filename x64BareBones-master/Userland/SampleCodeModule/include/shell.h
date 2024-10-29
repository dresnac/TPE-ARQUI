#ifndef SHELL_H
#define SHELL_H

#include <stdint.h>

extern uint64_t syscall(uint64_t rax, uint64_t rbx, uint64_t rcx, uint64_t rdx); //sacar, va en la librería de c

void startShell();

#endif