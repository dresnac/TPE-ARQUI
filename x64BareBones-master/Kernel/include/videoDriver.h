#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H

#include <stdint.h>

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);
void drawChar(char, int, int);
void print(const char *s, int *cursor);
void newline(int *cursor);
void delete(int *cursor);
#endif