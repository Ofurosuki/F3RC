#include "ir.h"

#include <mbed.h>

#include "ReceiverIR.h"

uint8_t keyword[] = {0x8C, 0xE0, 0x00};

void waitSignal(PinName pin) {
  // printf("start waitSignal\n");
  ReceiverIR ir(pin);

  RemoteIR::Format format;
  uint8_t buffer[16];
  while (true) {
    if (ir.getState() != ReceiverIR::Received) continue;

    ir.getData(&format, buffer, sizeof(buffer) * 8);

    // printf("receive signal\n");

    for (uint8_t i = 0; i < sizeof(keyword); i++) {
      if (buffer[i] != keyword[i]) continue;
    }
    break;
  }
}
