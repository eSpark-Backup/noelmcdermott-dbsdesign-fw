#pragma once

#include "ENCODER.hpp"
#include "DISPLAY.hpp"
#include <TMCStepper.h>
#include "LAMBDA_RPM.hpp"
#include "ERROR_HANDLER.hpp"
#include "variable_init.hpp"

class Encoder;
class ErrorHandler;

#define DIR_PIN 10
#define STEP_PIN 9
#define CS_PIN  15 
#define SW_MOSI 13
#define SW_MISO 12
#define SW_SCK  14 

class Stepper {
public:
  Stepper()
    : driver(CS_PIN) {
    SPI.begin(SW_SCK, SW_MISO, SW_MOSI);
    driver.begin();
    driver.rms_current(1000);
    driver.en_pwm_mode(1);
    driver.microsteps(16);
    digitalWrite(DRIVER_POWER_V11, LOW);
  };

  void stepperInitialize();
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
  void inRange();
  void outOfRange();
  void runStepper(int speed, int steps);
  void setEncoderButtonState(bool state);
  void setoverRatingV18(bool state);
  void setoverCurrentV17(bool state);
  bool getoverRatingV18();
  bool getoverCurrentV17();

private:
  TMC2160Stepper driver;
  Display *display = new Display();
  Encoder encoder;
  ErrorHandler *errorHand = new ErrorHandler();
  Lambda *lamd = new Lambda();

  float ENCODER_VAL_IN_VOLT_V13;
  unsigned long soundTimer;
  int currentPositionFromHomeV5 = 0;
  int position22 = 0;
  int homePositionV2_5 = 0;
  bool overCurrentV17 = 0;
  bool overRatingV18 = 0;
  float v7ConvAfrV73 = 0;
  int halSensorConRpmV8 = 0;
  float convVoltageV14 = 0;
  float convCurrentV14 = 0;
  int positionV2_4 = 0;
  unsigned long lastTime = 0;
  float rpm = 0;
};
