#ifndef STANDARDLIB_H
#define STANDARDLIB_H

#include <stdarg.h>
#include <stdint.h>
#include <syscalls.h>
#include <localtime.h>

typedef enum
{
    STDIN = 0,
    STDOUT,
    STDERR,
    STDMARK,
} FileDescriptor;


char getChar();
void putChar(char c);
// int64_t beep(uint64_t frequency, uint64_t duration);
int64_t clear_screen();
// int64_t setFontSize(uint64_t size);
uint64_t strlen(const char *str);
void strcopy(const char * s, char * t);
char * numToString(uint64_t num, uint64_t base);
int64_t puts(const char * str);
int64_t fputc(char c, FileDescriptor fd);
void time(LocalTime * time);
int64_t fprintf(FileDescriptor fd, const char * fmt, ...);
int64_t printf(const char * fmt, ...);
char* gets(char* buffer, int n);
int64_t strcmp(const char *str1, const char *str2);
void print_regs();
//int64_t enter_video_mode();
// int64_t enter_text_mode();
// int64_t draw_pixel(uint64_t x, uint64_t y, Color color);
// int64_t draw_rectangle(uint64_t x, uint64_t y, uint64_t width, uint64_t height, Color color);
// int64_t draw_letter(uint64_t x, uint64_t y, char letter, Color color, uint64_t font_size);
// void print_register_snapshot();

#endif