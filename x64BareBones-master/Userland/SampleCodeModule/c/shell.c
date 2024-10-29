#include <stdint.h>

uint64_t syscall(uint64_t rax, uint64_t rbx, uint64_t rcx, uint64_t rdx); //sacar, va en la librería de c


void startShell(){

    char * ejemplo = "Hola";

    syscall(4, 1, (uint64_t) ejemplo, 5);

}