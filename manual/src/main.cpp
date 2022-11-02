#include <TransmitterIR.h>
#include <mbed.h>

#include "config.h"
#include "controller.h"
#include "servo.h"

#define sqrt_2_exp_minus_1 0.707107  //ルート2の-1乗
//                             y
//足回り　                      ^
//          front              |
//   wheel1         wheel0     |
//                              ------>x
//   wheel2         wheel3
//          rear

Controller controller(can1, 0x334);

void onPushOpenArm(int armNum, bool state) {
  if (!state) return;

  if (armNum == 0) {
    moveServo(servoL, 500);
  } else if (armNum == 1) {
    moveServo(servoC, 1200);
  } else {
    moveServo(servoR, 1100);
  }
}

void onPushCloseArm(bool state) {
  if (!state) return;

  move3Servo(servoL, 1300, servoC, 500, servoR, 130);
}

void onPushUpWinch(bool state) {
  if (state) {
    winch0 = 1;
    winch1 = 0;
  } else {
    winch0 = 0;
    winch1 = 0;
  }
}

void onPushDownWinch(bool state) {
  if (state) {
    winch0 = 0;
    winch1 = 1;
  } else {
    winch0 = 0;
    winch1 = 0;
  }
}

void step(int stepNum, bool direction) {
  step_dir = direction;
  int i;
  for (i = 0; i < stepNum; i++) {
    step_num = 1;
    ThisThread::sleep_for(4ms);
    step_num = 0;
    ThisThread::sleep_for(4ms);
    printf("%d\n", i);
  }
}

bool isArmForward = false;

void onPushForwardArm(bool state) {
  if (!state) return;
  if (isArmForward) return;

  step(120, 0);
  isArmForward = true;
}

void onPushBackArm(bool state) {
  if (!state) return;
  if (!isArmForward) return;
  step(120, 1);
  isArmForward = false;
}
void onPushStartAutoRobot(bool state) {
  if (!state) return;

  TransmitterIR ir(IRLED_PIN);
  for (int i = 0; i < 20; i++) {
    while (ir.getState() != TransmitterIR::State::Idle) {
    }
    uint8_t buf[] = {0x8C, 0xE0, 0x00};
    int bitcount = 20;
    ir.setData(RemoteIR::Format::NEC, buf, bitcount);
  }
}

void onPushBtn(size_t btnNum, bool state) {
  printf("push button %d\n", btnNum);
  switch (btnNum) {
    case 0:  // x
      onPushOpenArm(0, state);
      break;
    case 1:  // a
      onPushOpenArm(1, state);
      break;
    case 2:  // b
      onPushOpenArm(2, state);
      break;
    case 3:  // y
      onPushCloseArm(state);
      break;
    case 12:  // up
      onPushUpWinch(state);
      break;
    case 13:  // down
      onPushDownWinch(state);
      break;

    case 6:  // LZ
      onPushForwardArm(state);
      break;
    case 7:  // RZ
      onPushBackArm(state);
      break;

    case 16:  //真ん中のロジクールのボタン
      onPushStartAutoRobot(state);
      break;
  }
}

class Wheel {
 public:
  float MDpulse_raw;
  Wheel(DigitalOut& _dir, PwmOut& _pwmout, float _motor_ratio)
      : MDdir(_dir), MDpulse(_pwmout), motor_ratio(_motor_ratio) {}

  void set_MDpulse() {
    if (MDpulse_raw > 0) {
      MDpulse = MDpulse_raw * motor_ratio;
      MDdir = 0;
    } else {
      MDpulse = -MDpulse_raw * motor_ratio;
      MDdir = 1;
    }
  }

 private:
  DigitalOut& MDdir;
  PwmOut& MDpulse;
  float motor_ratio;
};

float input_x = 0;  //-1~1をとる 左のjoyconを想定
float input_y = 0;  //-1~1をとる 左のjoyconを想定
float input_z =
    0;  //-1~1をとる 右のjoyconを想定（右ジョイコンのy軸は現状読み取らない予定）
float velocity_rotation_ratio = 0;  //走行中の本体の回転と移動の出力の案配
                                    // 0-1をとる 1で移動100%、 0で自転100%
float velocity = 0;

void set_velocity_rotaion_ratio() {
  velocity = sqrt(input_x * input_x + input_y * input_y);
  velocity_rotation_ratio = velocity;
}

int main() {
  // onPushCloseArm(true);

  pwmout0.period_us(100);
  pwmout1.period_us(100);
  pwmout2.period_us(100);
  pwmout3.period_us(100);

  onPushOpenArm(0, true);
  onPushOpenArm(1, true);
  onPushOpenArm(2, true);

  controller.setButtonEventListener(&onPushBtn);

  Wheel wheel0(dir0, pwmout0, 0.8);
  Wheel wheel1(dir1, pwmout1, 0.8);
  Wheel wheel2(dir2, pwmout2, 0.8);
  Wheel wheel3(dir3, pwmout3, 0.8);

  // wheel0.MDpulse_raw = 0.5;
  // wheel0.set_MDpulse();

  while (true) {
    controller.receiveData();
    // printf("axesX: %d, axesY, %d", controller.axes.x, controller.axes.y);
    set_velocity_rotaion_ratio();
    input_x = -controller.axes.x * 0.01;
    // input_x = 1;
    input_y = controller.axes.y * 0.01;
    input_z = controller.axes.z * 0.01;
    wheel0.MDpulse_raw =
        sqrt_2_exp_minus_1 * velocity_rotation_ratio * (-input_x + input_y) +
        (1 - velocity_rotation_ratio) * input_z;
    wheel1.MDpulse_raw =
        sqrt_2_exp_minus_1 * velocity_rotation_ratio * (-input_x - input_y) +
        (1 - velocity_rotation_ratio) * input_z;
    wheel2.MDpulse_raw =
        sqrt_2_exp_minus_1 * velocity_rotation_ratio * (input_x - input_y) +
        (1 - velocity_rotation_ratio) * input_z;
    wheel3.MDpulse_raw =
        sqrt_2_exp_minus_1 * velocity_rotation_ratio * (input_x + input_y) +
        (1 - velocity_rotation_ratio) * input_z;

    printf("wheel0: %d, wheel1: %d, wheel2: %d, wheel3: %d\n",
           (int)(wheel0.MDpulse_raw * 100), (int)(wheel1.MDpulse_raw * 100),
           (int)(wheel2.MDpulse_raw * 100), (int)(wheel3.MDpulse_raw * 100));

    wheel0.set_MDpulse();
    wheel1.set_MDpulse();
    wheel2.set_MDpulse();
    wheel3.set_MDpulse();
  }
}
