#include <mbed.h>

#include "config.h"
#include "hit.h"
#include "ir.h"
#include "motor.h"
#include "move.h"
#include "step.h"

const int sensorTH = 10;
int sensorcount = 0;

int progress_cnt = 0;
bool wait_sensor = true;
void getStatus() {
  if (switch0 == 0) {
    progress_cnt = 0;
    printf("progress_cnt: %d\n", progress_cnt);
  }
  if (switch1 == 0) {
    progress_cnt = 1;
    printf("progress_cnt: %d\n", progress_cnt);
    buzzer(1);
  }
  if (switch2 == 0) {
    progress_cnt = 2;
    printf("progress_cnt: %d\n", progress_cnt);
    buzzer(2);
  }
  if (switch3 == 0) {
    progress_cnt = 3;
    printf("progress_cnt: %d\n", progress_cnt);
    buzzer(3);
  }
  if (switch4 == 0) {
    progress_cnt = 4;
    printf("progress_cnt: %d\n", progress_cnt);
    buzzer(4);
  }
  if (switch5 == 0) {
    progress_cnt = 5;
    printf("progress_cnt: %d\n", progress_cnt);
    buzzer(5);
  }
  if (switch6 == 0) {
    wait_sensor = false;
    printf("false\n");
    buzzer_long(1);
  }
  if (switch7 == 0) {
    wait_sensor = true;
    printf("true\n");
    buzzer_long(2);
  }
}

void init() {
  printf("boot\n");
  switch0.mode(PullUp);
  switch1.mode(PullUp);
  switch2.mode(PullUp);
  switch3.mode(PullUp);
  switch4.mode(PullUp);
  switch5.mode(PullUp);
  switch6.mode(PullUp);
  switch7.mode(PullUp);
  pwm0.period(0.00001);
  pwm1.period(0.00001);
  pwm2.period(0.00001);
  pwm3.period(0.00001);

  printf("init complete\n");
  printf("waiting for start\n");
  buzzer(2);
  while (true) {
    getStatus();
    if (!button) break;
  }
}

int sensor[4];
void checkSensor() {
  sensor[0] = line0.read_u16();
  sensor[1] = line1.read_u16();
  sensor[2] = line2.read_u16();
  sensor[3] = line3.read_u16();
}

/*
InterruptIn pushTheUserButton(USER_BUTTON);
void ringTheBuzzer(){
  buzzer(1);

pushTheUserButton.fall(&ringTheBuzzer);
}
*/

