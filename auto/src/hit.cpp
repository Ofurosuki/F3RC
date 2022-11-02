#include "hit.h"

#include <mbed.h>

#include "config.h"
#include "move.h"

// int j = 0;
// const int TH = 30;

// //前
// bool hasHitForward() {
//   j = 0;
//   while (switch0 == 0 && switch7 == 0) {
//     j++;
//     printf("%d\n", j);
//     if (j > TH) {
//       printf("frontdetected\n");
//       buzzer(2);
//       return true;
//       break;
//     }
//   }
//   return false;
// }

// //後
// bool hasHitBack() {
//   j = 0;
//   // back(10);
//   while (switch3 == 0 && switch4 == 0) {
//     j++;
//     printf("%d\n", j);
//     if (j > TH) {
//       buzzer(2);
//       return true;
//       break;
//     }
//   }
//   return false;
// }

// //左
// bool hasHitLeft() {
//   j = 0;
//   while (switch1 == 0 && switch2 == 0) {
//     j++;
//     if (j > TH) {
//       buzzer(2);
//       return true;
//       break;
//     }
//   }
//   return false;
// }

// //右
// bool hasHitRight() {
//   j = 0;
//   while (switch5 == 0 && switch6 == 0) {
//     j++;
//     if (j > TH) {
//       buzzer(2);
//       return true;
//       break;
//     }
//   }
//   return false;
// }

// //右斜め前
// bool hasHitMiginanamemae() {
//   j = 0;
//   while (switch5 == 0 || switch6 == 0) {
//     j++;
//     if (j > TH) {
//       buzzer(2);
//       return true;
//       break;
//     }
//   }
//   return false;
// }

// //左斜め下
// bool hasHitHidarinanameshita() {
//   j = 0;
//   while (switch3 == 0 || switch4 == 0) {
//     j++;
//     if (j > TH) {
//       buzzer(2);
//       return true;
//       break;
//     }
//   }
//   return false;
// }

// void horizontalCorrect() { forward(30, 1000); }

// void forwardCorrectL() { left(30, 1000); }

// void forwardCorrectR() { right(30, 1000); }

// void backCorrect() { back(30, 1000); }

