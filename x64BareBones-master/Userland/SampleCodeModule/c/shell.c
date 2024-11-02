#include <stdint.h>
#include <shell.h>
#include <standardlib.h>

#define PROMPT_TEXT "$:> "

void startShell(){

    printf(PROMPT_TEXT);
    while(1){
        char c = getChar();
        putChar(c);
    }

}