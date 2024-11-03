#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>
#include <localtime.h>

/*Hace falta el "extern"?*/
uint64_t sys_read(uint64_t fd, char * buffer, uint64_t count);

uint64_t sys_write(uint64_t fd, const char * buffer, uint64_t count);

uint64_t sys_clear_screen(void);

uint64_t sys_time(LocalTime * time);



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

uint64_t sys_get_regs(Snapshot *);

#endif