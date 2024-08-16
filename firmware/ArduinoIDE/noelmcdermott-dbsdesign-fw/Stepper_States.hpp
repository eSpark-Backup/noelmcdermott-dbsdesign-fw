#pragma once
#include<Arduino.h>
#include "LED.hpp"
#include "EVENTS.hpp"
#include"AnalogEvent.hpp"
#include <TMCStepper.h>
#include "variable_init.hpp"

       

#define MAX_DRIVER_CURRENT_V16           20           //(20mA) maximum allowable driver current

// extern MilliAmp_Conv milli_Conv;
extern TMC2160Stepper driver;

class StepperState
{
  public:
  void setup();
  void homingState();
  void run();
  void test();
  float getMotorCurrent();
  bool overCurrentEvent();
  void moveClockwise();
  void moveAnticlockwise() ;
  void stopStepper();
  void enableStepper();
  // void overCurrentEvent();
  // float getMotorCurrent();

};