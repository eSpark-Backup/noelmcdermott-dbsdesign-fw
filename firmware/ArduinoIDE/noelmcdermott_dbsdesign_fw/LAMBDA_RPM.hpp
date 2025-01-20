#ifndef LAMBDA_RPM_HPP
#define LAMBDA_RPM_HPP

#include <Arduino.h>

#include <Lambda_rpm.h>
#include "LED.hpp"

#define SW_MOSI 13  // Software Master Out Slave In (MOSI)
#define SW_MISO 12  // Software Master In Slave Out (MISO)
#define SW_SCK 14   // Software Slave Clock (SCK)

class Stepper;

class Lambda {
public:
  Lambda();
  void setup();
  int getRPM();
  float getAF();
  void LambdaSetup();

private:
  Lambda_rpm lamda;
};


#endif  // LAMBDA_RPM_HPP
