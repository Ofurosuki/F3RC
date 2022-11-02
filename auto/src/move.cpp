#include "move.h"

#include <mbed.h>

#include "config.h"
#include "hit.h"
#include "motor.h"

Motor m1(dir1, pwm1, 1);
Motor m2(dir2, pwm2, 1);
Motor m0(dir0, pwm0, 1.1);
Motor m3(dir3, pwm3, 1.1);

int j = 0;
const int TH = 30;

//前
bool hasHitForward() {
  j = 0;
  while (switch0 == 0 && switch7 == 0) {
    j++;
    printf("%d\n", j);
    if (j > TH) {
      printf("frontdetected\n");
      buzzer(2);
      return true;
      break;
    }
  }
  return false;
}

//後
bool hasHitBack() {
  j = 0;
  // back(10);
  while (switch3 == 0 && switch4 == 0) {
    j++;
    printf("%d\n", j);
    if (j > TH) {
      buzzer(2);
      return true;
      break;
    }
  }
  return false;
}

//左
bool hasHitLeft() {
  j = 0;
  while (switch1 == 0 && switch2 == 0) {
    j++;
    if (j > TH) {
      buzzer(2);
      return true;
      break;
    }
  }
  return false;
}

//右
bool hasHitRight() {
  j = 0;
  while (switch5 == 0 && switch6 == 0) {
    j++;
    if (j > TH) {
      buzzer(2);
      return true;
      break;
    }
  }
  return false;
}

//右斜め前
bool hasHitDiagonalRight() {
  j = 0;
  while (switch5 == 0 || switch6 == 0) {
    j++;
    if (j > TH) {
      buzzer(2);
      return true;
      break;
    }
  }
  return false;
}

//左斜め後ろ
bool hasHitDiagonalLeft() {
  j = 0;
  while (switch3 == 0 || switch4 == 0) {
    j++;
    if (j > TH) {
      buzzer(2);
      return true;
      break;
    }
  }
  return false;
}

void buzzer(int t) {
  for (int i = 1; i <= t; i++) {
    buzzer0 = 1;
    wait_ms(50);
    buzzer0 = 0;
    wait_ms(25);
  }
}

void buzzer_long(int t) {
  for (int i = 1; i <= t; i++) {
    buzzer0 = 1;
    wait_ms(200);
    buzzer0 = 0;
    wait_ms(25);
  }
}

void wait_ms(int ms) { ThisThread::sleep_for(ms); }

void forward(int speed, int ms) {
  stop(200);
  m0.run(-speed);
  m3.run(-speed);
  m1.run(speed);
  m2.run(speed);
  if (ms > 0) {
    wait_ms(ms);
  }
}

void back(int speed, int ms) {
  stop(200);
  m1.run(-speed);
  m2.run(-speed);
  m0.run(speed);
  m3.run(speed);
  if (ms > 0) {
    wait_ms(ms);
  }
}

void left(int speed, int ms) {
  stop(200);
  m0.run(-speed);
  m1.run(-speed);
  m2.run(speed);
  m3.run(speed);
  if (ms > 0) {
    wait_ms(ms);
  }
}

void right(int speed, int ms) {
  stop(200);
  m2.run(-speed);
  m3.run(-speed);
  m0.run(speed);
  m1.run(speed);
  if (ms > 0) {
    wait_ms(ms);
  }
}

void diagonalRight(int speed, int ms) {
  stop(200);
  m1.run(speed);
  m3.run(-speed);
  m0.run(0);
  m2.run(0);
  if (ms > 0) {
    wait_ms(ms);
  }
}

void diagonalLeft(int speed, int ms) {
  stop(200);
  m1.run(-speed);
  m3.run(speed);
  m2.run(0);
  m0.run(0);
  if (ms > 0) {
    wait_ms(ms);
  }
}

void stop(int milisecond) {
  m0.run(0);
  m1.run(0);
  m2.run(0);
  m3.run(0);
  if (milisecond == 0) {
    while (1)
      ;
  } else {
    wait_ms(milisecond);
  }
}

void rotate(int angle) {
  stop(200);
  if (angle >= 0) {
    m0.run(-22);
    m1.run(-22);
    m2.run(-18);
    m3.run(-18);
    wait_ms(1900 * angle / 90);
  } else if (angle < 0) {
    m0.run(22);
    m1.run(22);
    m2.run(18);
    m3.run(18);
    wait_ms(1900 * (-angle) / 90);
  }
  m0.run(0);
  m1.run(0);
  m2.run(0);
  m3.run(0);
}

void forwardToWall(int speed, int modifierF1, int modifierF2) {
  forward(speed);
  while (1) {
    if (switch0 == 0 && switch7 == 1) {
      m1.run(0);
      m2.run(0);
      m0.run(-20);
      m3.run(-20);
    } else if (switch0 == 1 && switch7 == 0) {
      m0.run(0);
      m3.run(0);
      m1.run(+20);
      m2.run(+20);
    } else if (switch5 == 0 || switch6 == 0) {
      m0.run(m0.get_speed() - 25 - modifierF1);
      m1.run(m1.get_speed() - 10);
      m2.run(m2.get_speed() + 25 + modifierF1);
      m3.run(m3.get_speed());
      wait_ms(1000);
      m0.run(m0.get_speed() + 25 + modifierF1);
      m1.run(m1.get_speed() + 10);
      m2.run(m2.get_speed() - 25 - modifierF1);
      m3.run(m3.get_speed());
      wait_ms(1000);
    } else if (switch1 == 0 || switch2 == 0) {
      m0.run(m0.get_speed());
      m1.run(m1.get_speed() + 25 + modifierF2);
      m2.run(m2.get_speed());
      m3.run(m3.get_speed() - 25 - modifierF2);
      wait_ms(1000);
      m0.run(m0.get_speed());
      m1.run(m1.get_speed() - 25 - modifierF2);
      m2.run(m2.get_speed());
      m3.run(m3.get_speed() + 25 + modifierF2);
      wait_ms(1000);
    }
    if (hasHitForward()) break;
  }
}

