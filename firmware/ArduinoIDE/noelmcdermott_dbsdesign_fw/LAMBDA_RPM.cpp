#include "LED.hpp"
#include "LAMBDA_RPM.hpp"
#include "variable_init.hpp"

Lambda::Lambda(): 
  lamda(LAMBDA_CS1_PIN){}

void Lambda::LambdaSetup()
{
  pinMode(LAMBDA_CS1_PIN, OUTPUT);
  lamda.transmission();
  Lambda::O2Value     = lamda.O2Read();
  Lambda::rpmValue    = lamda.rpmRead();
  Lambda::AFRValue    = lamda.afrGasolineRead ();
  Lambda::State_value = lamda.stateTextRead();
}

void Lambda::setup()
{
  lamda.SPIbeginsettings(500000); 
  lamda.begin();                   
  lamda.rpmBegin();
}

int Lambda::getRPM()
{
  Serial.print("RPM: ");
  Serial.println(Lambda::rpmValue);
  return Lambda::rpmValue;
}

float Lambda::getAF()
{ 
  Serial.print("State: ");
  Serial.println(Lambda::State_value);
  Serial.print("  %O2: ");
  Serial.println(Lambda::O2Value);
  Serial.print("AFR value: ");
  Serial.println(Lambda::AFRValue);
  return Lambda::AFRValue;
}