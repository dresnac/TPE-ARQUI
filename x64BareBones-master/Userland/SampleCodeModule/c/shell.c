#include <stdint.h>
#include <shell.h>

void startShell(){

    char * ejemplo = "Jorge";

    syscall(4, 1,(int64_t) ejemplo, 5);

}