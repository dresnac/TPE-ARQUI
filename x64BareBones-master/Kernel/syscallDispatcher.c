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
    //completar
    
};


void syscallDispatcher(pushed_registers * regs){ //en realidad serían args variables

    syscall_manager[regs->rax](regs);

}

void write(pushed_registers * regs){
    print("hola");
    print((char*) regs->rcx);
}

void empty(pushed_registers * regs){
    return;
}

void read(pushed_registers * regs){
    return;
}