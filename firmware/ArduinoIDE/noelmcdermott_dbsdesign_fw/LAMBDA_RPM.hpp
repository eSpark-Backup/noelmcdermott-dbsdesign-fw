#ifndef LAMBDA_RPM_HPP
#define LAMBDA_RPM_HPP

#include <Lambda_rpm.h>

#define SW_MOSI 13
#define SW_MISO 12
#define SW_SCK  14 

class Stepper;

class Lambda {
public:
  Lambda();
  void setup();
  int getRPM();
  float getAF();
  void LambdaSetup();

private:
  int    rpmValue = 0;
  float  O2Value  = 0.0;
  float  AFRValue = 0.0;
  String State_value = "NONE";

  Lambda_rpm lamda;
};

#endif  // LAMBDA_RPM_HPP
