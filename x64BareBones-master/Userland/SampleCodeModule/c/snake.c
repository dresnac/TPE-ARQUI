#include <snake.h>


#define SINGLE_START_X  5
#define SINGLE_START_Y (SIDE/2)
#define APPLE_START_X  13
#define APPLE_START_Y (SIDE/2)

#define TICKS_PER_MOVEMENT 6

typedef enum{
    LEFT = 0, UP, DOWN, RIGHT
}Direction;

int playSingle(int level);
void initSingle(BlockMatrix matrix, SnakeType * snake, Coords * apple);
void fillInitialMatrix(BlockMatrix matrix);
void render(BlockMatrix matrix);
void changeDirection(Direction * dir, char pressedKey);


int playSnake(GameModeType gameMode, int level){
    int toRet = 0;
    //activateInput();  //agregar en standardlib.c, llama a una nueva syscall sys_input_on
    switch(gameMode){
        case SINGLE: toRet = playSingle(level); break;
        // case MULTIPLAYER: toRet = playMultiplayer(level); break;
        // case BATTLE: toRet = playBattle(level); break;
        default: return GAMEMODE_ERR;
    }
    //deactivateInput();
    return toRet;
}

int playSingle(int level){

    BlockMatrix matrix;
    SnakeType snake;
    Coords apple;
    initSingle(matrix, &snake, &apple);
    render(matrix);
    while(getChar() != 'd');  //Hasta que no se haga avanzar la serpiente no arranca
    // Direction dir = RIGHT;
    unsigned long ticksAtStart = getTicks();  //agregar a standardlib.c
    char pressedKey = 0;
    int end = 0;
    int wait = 0;
    unsigned long ticks = 0;
    activateInput();
    int i=0;
    while(i < 5){
        readInput(&pressedKey);
        printf("pk = %d", pressedKey);
        if(pressedKey != 0){
            printf("La tecla fue: %c\n", pressedKey);
            i++;
        }
        i++;
    }
    deactivateInput();
    while(getChar() != 'e');
    //activateInput();
    // while(!end){
    //     readInput(&pressedKey);
    //     if(pressedKey != 0){
    //         changeDirection(&dir, pressedKey);
    //     }
    //     if((ticks = getTicks() - ticksAtStart) != 0 && ticks % (TICKS_PER_MOVEMENT/level) == 0 && !wait){
    //         end = updatePos(matrix, &snake, &apple);
    //         wait = 1;
    //     }
    //     if(ticks != 1 && ticks % (TICKS_PER_MOVEMENT/level) == 1){    //dejo pasar un tick
    //          wait = 0;    
    //     }
    //     render(matrix);
    // }
    //deactivateInput();

}

void initSingle(BlockMatrix matrix, SnakeType * snake, Coords * apple){
    int x = SINGLE_START_X;
    int y = SINGLE_START_Y;
    snake->type = SNAKE1;
    snake->dim = START_LEN;
    fillInitialMatrix(matrix);
    for(int i=0; i < START_LEN; i++){
        matrix[x-i][y] = snake->type;
        snake->body[i] = (Coords){x-i, y};
    }
    apple->x = APPLE_START_X;
    apple->y = APPLE_START_Y;
    matrix[apple->x][apple->y] = APPLE;
}

void fillInitialMatrix(BlockMatrix matrix){
    for(int i=0; i < SIDE; i++){
        for(int j=0; j < SIDE; j++){
            if(i == 0 || i == (SIDE-1) || j == 0 || j == (SIDE-1)){
                matrix[i][j] = LIMIT;
            }else{
                matrix[i][j] = BACKGROUND;
            }
        }
    }
}

void render(BlockMatrix matrix){
    for(int i=0; i < SIDE; i++){
        for(int j=0; j < SIDE; j++){
            draw_rectangle(MATRIX_START_X+BLOCK_SIDE*i, MATRIX_START_Y+BLOCK_SIDE*j, BLOCK_SIDE, BLOCK_SIDE, colorByBlock[matrix[i][j]]);
        }
    }
}

void changeDirection(Direction * dir, char pressedKey){

}

int updatePos(BlockMatrix matrix, SnakeType * snake, Coords * apple){
    
    return 0;
}