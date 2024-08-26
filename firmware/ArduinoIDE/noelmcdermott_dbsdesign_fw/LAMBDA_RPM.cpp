#include "LAMBDA_RPM.hpp"

// Lambda_rpm  lambda1(LAMBDA_CS1_PIN);
void Lambda::setup() {
  lambda1.SPIbeginsettings(500000);  //Sets up SPI communications with the lambda sensor module(long int bauds)  //Establece comunicaciones SPI con el modulo de sonda lambda a una velocidad de (long int bauds)
  lambda1.begin();                   //Turn on the lambda module, it will take a while as it has to warm up.  //Enciende placa lambda, tardara un rato puesto que tiene que calentarse
  lambda1.rpmBegin();
}

int Lambda::rpm() {
  lambda1.transmission();
  int rpmValue = lambda1.rpmRead();
  return rpmValue;
}

float Lambda::AFcalculation() {
  lambda1.transmission();
  float AFvalue = lambda1.afrGasolineRead();
  return AFvalue;
}