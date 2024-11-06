#include <keyboardDriver.h>
#include <stdint.h>

extern uint8_t getKey();


/*
 * Buffer --> es "circular". Si se llena, pisa lo que primero se puso.
 */


static uint16_t buffer[BUFFER_SIZE];
static uint64_t buffer_dim = 0;
static uint64_t buffer_current = 0;
static uint8_t reg_shot_flag = 0;


extern uint16_t pressedKeyShiftMap[][2];

#define CANT_FUNCTION_KEYS 12
static void f1key(void);
static function_key functionKeyFunArray[CANT_FUNCTION_KEYS] = {f1key};
static void f1key(void){
    reg_shot_flag = 1;
}

void setFKeyFunction(uint64_t key_number, function_key f){
    if(key_number == 0 || key_number > CANT_FUNCTION_KEYS ){
        return;
    }
    key_number--;
    functionKeyFunArray[key_number] = f;
}

static void functionKeyHandler(uint64_t code){
    int64_t i = -1;
    switch (code) {
        case F1:i = 0;break;
        case F2: i =1; break;
        case F3: i=2; break;
        case F4: i =3; break;
        case F5: i=4; break;
        case F6: i =5; break;
        case F7: i=6; break;
        case F8: i =7; break;
        case F9: i=8; break;
        case F10: i =9; break;
        case F11: i=10; break;
        case F12: i =11; break;
    }
    if(i != -1 && functionKeyFunArray[i] != 0){
        functionKeyFunArray[i]();
    }

}


static uint8_t isReleased(uint8_t key){
    return (key & 0x80);
}
static uint8_t isPressed(uint8_t key){
    return !isReleased(key);
}

#define specialKeyPressedMapIdx(code) (code - FIRST_SPECIAL_KEY)
static uint16_t specialKeyPressedMap[SPECIAL_KEYS_CANT] = {0};
static int isSpecialKey(uint16_t code){
    return (code >= FIRST_SPECIAL_KEY) && (code <= LAST_SPECIAL_KEY);
}

static int specialKeyPressed(uint16_t code){
    if(!isSpecialKey(code)){
        return -1;
    }
    return specialKeyPressedMap[specialKeyPressedMapIdx(code)];
}


static int capsLockPressed(){
    return specialKeyPressed(CAPS_LOCK);
}
static int shiftPressed(){
    return (specialKeyPressed(LEFT_SHIFT) || specialKeyPressed(RIGHT_SHIFT)) ? 1:0;
}
static int shiftCapsLockPressed(){
    return (shiftPressed()^capsLockPressed()); //xor
}

static uint8_t releasedKeyToPressedMask(uint8_t key){
    return key&0x7F;
}



uint64_t bufferHasNext(){
    return ( buffer_dim > 0 ) && ( buffer_current < buffer_dim );
}

uint64_t getCurrent(){
    if(bufferHasNext()) {
        return buffer[buffer_current++];
    }
    return 0;
}

void keyboardHandler(){
    reg_shot_flag = 0;
    uint8_t key = getKey();


    uint8_t key_is_pressed = isPressed(key) ? 1:0;

    if( !key_is_pressed){
        key = releasedKeyToPressedMask(key); //la tabla es para PRESSED !
    }

    uint16_t code = pressedKeyShiftMap[key][shiftCapsLockPressed()];


    if(isSpecialKey(code)){
        if(code != CAPS_LOCK && code != NUM_LOCK && code != SCROLL_LOCK){
            specialKeyPressedMap[specialKeyPressedMapIdx(code)] = key_is_pressed;
        }else if(key_is_pressed) {
            specialKeyPressedMap[specialKeyPressedMapIdx(code)] = 1 - specialKeyPressedMap[specialKeyPressedMapIdx(code)];
        }
    }

    if(!key_is_pressed){
        return;
    }
    functionKeyHandler(code);


    buffer[buffer_dim] = code;
    if(buffer_dim < BUFFER_SIZE){
        buffer_dim++;
    }else{
        buffer_dim = 1;
    }
}

uint8_t should_take_reg_shot() {
    return reg_shot_flag;
}



// #include <stdint.h>
// #include <videoDriver.h>

