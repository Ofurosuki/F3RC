#include "config.h"

DigitalIn switch0(SWITCH_PIN0);
DigitalIn switch1(SWITCH_PIN1);
DigitalIn switch2(SWITCH_PIN2);
DigitalIn switch3(SWITCH_PIN3);
DigitalIn switch4(SWITCH_PIN4);
DigitalIn switch5(SWITCH_PIN5);
DigitalIn switch6(SWITCH_PIN6);
DigitalIn switch7(SWITCH_PIN7);

DigitalOut dir0(DIR_PIN0);
DigitalOut dir1(DIR_PIN1);
DigitalOut dir2(DIR_PIN2);
DigitalOut dir3(DIR_PIN3);

DigitalOut buzzer0(BUZZER_PIN);

PwmOut pwm0(PWM_PIN0);
PwmOut pwm1(PWM_PIN1);
PwmOut pwm2(PWM_PIN2);
PwmOut pwm3(PWM_PIN3);

DigitalOut led(LED1);
DigitalIn button(USER_BUTTON);

AnalogIn line0(SENSOR_PIN0);
AnalogIn line1(SENSOR_PIN1);
AnalogIn line2(SENSOR_PIN2);
AnalogIn line3(SENSOR_PIN3);