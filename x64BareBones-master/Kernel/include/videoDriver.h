#ifndef VIDEODRIVER_H
#define VIDEODRIVER_H

#include <stdint.h>

void putPixel(uint32_t hexColor, uint64_t x, uint64_t y);
void drawChar(char c, uint32_t hexColor);
void vdPrint(const char *buffer, int count, uint32_t hexColor);
void newline();
void delete();
void tab();
void vdClearScreen();
int vdChangeFontSize(int);
#endif