#ifndef ENCODER_HPP
#define ENCODER_HPP

#include <Arduino.h>
#include <RotaryEncoder.h>
#include "variable_init.hpp"
#include "LED.hpp"
#include "EVENTS.hpp"

#define ENCODER_OUT_A                   2
#define ENCODER_OUT_B                   21
#define MAX_ENCODER_VAL                 4095
#define MAX_VOLTAGE                     3.3

class Encoder {
public:
  Encoder();
  void setup();
  void encoderTicks();
  float getEconderVoltage();


private:
float getEcoderPosition();
RotaryEncoder encod;
};

#endif // ENCODER_HPP