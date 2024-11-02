#include <stdint.h>
#include <shell.h>
#include <standardlib.h>

#define PROMPT_TEXT "$:> "
#define MAX_CHARS 110
#define MSG_BUFFER_FULL "\nCuidado: Buffer de comandos lleno\n"

static void interpret(char * buffer);

void startShell(){

    char commandBuff[MAX_CHARS] = {0};
    int i=0;
    int newPrompt;
    char c;
    while(1){
        newPrompt = 0;
        printf(PROMPT_TEXT);
        while(i < MAX_CHARS && !newPrompt){
            c = getChar();
            if(c == '\n'){
                commandBuff[i] = '\0';
                interpret(commandBuff);
                i = 0;
                newPrompt = 1;
                putChar(c);
            }else if(c == '\b'){
                if(i > 0){
                    i--;
                    putChar(c);
                }
            }else{
                commandBuff[i++] = c;
                putChar(c);
            }
            if(i >= MAX_CHARS){  //hay que hacer que cuando llegue al final de la línea siga en la siguiente
                fprintf(STDERR, MSG_BUFFER_FULL);
                i = 0;
                newPrompt = 1;
            }        
        }
    }
    
}


static void interpret(char * buffer){
    return;
}