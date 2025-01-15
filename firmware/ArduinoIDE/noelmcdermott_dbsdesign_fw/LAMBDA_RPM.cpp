#include "LAMBDA_RPM.hpp"

// Lambda_rpm  lambda1(LAMBDA_CS1_PIN);

Lambda::Lambda(): 
  lamda(LAMBDA_CS1_PIN){
    
  }

void Lambda::setup() {
  lamda.SPIbeginsettings(500000);  //Sets up SPI communications with the lambda sensor module(long int bauds)  //Establece comunicaciones SPI con el modulo de sonda lambda a una velocidad de (long int bauds)
  lamda.begin();                   //Turn on the lambda module, it will take a while as it has to warm up.  //Enciende placa lambda, tardara un rato puesto que tiene que calentarse
  lamda.rpmBegin();
}

int Lambda::getRPM() {
   lamda.transmission();
  int rpmValue = lamda.rpmRead();
  return rpmValue;
}

float Lambda::getAF() {
   lamda.transmission();
  float AFvalue = lamda.afrGasolineRead();
  return AFvalue;
}
