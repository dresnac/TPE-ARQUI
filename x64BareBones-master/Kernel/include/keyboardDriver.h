#ifndef KEYBOARDDRIVER_H
#define KEYBOARDDRIVER_H

char getKeyPressed(int *shiftFlag);
void escPressed();
void updateBuffer();
char getKeyFromBuffer();

#endif