#include "motor.h"

#include <mbed.h>

#include "config.h"

Motor::Motor(DigitalOut &_dir, PwmOut &_pulse, float _motor_ratio)
    : dir(_dir), pulse(_pulse), motor_ratio(_motor_ratio) {}

  void Motor::run(int speed) {
    current_speed=speed;
    if (speed < -40) {
      speed = -40;
    } else if (speed > 40) {
      speed = 40;
    }
    if (speed > 0) {
      dir = isInvert;
      pulse = ((float)speed / 100) * motor_ratio;
    } else if (speed < 0) {
      dir = !isInvert;
      pulse = ((float)-speed / 100) * motor_ratio;
    } else {
      pulse = 0;
    }


  }

  int Motor::get_speed() {
      return current_speed;
  }

