#include <stdint.h> //para uint64_t
#include <stdarg.h> //para cantidad de argumentos variables
#include <videoDriver.h>
#include <keyboardDriver.h>
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
    // int * shiftFlag = {0};     //Intente algo pero no funcionó, quizas lo mejor sea hacer un buffer para el keyboard
    // char * aux = (char*) regs->rcx;
    // for(int i=0; i < regs->rdx; i++){
    //     aux[i] = getKeyPressed(shiftFlag);
    //     aux[i] = 'a';
    //     vdPrint("La letra es: ", 20, 0x00FFFFFF);
    //     vdPrint(regs->rcx, 1, 0x00FFFFFF);
    // }
    return;
}