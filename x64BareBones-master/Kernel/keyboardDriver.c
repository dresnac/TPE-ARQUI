#include <stdint.h>
#include <videoDriver.h>

//keyboardDriver.c
#define SHIFT_PRESSED 0x2A  //42 en decimal
#define SHIFT_RELEASED 0xAA  //170 en decimal
#define RELEASED_CODE 0x80  //A partir de este código, se indican las teclas liberadas 

extern int getKey();
static char getKeyPressedRec(int *shiftFlag);
static char getAscii(int scancode, int shiftOn);

static uint8_t reg_shot_flag = 0;
static char buffer[10000];
static int current = 0;

/* Wrapper */
char getKeyPressed(int *shiftFlag){
    return getKeyPressedRec(shiftFlag);
}

/* Devuelve el caracter presionado (no se ocupa de imprimir ni parecido)
    Pensar si es mejor no hacerla recursiva */
static char getKeyPressedRec(int *shiftFlag){

    int scancode = getKey();

    if(scancode == (int) SHIFT_PRESSED){  //si se presiona el shift, pido la siguiente tecla presionada pero en "mayúscula"
        *shiftFlag = 1;
		return getKeyPressedRec(shiftFlag);
    }
    if(scancode == (int) SHIFT_RELEASED){ //si se suelta el shift, pido la siguiente tecla presionada en "minúscula"
        *shiftFlag = 0;
		return getKeyPressedRec(shiftFlag);
    }
    if(scancode >= (int) RELEASED_CODE){
        return getKeyPressedRec(shiftFlag); //si se devuelve un código de letra liberada, pido la siguiente tecla presionada
    }
    return getAscii(scancode, *shiftFlag);

}

static char getAscii(int scancode, int shiftOn){
    /* Mapeo (Teclado de Mac) de scancode a caracteres en ascii.
    El scancode es un código en hexa que devuelve el teclado según la tecla presionada/liberada.
    Al soltar una tecla se devuelve su scancode inicial + 0x80.  */
    unsigned char scancode_to_ascii[58][2] = 
	{
		{0, 0},
		{27, 27},  //Escape
		{'1', '!'},
		{'2', '@'},
		{'3', '#'},
		{'4', '$'},
		{'5', '%'},
		{'6', '^'},
		{'7', '&'},
		{'8', '*'},
		{'9', '('}, 
		{'0', ')'},
		{'-', '_'},
		{'=', '+'},
		{8, 8},  //Backspace
		{9, 9},  //Horizontal tab
		{'q', 'Q'},
		{'w', 'W'},
		{'e', 'E'},
		{'r', 'R'},
		{'t', 'T'},
		{'y', 'Y'},
		{'u', 'U'},
		{'i', 'I'},
		{'o', 'O'},
		{'p', 'P'},
		{'[', '{'},
		{']', '}'},
		{'\n', '\n'},  //Salto de línea
		{0, 0},
		{'a', 'A'},
		{'s', 'S'},
		{'d', 'D'},
		{'f', 'F'},
		{'g', 'G'},
		{'h', 'H'},
		{'j', 'J'},
		{'k', 'K'},
		{'l', 'L'},
		{';', ':'},
		{39, 34},  // ' y "
		{'`', '~'},
		{0, 0},
		{'\\', '|'},
		{'z', 'Z'},
		{'x', 'X'},
		{'c', 'C'},
		{'v', 'V'},
		{'b', 'B'},
		{'n', 'N'},
		{'m', 'M'},
		{',', '<'},
		{'.', '>'},
		{'/', '?'},
		{0, 0},
		{0, 0},
		{0, 0},
		{' ', ' '},
	};

    return scancode_to_ascii[scancode][shiftOn];
}


uint8_t should_take_reg_shot() {
	return reg_shot_flag;
}

void escPressed(){
	reg_shot_flag = 1;
}

void updateBuffer(){
	int shift = 0;
	buffer[current++] = getKeyPressed(&shift);
}

char getKeyFromBuffer(){
	return buffer[current-1];
}