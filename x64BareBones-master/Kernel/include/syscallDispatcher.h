#ifndef SYSCALLDISPATCHER_H
#define SYSCALLDISPATCHER_H

#include <stddef.h>

typedef struct {
    uint64_t rax;
    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;
    uint64_t rsp;
    uint64_t r8;
    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
    uint64_t rip;
} Snapshot;


typedef struct {
    int horas;
    int minutos;
}LocalTime;

typedef struct {
	uint64_t r15, r14, r13, r12, r11, r10, r9, r8, rsi, rdi, rbp, rdx, rcx, rbx, rax;
} pushed_registers;

void empty(pushed_registers * regs);
void read(pushed_registers * regs);
void write(pushed_registers * regs);
void clear_screen(pushed_registers * regs);
void time(pushed_registers * regs);
void regs(pushed_registers * regs);
void change_font_size(pushed_registers * regs);

void syscallDispatcher(pushed_registers * regs);

#endif