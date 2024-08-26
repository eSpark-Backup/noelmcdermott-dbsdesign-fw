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
#include "LAMBDA_RPM.hpp"

class Encoder;
class ErrorHandler;

#define MAX_DRIVER_CURRENT_V16 20  //(20mA) maximum allowable driver current

extern TMC2160Stepper driver;

class StepperState {
public:
  void setup(Display *dis, Encoder *enc, ErrorHandler *error, Lambda *lam);
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
  bool checkRPM();
  // int rpmStepper();
  // static void countPulse();

private:
  Display *display;
  Encoder *encoder;
  ErrorHandler *errorHand;
  Lambda *lamd;
  float ENCODER_VAL_IN_VOLT_V13;
  unsigned long soundTimer;
  int CURRENT_POSITION_FROM_HOME_V5 = 0;
  int HOME_POSITION_V2_5 = 0;
  int V7_CONV_AFR_V73 = 0;
  int HAL_SENSOR_CON_RPM_V8 = 0;
  float CONV_VOLTAGE_V14 = 0;
  float CONV_CURRENT_V14 = 0;
  unsigned long lastTime = 0;
  float rpm = 0;
};