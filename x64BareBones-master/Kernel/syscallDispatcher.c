#include <stdint.h> //para uint64_t
#include <stdarg.h> //para cantidad de argumentos variables
#include <videoDriver.h>
#include <keyboardDriver.h>
#include <stddef.h>  //para size_t
#include <syscallDispatcher.h>

static int shiftFlag = 0;

static char * numToString(uint64_t num, uint64_t base);
static uint8_t bcd_decimal(uint8_t BCD);
extern int getHs();
extern int getMin();

static void (*syscall_manager[])() = {
    empty,
    empty,
    empty,
    read,
    write,
    clear_screen,
    delete,     //este llama directo a la func de video driver
    newline,
    time,
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
    vdClearScreen();
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

void time(pushed_registers * regs){
    // char *horas;
    // char *minutos;
    // char *time;
    // horas=numToString(getHs(),16);
    // minutos=numToString(getMin(),16);
    // newline();
    // vdPrint(horas, 2, 0x00FFFFFF);
    // vdPrint(":",1,0x00FFFFFF);
    // vdPrint(minutos, 2, 0x00FFFFFF);
    LocalTime * time = regs->rbx;
    // vdPrint(numToString(getHs(), 16), 2, 0x00FFFFFF); // getHs está devolviendo 0.
    time->horas = bcd_decimal(getHs());
    time->minutos = bcd_decimal(getMin());
}

static char * numToString(uint64_t num, uint64_t base) {
    static char buffer[64];
    char * ptr = &buffer[63];
    *ptr = '\0';
    do {
        *--ptr = "0123456789abcdef"[num % base];
        num /= base;
    } while(num != 0);
    return ptr;
}

static uint8_t bcd_decimal(uint8_t BCD) {
    return (BCD >> 4) * 10 + (BCD & 0x0F);
}