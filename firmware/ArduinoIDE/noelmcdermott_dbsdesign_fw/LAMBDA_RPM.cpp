#include "LED.hpp"
#include "LAMBDA_RPM.hpp"
#include "variable_init.hpp"

float  AFRVal = 0.0;
String Status = "NONE";
int    rpmVal = 0;

Lambda::Lambda(): 
  lamda(LAMBDA_CS1_PIN){}

void Lambda::LambdaSetup()
{
 
  lamda.transmission();
  Lambda::O2Value     = lamda.O2Read();
  Lambda::rpmValue    = lamda.rpmRead();
  Lambda::AFRValue    = lamda.afrGasolineRead ();
  Lambda::State_value = lamda.stateTextRead();

    Serial.print("\t");  
  Serial.print(" Estate: ");
  Serial.print(State_value);
  Status = State_value;

  Serial.print("\t");

  /*%O2*/
  Serial.print(" %O2: ");
  if (lamda.validO2Read()!=true){
    Serial.print(O2Value,2);
  }else{
    Serial.print("------");
  }

    /*AFR*/
    Serial.print(" AFR Petrol: ");
  if (lamda.validO2Read()!=true){
    AFRVal = AFRValue;
    Serial.print(AFRValue,2);
  }else{
    Serial.print("------");
  }
  
  /*RPM*/
  Serial.print("\t");
  Serial.print(" rpm: ");
  Serial.print(rpmValue);  
  rpmVal = rpmValue;
  Serial.print("\t");
   
  Serial.print("\n\r"); 
  delay(500);
}

void Lambda::setup()
{
  lamda.SPIbeginsettings(500000); 
  lamda.begin();                   
  lamda.rpmBegin();
}

int Lambda::getRPM()
{

 
  return rpmVal;
}

float Lambda::getAF()
{ 
  return AFRVal;
}