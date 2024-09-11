#pragma once

#include <Lambda_rpm.h>
#include "LED.hpp"
#include "Stepper_States.hpp"

class Lambda {
public:
  Lambda()
    : lamda(LAMBDA_CS1_PIN) {}
  void setup();
  int getRPM();
  float getAF();


private:
  Lambda_rpm lamda;
};
