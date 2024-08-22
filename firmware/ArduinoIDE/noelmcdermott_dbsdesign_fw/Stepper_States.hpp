#pragma once
#include <Arduino.h>
#include "LED.hpp"
#include "EVENTS.hpp"
#include "CONVERSION.hpp"
#include <TMCStepper.h>
#include "variable_init.hpp"
#include "DISPLAY.hpp"
#include "ENCODER.hpp"
#include "ERROR_HANDLER.hpp"

class Encoder;
class ErrorHandler;

#define MAX_DRIVER_CURRENT_V16 20  //(20mA) maximum allowable driver current

// extern MilliAmp_Conv milli_Conv;
extern TMC2160Stepper driver;

class StepperState {
public:
  void setup(Display *dis, Encoder *enc, ErrorHandler *error);
  void homePosition();
  void run();
  void test();
  float getMotorCurrent();
  bool overCurrentEvent();
  void moveClockwise(int speed);
  void moveAnticlockwise(int speed);
  void stopStepper();
  void enableStepper();
  bool outOfRangEvent();
  int rpmStepper();
  static void countPulse();
  // void overCurrentEvent();
  // float getMotorCurrent();
private:
  Display *display;
  Encoder *encoder;
  ErrorHandler *errorHand;
  float ENCODER_VAL_IN_VOLT_V13;
  unsigned long soundTimer;
  int CURRENT_POSITION_FROM_HOME_V5 = 0;
  int HOME_POSITION_V2_5 = 0;
  // static volatile unsigned long pulseCount; // To store the number of pulses
  static int pulseCount;
  unsigned long lastTime = 0;
  float rpm = 0;
};