#include <standardlib.h>
#include <stdarg.h>
#include <stdint.h>

//ver bien que devuelve cada función (en particular, cada syscall)


char getChar(){
    uint16_t c;
    while( sys_read(STDIN, &c, 1) == 0 || c > 255 );
    return (char) c;
}

void putChar(char c) {
    sys_write(STDOUT, &c, 1);
}

// int64_t beep(uint64_t frequency, uint64_t duration) {
//     return sys_beep(frequency, duration);
// }  PROXIMAMENTE

int64_t clear_screen() {
    return sys_clear_screen();
}


// int64_t setFontSize(uint64_t size) {
//     return sys_set_font_size(size);
// }


uint64_t strlen(const char *str) {
    const char *s = str;
    while (*s)
        ++s;
    return s - str;
}


char * numToString(uint64_t num, uint64_t base) { //VIVA CUBA
    static char buffer[64];
    char * ptr = &buffer[63];
    *ptr = '\0';
    do {
        *--ptr = "0123456789abcdef"[num % base];
        num /= base;
    } while(num != 0);
    return ptr;
}


int64_t puts(const char * str) {
    return sys_write(STDOUT, str, strlen(str));
}


int64_t fputc(char c, FileDescriptor fd) {
    return sys_write(fd, &c, 1) == -1 ? -1 : 0;  //nunca devuelve -1, ver si pasamos todo a que sea void
}


