#ifndef LAMBDA_RPM_HPP
#define LAMBDA_RPM_HPP

#include <Arduino.h>

#include <Lambda_rpm.h>
#include "LED.hpp"
// #include "Stepper_States.hpp"

class Stepper;

class Lambda {
public:
  Lambda();
  void setup();
  int getRPM();
  float getAF();

private:
  Lambda_rpm lamda;
};


#endif // LAMBDA_RPM_HPP
