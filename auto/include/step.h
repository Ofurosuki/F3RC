#pragma once
#include <mbed.h>

void makiage(int, int);
void step(int, bool, PinName, PinName, float);
void stepLock();
void releaseObject();
void openArm();
void closeArm();
void hajishita();
void releaseObjectAtCentral();