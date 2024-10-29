#include <time.h>
#include <keyboardDriver.h>
#include <stdint.h>



static void int_20();
static void int_21();

static void (*irq_routines[2])() = {
    int_20,
    int_21
};

void irqDispatcher(uint64_t irq) {
    irq_routines[irq]();
    return;
}


void int_20() {
    timer_handler();
}
void int_21(){
    //keyboardHandler();
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
