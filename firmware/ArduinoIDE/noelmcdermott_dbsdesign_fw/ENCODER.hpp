#ifndef ENCODER_HPP
#define ENCODER_HPP

#include <RotaryEncoder.h>

#define ENCODER_OUT_A   2
#define ENCODER_OUT_B   21
#define MAX_VOLTAGE     3.3
#define MAX_ENCODER_VAL 255  //1024   // 4096

class Encoder {
public:
  Encoder();
  void setup();
  float getEncoderVoltage();
  static void IRAM_ATTR checkPositionInterrupt();

private:
  RotaryEncoder encod;
};

#endif  // ENCODER_HPP