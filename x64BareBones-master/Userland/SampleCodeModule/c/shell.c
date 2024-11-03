#include <stdint.h>
#include <shell.h>
#include <standardlib.h>

#define PROMPT_TEXT "$:> "
#define MAX_CHARS 110
#define MSG_BUFFER_FULL "\nCuidado: Buffer de comandos lleno\n"

static int interpret(char * buffer);
static void help();
static void showCurrentTime();
static void zoomIn();
static void zoomOut();
static void getRegs();
static void div0();
static void opCode();
static void clear();
static void snake();

static module modules[] = {
    {"help", help},
    {"time", showCurrentTime},
    {"zoomin", zoomIn},
    {"zoomout", zoomOut},
    {"getregs", getRegs},
    {"dividebyzero", div0},
    {"opcode", opCode},
    {"clear", clear},
    {"snake", snake}
};


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
                //interpret(commandBuff);
                i = 0;
                newPrompt = 1;
                if(!interpret(commandBuff)){putChar(c);}
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


static int interpret(char * buffer){
    int flag = 0;
    for(int i = 0; i<MAX_MODULES; i++){
        if(!strcmp(buffer, modules[i].name)){
            modules[i].function();
            if(i==7){               //si el comando fue clear activa el flag (modificarlo)
                flag = 1;
            }
        }
    }
    return flag;
}

//muestra comandos disponibles
static void help(){
    printf("\n\tCOMANDOS DISPONIBLES\n");
    printf("\thelp\n");
    printf("\ttime\n");
    printf("\tzoomin\n");
    printf("\tzoomout\n");
    printf("\tgetregs\n");
    printf("\tdevidebyzero\n");
    printf("\topcode\n");
    printf("\tclear\n");
    printf("\tsnake\n");
}

//muestra la hora actual
static void showCurrentTime(){
    LocalTime currentTime;
    time(&currentTime);  //completa el struct con la hora actual
    printf("\nLa hora es %d:%d", currentTime.horas, currentTime.minutos);
}

//agranda la pantalla
static void zoomIn(){
    return;
}

//achica la pantalla
static void zoomOut(){
    return;
}

//muestra los registros
static void getRegs(){
    return;
}

//divide por cero hace saltar la excepcion
static void div0(){
    return;
}

//(?)
static void opCode(){
    return;
}

//borra toda la pantalla y solo deja el primer prompt
static void clear(){
    clear_screen();
}

//juego del snake
static void snake(){
    return;
}