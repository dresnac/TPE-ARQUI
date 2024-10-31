#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H

#include <stdint.h>

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);
void drawChar(char);
void print(const char *s);
void newline();
void delete();
#endif