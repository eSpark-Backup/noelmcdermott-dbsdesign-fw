#pragma once
#include<Arduino.h>
#include <TMCStepper.h>
#include "LED.hpp"
#include "Stepper_States.hpp"
#include "variable_init.hpp"

#define MODE_SELECT_V12                 5               //mode selection switch state (“Run” = 1, “Test” = 0)
#define EXTERNAL_INPUT                  A0               //EXTERNAL INPUT
#define LIMIT_SWITCH                     6               //LIMIT SWITCH
#define RESET_V9                         7               //RESET PUSH BUTTTON


// extern TMC2160Stepper driver;

class Events
{
  public:
    void setup();
    void errorEvents();
    void resetErrorEvent();
};  