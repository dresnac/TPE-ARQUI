#include <time.h>
#include <keyboardDriver.h>
#include <stdint.h>
#include <videoDriver.h>



static void int_20();
static void int_21();

static int int_21_flag = 0;

static void (*irq_routines[2])() = {
    int_20,
    int_21
};

void irqDispatcher(uint64_t irq) {
    irq_routines[irq]();
    return;
}


void int_20() {
    timerHandler();
}
void int_21(){
    //keyboardHandler(); //borrar
    if(int_21_flag){
        
        vdPrint("int 21\n", 7, 0x00FFFFFF);
        updateBuffer();
    }
}

void setInt21Flag(int flag){
    int_21_flag = flag;
    vdPrint("Flag actualizado\n", 17, 0x00FFFFFF);
}

// #include <time.h>
// #include <stdint.h>

// static void int_20();

// void irqDispatcher(uint64_t irq) {
// 	switch (irq) {
// 		case 0:
// 			int_20();
// 			break;
// 	}
// 	return;
// }

// void int_20() {
// 	timer_handler();
// }
