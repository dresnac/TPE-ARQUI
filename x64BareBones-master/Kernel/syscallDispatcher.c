#include <stdint.h> //para uint64_t
#include <stdarg.h> //para cantidad de argumentos variables
#include <videoDriver.h>
#include <stddef.h>  //para size_t
#include <syscallDispatcher.h>

static void (*syscall_manager[])() = {
    empty,
    empty,
    empty,
    read,
    write,
    clear_screen,
    delete,     //este llama directo a la func de video driver
    newline,
    //completar
    
};

void syscallDispatcher(pushed_registers * regs){ //en realidad serían args variables

    syscall_manager[regs->rax](regs);

}

void write(pushed_registers * regs){
    print((char*) regs->rcx);
}

void clear_screen(pushed_registers * regs){
    return;
}

void empty(pushed_registers * regs){
    return;
}

void read(pushed_registers * regs){
    return;
}