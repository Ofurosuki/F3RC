#include <mbed.h>

void moveServo(DigitalOut& servo, int us) {
  for (int i = 0; i < 100; i++) {
    servo = 1;
    wait_us(us);
    servo = 0;
    wait_us(20000 - us);
  }
}

void move3Servo(DigitalOut& servo0, int us0, DigitalOut& servo1, int us1,
                DigitalOut& servo2, int us2) {
  for (int i = 0; i < 100; i++) {
    int count0 = 0;
    int count1 = 0;
    int count2 = 0;

    for (int j = 0; j < 2000; j++) {
      count0++;
      count1++;
      count2++;

      servo0 = (count0 <= us0 / 10);
      servo1 = (count1 <= us1 / 10);
      servo2 = (count2 <= us2 / 10);

      wait_us(10);
    }
  }
}