int main() {
  init();
  if (progress_cnt == 0) {
    if (wait_sensor == true) waitSignal(IR_PIN);
    wait_sensor = 1;
    closeArm();
    stepLock();
    // 1周目第2病院
    backToWall(30);
    forward(30, 700);
    rightToWall(30);
    left(30, 500);
    forwardToWall(30);  //第2病院到着
    back(30, 500);
    // 1個目置く
    stop(200);
    releaseObject();
    //帰る
    backToWall(30);
    forward(30, 1000);
    leftToWall(30);
    right(30, 700);
    stop(200);
    openArm();
    progress_cnt = 1;
  }

  if (progress_cnt == 1) {
    if (wait_sensor == true) waitSignal(IR_PIN);
    wait_sensor = 1;

    closeArm();
    stepLock();
    // 1周目第1病院
    backToWall(30);
    forward(30, 700);
    stepLock();
    rotate(-90);
    stepLock();
    stop(200);
    backToWall(30);
    forwardToWall(30);  //第1病院到着
    back(30, 500);
    // 2個目置く
    stop(500);
    releaseObject();

    //帰る
    backToWall(30, 10);  //引数2つ目は補正値
    forward(30, 700);
    rotate(90);
    stop(200);
    backToWall(30);
    forward(30, 700);
    stop(200);

    progress_cnt = 2;
    openArm();
  }

  if (progress_cnt == 2) {
    if (wait_sensor == true) waitSignal(IR_PIN);
    wait_sensor = 1;

    closeArm();
    stepLock();

    // 2周目
    // 2周目第２病院
    backToWall(30);
    forward(30, 700);
    right(30, 4000);
    
    right(30);
    while (sensorcount < sensorTH) {
      checkSensor();
      if (sensor[1] >= 5000 && sensor[2] >= 5000) {
        sensorcount++;
      }
    }
    sensorcount=0;
    diagonalRightToWall(30);
    left(30, 200);
    forward(30);
    while (sensorcount < sensorTH) {
      checkSensor();
      if (sensor[1] >= 5000 && sensor[0] >= 5000) {
        sensorcount++;
      }
    }
    sensorcount=0;
    //完全進入するかどうか確かめる
    forward(30, 3000);
    // 1個目置く
    stop(500);
    releaseObject();
    //帰る
    back(30, 5000);
    back(20);
    while (sensorcount < sensorTH) {
      checkSensor();
      if (sensor[2] >= 5000 && sensor[3] >= 5000) {
        sensorcount++;
      }
    }
    sensorcount=0;
    diagonalLeftToWall(30);
    forward(30, 200);
    leftToWall(30);
    right(30, 700);
    stop(200);

    openArm();
    progress_cnt = 4;
  }

  if (progress_cnt == 3) {  //ワクチン受けとる　
    if (wait_sensor == true) waitSignal(IR_PIN);
    wait_sensor = 1;

    closeArm();
    stepLock();

    // 2周目第1病院
    backToWall(30);
    forward(30, 1000);
    rotate(-90);
    stop(200);
    backToWall(30);
    forward(30,4000);
    forward(30);
    while (sensorcount < sensorTH) {
      checkSensor();
      if (sensor[1] >= 5000 && sensor[0] >= 5000) {
        sensorcount++;
      }
    }
    sensorcount=0;
    //完全進入してるかどうか確かめる
    forward(30, 1000);
    // 2個目置く
    stop(500);
    releaseObject();
    //帰る
    back(30, 1000);
    rotate(90);
    backToWall(30);
    forward(30, 1000);
    leftToWall(30);
    right(30, 700);
    stop(200);

    openArm();
    progress_cnt = 5;
  }

  if (progress_cnt == 4) {
    if (wait_sensor == true) waitSignal(IR_PIN);
    wait_sensor = 1;

    closeArm();
    stepLock();

    // 1周目中央病院
    backToWall(30);
    forward(30, 700);
    stepLock();
    right(30, 7000);
    forwardToWall(30);
    back(30, 500);
    stepLock();
    rotate(90);
    stepLock();
    stop(200);
    backToWall(30);

    // ラインを読むまで前進

    forward(20);
    while (sensorcount < sensorTH) {
      checkSensor();
      if (sensor[2] >= 5000 & sensor[3] >= 5000) {
        sensorcount++;
      }
    }
    sensorcount=0;
    rightToWall(20);
    left(20,500);
    forward(20,1000);
    // forward(20, 7000);
    // 3個目置く
    stop(500);
    releaseObjectAtCentral();

    //帰る
    backToWall(30);
    forward(30, 500);
    leftToWall(30);
    right(30, 500);
    forward(30,3000);
    leftToWall(30);
    right(30,500);
    forwardToWall(30);
    back(30, 700);
    rotate(-90);
    stop(200);
    backToWall(30);
    forward(30, 700);
    stop(200);

    openArm();

    progress_cnt = 3;
  }

  if (progress_cnt == 5) {
    if (wait_sensor == true) waitSignal(IR_PIN);
    wait_sensor = 1;

    closeArm();
    stepLock();

    // 2周目中央病院
    backToWall(30);
    forward(30, 700);
    right(30, 7000);
    forwardToWall(30);
    back(30, 500);
    rotate(90);
    backToWall(30);
    // forward(20, 7000);
    sensorcount = 0;
    forward(20);
    while (sensorcount < sensorTH) {
      checkSensor();
      if (sensor[1] >= 5000 & sensor[0] >= 5000) {
        sensorcount++;
      }
    }
    sensorcount=0;
    rightToWall(20);
    left(20,500);
    forward(20,1000);
    // 3個目置く
    stop(500);
    releaseObjectAtCentral();
    //帰る
    backToWall(30);
    forward(30, 500);
    leftToWall(30);
    right(30, 500);
    forward(30,3000);
    leftToWall(30);
    right(30,500);
    forwardToWall(30);
    back(30, 300);
    rotate(-90);
    stop(200);
    leftToWall(30);
    right(30,200);
    forward(30);
    sensorcount = 0;
    while (sensorcount < sensorTH) {
      checkSensor();
      if (sensor[1] >= 5000 & sensor[0] >= 5000) {
        sensorcount++;
      }
    } 
    sensorcount=0; 
    forward(20,1000);
    leftToWall(10);
    buzzer_long(2);  

    stop(0);
    while (1) {
    }
  }
}