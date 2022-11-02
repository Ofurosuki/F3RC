#pragma once
#include <mbed.h>
bool hasHitForward();
bool hasHitBack();
bool hasHitLeft();
bool hasHitRight();
bool hasHitDiagonalRight();
bool hasHitDiagonalLeft();
void buzzer(int);
void buzzer_long(int);
void wait_ms(int);

void forward(int, int ms = 0);
void back(int, int ms = 0);
void left(int, int ms = 0);
void right(int, int ms = 0);
void diagonalRight(int, int ms = 0);
void diagonalLeft(int, int ms = 0);

void stop(int);
void rotate(int);
// slack mite-kudasai
void forwardToWall(int, int modifierF1 = 0, int modifierF2 = 0);
void backToWall(int, int modifierB1 = 0, int modifierB2 = 0);
void leftToWall(int, int modifierL1 = 0, int modifierL2 = 0);
void rightToWall(int, int modifierR1 = 0, int modifierR2 = 0);
void diagonalRightToWall(int);
void diagonalLeftToWall(int);