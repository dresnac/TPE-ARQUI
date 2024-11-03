#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <stdint.h>
#include <localtime.h>

/*Hace falta el "extern"?*/
uint64_t sys_read(uint64_t fd, char * buffer, uint64_t count);

uint64_t sys_write(uint64_t fd, const char * buffer, uint64_t count);

uint64_t sys_clear_screen(void);

uint64_t sys_time(LocalTime * time);

#endif