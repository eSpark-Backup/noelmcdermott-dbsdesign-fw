#pragma once
#include <Arduino.h>
#include "variable_init.hpp"
#include "LED.hpp"
#include "EVENTS.hpp"


#define MAX_ENCODER_VAL 4095
#define MAX_VOLTAGE 3.3

class Encoder {
public:
  void setup();
  void encoderRunning();
  float getEncoderValue();

private:
  long encoder_val;
  long motor_position;
  static void encoderPinChangeA();
  static void encoderPinChangeB();

  static Encoder* instance;
};