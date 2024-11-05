#include <snake.h>


#define SINGLE_START_X  5
#define SINGLE_START_Y (SIDE/2)
#define APPLE_START_X  13
#define APPLE_START_Y (SIDE/2)

#define TICKS_PER_MOVEMENT 6

int playSingle(int level);
void initSingle(BlockMatrix matrix, SnakeType * snake, Coords * apple);
void fillInitialMatrix(BlockMatrix matrix);
void render(BlockMatrix matrix);


int playSnake(GameModeType gameMode, int level){
    int toRet = 0;
    //activateInput();  //agregar en standardlib.c, llama a una nueva syscall sys_input_on
    switch(gameMode){
        case SINGLE: toRet = playSingle(level); break;
        // case MULTIPLAYER: toRet = playMultiplayer(level); break;
        // case BATTLE: toRet = playBattle(level); break;
        default: return GAMEMODE_ERR;
    }
    return toRet;
}

int playSingle(int level){

    BlockMatrix matrix;
    SnakeType snake;
    Coords apple;
    initSingle(matrix, &snake, &apple);
    render(matrix);
    while(getChar() != 'd');   //Hasta que no se haga avanzar la serpiente no arranca
    // int ticksAtStart = getTicks();  //agregar a standardlib.c
    // char pressedKey = 0;
    // int end = 0;
    // while(!end){
    //     readInput(&pressedKey);
    //     if(pressedKey != 0){
    //         changeDirection(pressedKey);
    //     }
    //     if((getTicks() - ticksAtStart) % (TICKS_PER_MOVEMENT/level) == 0){
    //         end = updatePos(matrix, &snake, &apple);
    //     }
    //     render(matrix);
    // }

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

void changeDirection(char pressedKey){

}

int updatePos(BlockMatrix matrix, SnakeType * snake, Coords * apple){
    
    return 0;
}