#ifndef SYSCALLDISPATCHER_H
#define SYSCALLDISPATCHER_H

#include <stddef.h>

void syscallDispatcher(int id, unsigned int fd, const char * buffer, size_t count);

#endif