void backToWall(int speed, int modifierB1, int modifierB2) {
  back(speed);
  printf("d\n");
  while (1) {
    if (switch3 == 0 && switch4 == 1) {
      m1.run(0);
      m2.run(0);
      m0.run(+20);
      m3.run(+20);
    } else if (switch3 == 1 && switch4 == 0) {
      m0.run(0);
      m3.run(0);
      m1.run(-20);
      m2.run(-20);
    } else if (switch5 == 0 || switch6 == 0) {
      left(30,500);
      // m0.run(m0.get_speed());
      // m1.run(m1.get_speed() - 30 - modifierB1);
      // m2.run(m2.get_speed());
      // m3.run(m3.get_speed() + 30 + modifierB1);
      // wait_ms(1000);
      // m0.run(m0.get_speed());
      // m1.run(m1.get_speed() + 30 + modifierB1);
      // m2.run(m2.get_speed());
      // m3.run(m3.get_speed() - 30 - modifierB1);
      wait_ms(1000);
    } else if (switch1 == 0 || switch2 == 0) {
      right(30,500);
      // m0.run(m0.get_speed() + 25 + modifierB2);
      // m1.run(m1.get_speed());
      // m2.run(m2.get_speed() - 25 - modifierB2);
      // m3.run(m3.get_speed());
      // wait_ms(1000);
      // m0.run(m0.get_speed() - 25 - modifierB2);
      // m1.run(m1.get_speed());
      // m2.run(m2.get_speed() + 25 + modifierB2);
      // m3.run(m3.get_speed());
      wait_ms(1000);
    }
    if (hasHitBack()) break;
  }
}

void leftToWall(int speed, int modifierL1, int modifierL2) {
  left(speed);
  while (1) {
    if (switch1 == 0 && switch2 == 1) {
      m0.run(0);
      m1.run(0);
      m2.run(+20);
      m3.run(+20);
    } else if (switch1 == 1 && switch2 == 0) {
      m2.run(0);
      m3.run(0);
      m0.run(-20);
      m1.run(-20);
    } else if (switch3 == 0 || switch4 == 0) {
      m0.run(m0.get_speed() - 25 - modifierL1);
      m1.run(m1.get_speed());
      m2.run(m2.get_speed() + 25 + modifierL1);
      m3.run(m3.get_speed());
      wait_ms(1000);
      m0.run(m0.get_speed() + 25 + modifierL1);
      m1.run(m1.get_speed());
      m2.run(m2.get_speed() - 25 - modifierL1);
      m3.run(m3.get_speed());
      wait_ms(1000);
    } else if (switch0 == 0 || switch7 == 0) {
      m0.run(m0.get_speed());
      m1.run(m1.get_speed() - 25 - modifierL2);
      m2.run(m2.get_speed());
      m3.run(m3.get_speed() + 25 + modifierL2);
      wait_ms(1000);
      m0.run(m0.get_speed());
      m1.run(m1.get_speed() + 25 + modifierL2);
      m2.run(m2.get_speed());
      m3.run(m3.get_speed() - 25 - modifierL2);
      wait_ms(1000);
    }
    if (hasHitLeft()) break;
  }
}

void rightToWall(int speed, int modifierR1, int modifierR2) {
  right(speed);
  while (1) {
    if (switch5 == 0 && switch6 == 1) {
      m2.run(0);
      m3.run(0);
      m0.run(+20);
      m1.run(+20);
    } else if (switch5 == 1 && switch6 == 0) {
      m0.run(0);
      m1.run(0);
      m2.run(-20);
      m3.run(-20);
    } else if (switch3 == 0 || switch4 == 0) {
      forward(30, 500);
      wait_ms(1000);
      // m0.run(m0.get_speed());
      // m1.run(m1.get_speed() + 25 + modifierR1);
      // m2.run(m2.get_speed());
      // m3.run(m3.get_speed() - 25 - modifierR1);
      // wait_ms(1000);
      // m0.run(m0.get_speed());
      // m1.run(m1.get_speed() - 25 - modifierR1);
      // m2.run(m2.get_speed());
      // m3.run(m3.get_speed() + 25 + modifierR1);
      // wait_ms(1000);
    } else if (switch0 == 0 || switch7 == 0) {
      back(30,500);
      wait_ms(1000);
      // m0.run(m0.get_speed() + 25 + modifierR2);
      // m1.run(m1.get_speed());
      // m2.run(m2.get_speed() - 25 - modifierR2);
      // m3.run(m3.get_speed());
      // wait_ms(1000);
      // m0.run(m0.get_speed() - 25 - modifierR2);
      // m1.run(m1.get_speed());
      // m2.run(m2.get_speed() + 25 + modifierR2);
      // m3.run(m3.get_speed());
      // wait_ms(1000);
    }
    if (hasHitRight()) break;
  }
}

void diagonalRightToWall(int speed) {
  diagonalRight(speed);
  while (true) {
    if (hasHitDiagonalRight()) break;
  }
}
void diagonalLeftToWall(int speed) {
  diagonalLeft(speed);
  while (true) {
    if (hasHitDiagonalLeft()) break;
  }
}