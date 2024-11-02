#include <stdint.h> //para uint64_t
#include <stdarg.h> //para cantidad de argumentos variables
#include <videoDriver.h>
#include <keyboardDriver.h>
#include <stddef.h>  //para size_t
#include <syscallDispatcher.h>

static int shiftFlag = 0;

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
    uint32_t colorByFD[] = { 0, 0x00FFFFFF, 0x00FF0000, 0x0000FF00 };
    vdPrint((char*) regs->rcx, regs->rdx, colorByFD[regs->rbx]);
}

void clear_screen(pushed_registers * regs){
    return;
}

void empty(pushed_registers * regs){
    return;
}

void read(pushed_registers * regs){  //el FileDescriptor no sirve de mucho supongo
    char * aux = (char*) regs->rcx;
    for(int i=0; i < regs->rdx; i++){
        aux[i] = getKeyPressed(&shiftFlag);
    }
    return;
}