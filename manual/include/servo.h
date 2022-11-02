#pragma once
#include <mbed.h>

void moveServo(DigitalOut& servo, int us);

void move3Servo(DigitalOut& servo0, int us0, DigitalOut& servo1, int us1,
                DigitalOut& servo2, int us2);