// //keyboardDriver.c
// #define SHIFT_PRESSED 0x2A  //42 en decimal
// #define SHIFT_RELEASED 0xAA  //170 en decimal
// #define RELEASED_CODE 0x80  //A partir de este código, se indican las teclas liberadas 

// extern int getKey();
// static char getKeyPressedRec(int *shiftFlag);
// static char getAscii(int scancode, int shiftOn);

// static uint8_t reg_shot_flag = 0;
// static char buffer[10000];
// static int current = 0;

// /* Wrapper */
// char getKeyPressed(int *shiftFlag){
//     return getKeyPressedRec(shiftFlag);
// }

// /* Devuelve el caracter presionado (no se ocupa de imprimir ni parecido)
//     Pensar si es mejor no hacerla recursiva */
// static char getKeyPressedRec(int *shiftFlag){

//     int scancode = getKey();

//     if(scancode == (int) SHIFT_PRESSED){  //si se presiona el shift, pido la siguiente tecla presionada pero en "mayúscula"
//         *shiftFlag = 1;
// 		return getKeyPressedRec(shiftFlag);
//     }
//     if(scancode == (int) SHIFT_RELEASED){ //si se suelta el shift, pido la siguiente tecla presionada en "minúscula"
//         *shiftFlag = 0;
// 		return getKeyPressedRec(shiftFlag);
//     }
//     if(scancode >= (int) RELEASED_CODE){
//         return getKeyPressedRec(shiftFlag); //si se devuelve un código de letra liberada, pido la siguiente tecla presionada
//     }
//     return getAscii(scancode, *shiftFlag);

// }

// static char getAscii(int scancode, int shiftOn){
//     /* Mapeo (Teclado de Mac) de scancode a caracteres en ascii.
//     El scancode es un código en hexa que devuelve el teclado según la tecla presionada/liberada.
//     Al soltar una tecla se devuelve su scancode inicial + 0x80.  */
//     unsigned char scancode_to_ascii[58][2] = 
// 	{
// 		{0, 0},
// 		{27, 27},  //Escape
// 		{'1', '!'},
// 		{'2', '@'},
// 		{'3', '#'},
// 		{'4', '$'},
// 		{'5', '%'},
// 		{'6', '^'},
// 		{'7', '&'},
// 		{'8', '*'},
// 		{'9', '('}, 
// 		{'0', ')'},
// 		{'-', '_'},
// 		{'=', '+'},
// 		{8, 8},  //Backspace
// 		{9, 9},  //Horizontal tab
// 		{'q', 'Q'},
// 		{'w', 'W'},
// 		{'e', 'E'},
// 		{'r', 'R'},
// 		{'t', 'T'},
// 		{'y', 'Y'},
// 		{'u', 'U'},
// 		{'i', 'I'},
// 		{'o', 'O'},
// 		{'p', 'P'},
// 		{'[', '{'},
// 		{']', '}'},
// 		{'\n', '\n'},  //Salto de línea
// 		{0, 0},
// 		{'a', 'A'},
// 		{'s', 'S'},
// 		{'d', 'D'},
// 		{'f', 'F'},
// 		{'g', 'G'},
// 		{'h', 'H'},
// 		{'j', 'J'},
// 		{'k', 'K'},
// 		{'l', 'L'},
// 		{';', ':'},
// 		{39, 34},  // ' y "
// 		{'`', '~'},
// 		{0, 0},
// 		{'\\', '|'},
// 		{'z', 'Z'},
// 		{'x', 'X'},
// 		{'c', 'C'},
// 		{'v', 'V'},
// 		{'b', 'B'},
// 		{'n', 'N'},
// 		{'m', 'M'},
// 		{',', '<'},
// 		{'.', '>'},
// 		{'/', '?'},
// 		{0, 0},
// 		{0, 0},
// 		{0, 0},
// 		{' ', ' '},
// 	};

//     return scancode_to_ascii[scancode][shiftOn];
// }


// uint8_t should_take_reg_shot() {
// 	return reg_shot_flag;
// }

// void escPressed(){
// 	reg_shot_flag = 1;
// }

// void updateBuffer(){
// 	int shift = 0;
// 	buffer[current++] = getKeyPressed(&shift);
// }

// char getKeyFromBuffer(){
// 	return buffer[current-1];
// }