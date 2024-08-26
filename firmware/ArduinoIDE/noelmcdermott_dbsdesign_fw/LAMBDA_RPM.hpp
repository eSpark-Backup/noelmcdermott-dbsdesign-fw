

#pragma once

#include <Lambda_rpm.h>
#include "LED.hpp"

class Lambda {
public:
  Lambda()
    : lambda1(LAMBDA_CS1_PIN) {}
  void setup();
  int rpm();
  float AFcalculation();


private:
  Lambda_rpm lambda1;
};
