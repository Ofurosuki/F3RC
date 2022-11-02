#pragma once
#include <mbed.h>

#define STEP1_STP PB_2
#define STEP1_DIR PB_1
#define STEP2_STP PB_15
#define STEP2_DIR PB_14
#define STEP3_STP PB_13
#define STEP3_DIR PC_4

#define MOTOR_PIN0 PA_6 
#define MOTOR_PIN1 PC_9

#define SWITCH_PIN0 PA_15
#define SWITCH_PIN1 PC_3
#define SWITCH_PIN2 PB_7
#define SWITCH_PIN3 PC_12
#define SWITCH_PIN4 PC_10
#define SWITCH_PIN5 PC_11
#define SWITCH_PIN6 PC_2
#define SWITCH_PIN7 PD_2

#define DIR_PIN0 PB_4
#define DIR_PIN1 PA_8
#define DIR_PIN2 PC_7
#define DIR_PIN3 PA_7

#define PWM_PIN0 PB_5
#define PWM_PIN1 PB_10
#define PWM_PIN2 PA_9
#define PWM_PIN3 PB_6

#define SENSOR_PIN0 PB_0
#define SENSOR_PIN1 PC_1
#define SENSOR_PIN2 PA_4
#define SENSOR_PIN3 PC_0

#define BUZZER_PIN PA_5

#define IR_PIN PB_8

#define CW 1
#define CCW 0

extern DigitalIn switch0;
extern DigitalIn switch1;
extern DigitalIn switch2;
extern DigitalIn switch3;
extern DigitalIn switch4;
extern DigitalIn switch5;
extern DigitalIn switch6;
extern DigitalIn switch7;

extern DigitalOut dir0;
extern DigitalOut dir1;
extern DigitalOut dir2;
extern DigitalOut dir3;

extern DigitalOut buzzer0;

extern PwmOut pwm0;
extern PwmOut pwm1;
extern PwmOut pwm2;
extern PwmOut pwm3;

extern DigitalOut led;
extern DigitalIn button;

extern AnalogIn line0;
extern AnalogIn line1;
extern AnalogIn line2;
extern AnalogIn line3;