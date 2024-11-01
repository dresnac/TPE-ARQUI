#ifndef STANDARDLIB_H
#define STANDARDLIB_H

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
char * numToString(uint64_t num, uint64_t base);
int64_t puts(const char * str);


#endif