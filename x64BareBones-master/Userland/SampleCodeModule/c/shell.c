#include <stdint.h>
#include <shell.h>

void startShell(){

    char * ejemplo = "Hola";

    syscall(4, 1, ejemplo, 5);

}