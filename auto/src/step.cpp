#include "step.h"

#include "config.h"
#include "move.h"

void makiage(int time, int dir) {
  DigitalOut PIN0(MOTOR_PIN0);
  DigitalOut PIN1(MOTOR_PIN1);
  if (dir == 0) {
    PIN0 = 1;
    PIN1 = 0;
  } else if (dir == 1) {
    PIN0 = 0;
    PIN1 = 11;
  }
  wait_ms(time);
  PIN0 = 0;
  PIN1 = 0;
}

void step(int hold_step, bool hold_dir, PinName pinstep, PinName pinDIR) {
  DigitalOut step_a(pinstep);
  DigitalOut step_b(pinDIR);
  step_b = hold_dir;
  int i;
  for (i = 0; i < hold_step; i++) {
    step_a = 1;
    wait_ms(2);
    step_a = 0;
    wait_ms(2);
    printf("%d\n", i);
  }
}

void stepLock() {
  DigitalOut pin1(STEP1_STP);
  DigitalOut pin2(STEP1_DIR);
  DigitalOut pin3(STEP2_STP);
  DigitalOut pin4(STEP2_DIR);
  DigitalOut pin5(STEP3_STP);
  DigitalOut pin6(STEP3_DIR);
  pin1 = 0;
  pin2 = 0;
  pin3 = 0;
  pin4 = 0;
  pin5 = 0;
  pin6 = 0;
}

/*
  STEP1 開閉
  STEP2 押す
  STEP3 前後
*/

void releaseObject() {
  // step(80, 0, STEP1_STP, STEP1_DIR);
  // step(230, 0, STEP2_STP, STEP2_DIR);
  step(270, 0, STEP3_STP, STEP3_DIR);
  step(230, 1, STEP2_STP, STEP2_DIR);
  step(100, 1, STEP1_STP, STEP1_DIR);
  step(100, 0, STEP1_STP, STEP1_DIR);
  step(270, 1, STEP3_STP, STEP3_DIR);
  // makiage(5000, 0);
  // step(80, 1, STEP1_STP, STEP1_DIR);
}
void openArm() {
  // step(80, 0, STEP1_STP, STEP1_DIR);
  // step(230, 0, STEP2_STP, STEP2_DIR);
  // step(260, 0, STEP3_STP, STEP3_DIR);
  // step(230, 1, STEP2_STP, STEP2_DIR);
  // step(80, 1, STEP1_STP, STEP1_DIR);
  // step(80, 0, STEP1_STP, STEP1_DIR);
  // step(260, 1, STEP3_STP, STEP3_DIR);
  // // makiage(5000, 0);
  step(80, 1, STEP1_STP, STEP1_DIR);
}

void closeArm() {
  step(100, 0, STEP1_STP, STEP1_DIR);
  step(200, 0, STEP2_STP, STEP2_DIR);
  // step(260, 0, STEP3_STP, STEP3_DIR);
  // step(230, 1, STEP2_STP, STEP2_DIR);
  // step(80, 1, STEP1_STP, STEP1_DIR);
  // step(80, 0, STEP1_STP, STEP1_DIR);
  // step(260, 1, STEP3_STP, STEP3_DIR);
  // // makiage(5000, 0);
  // step(80, 1, STEP1_STP, STEP1_DIR);
  stepLock();
}

void hajishita() {
  // step(80,0,STEP1_STP,STEP1_DIR);
  // step(230,0,STEP2_STP,STEP2_DIR);
  step(260, 0, STEP3_STP, STEP3_DIR);
  step(230, 1, STEP2_STP, STEP2_DIR);
  step(80, 1, STEP1_STP, STEP1_DIR);
  step(80, 0, STEP1_STP, STEP1_DIR);
  step(270, 1, STEP3_STP, STEP3_DIR);
  step(80, 1, STEP1_STP, STEP1_DIR);
  // makiage(100,0);
  // step(80,1,STEP1_STP,STEP1_DIR);
}

void releaseObjectAtCentral() {
  // step(80,0,STEP1_STP,STEP1_DIR);
  // step(230,0,STEP2_STP,STEP2_DIR);
  makiage(4100, 1);
  stop(200);
  forward(20, 900);
  stop(200);
  step(80, 1, STEP1_STP, STEP1_DIR);
  stop(200);
  back(20, 1000);
  stop(200);
  step(80, 0, STEP1_STP, STEP1_DIR);
  stop(200);
  makiage(4300, 0);
  step(230, 1, STEP2_STP, STEP2_DIR);
  // step(80, 1, STEP1_STP, STEP1_DIR);
}