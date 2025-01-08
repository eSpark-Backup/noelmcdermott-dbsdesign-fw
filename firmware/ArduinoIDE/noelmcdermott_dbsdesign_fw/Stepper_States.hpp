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
#include "BUTTON.hpp"

class Encoder;
class ErrorHandler;
class Lambda;

#define MAX_DRIVER_CURRENT_V16 20  //(20mA) maximum allowable driver current
#define DRIVER_POWER_V11    11 // Enable PIN
#define DIR_PIN             10 // Direction
#define STEP_PIN            9 // Step
#define CS_PIN              15 // Chip select
#define SW_MOSI             13 // Software Master Out Slave In (MOSI)
#define SW_MISO             12 // Software Master In Slave Out (MISO)
#define SW_SCK              14 // Software Slave Clock (SCK)
// #define LAMBDA_CS1_PIN      16  // CS pin for lambda sheet


class Stepper {
public:
  Stepper(): driver(CS_PIN){
  SPI.begin(SW_SCK, SW_MISO, SW_MOSI, CS_PIN);                         // Initialize SPI
  driver.begin();                       // Initialize driver with default settings
  driver.rms_current(1000);              // Set motor RMS current
  driver.en_pwm_mode(1); 
  // driver.microsteps(16);
  digitalWrite(DRIVER_POWER_V11, LOW);
  };

  void stepperInitialize();
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
  TMC2160Stepper driver;  // Member object
  Display *display = new Display();
  Encoder *encoder;
  ErrorHandler *errorHand;
  Lambda *lamd;
  float ENCODER_VAL_IN_VOLT_V13;
  unsigned long soundTimer;
  int currentPositionFromHomeV5 = 0;
  int position22 = 0;
  int homePositionV2_5 = 0;
  int overCurrentV17 = 0;
  int overRatingV18 = 0;
  int v7ConvAfrV73 = 0;
  int halSensorConRpmV8 = 0;
  float convVoltageV14 = 0;
  float convCurrentV14 = 0;
  int positionV2_4 = 0;
  unsigned long lastTime = 0;
  float rpm = 0;
};