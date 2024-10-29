#include <stdint.h> //para uint64_t
#include <stdarg.h> //para cantidad de argumentos variables
#include <videoDriver.h>
#include <stddef.h>  //para size_t

void write(unsigned int fd, const char * buffer, size_t count);

void syscallDispatcher(int id, ...){

    va_list args;
    va_start(args, id);

    switch(id){
        case 4: int fd = va_arg(args, int); //crear enum fileDescriptor
                char * buffer = va_arg(args, char*);
                size_t count = va_arg(args, size_t);
                write(fd, buffer, count);
                break;

        default: int cursor[] = {0,0};
                print("Fail", cursor);
    }

    va_end(args);
}


void write(unsigned int fd, const char * buffer, size_t count){
    int cursor[] = {0,0};
    print(buffer, cursor);
}