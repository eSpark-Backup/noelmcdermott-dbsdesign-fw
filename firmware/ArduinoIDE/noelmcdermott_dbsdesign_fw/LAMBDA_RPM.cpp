#include "LAMBDA_RPM.hpp"


float  AFRValue = 0;
int    rpmValue = 0;
String State_value = "NONE";
float  O2Value = 0;

Lambda::Lambda(): 
  lamda(LAMBDA_CS1_PIN){ 
  }

void Lambda::LambdaSetup(){
  
  lamda.transmission();
  State_value=lamda.stateTextRead();//State of the lambda probe
  O2Value=lamda.O2Read();//%O2
  AFRValue = lamda.afrGasolineRead ();//AFR
  rpmValue = lamda.rpmRead();//RPM

  //   Serial.print("\t");  
  // Serial.print(" Estate: ");
  // Serial.print(State_value);
  // Serial.print("\t");

  // // /*%O2*/
  // Serial.print(" %O2: ");
  // if (lamda.validO2Read()!=true){//verify that the O2 sensor measurement is valid.//Compruebo que la medición del sensor de O2 es válida.
  //   Serial.print(O2Value,2);///print %O2 in the arduino IDE via the USART_USB//imprimo %O2 en la IDE de arduino por medio del USART_USB
  // }else{
  //   Serial.print("------");
  // }

    /*AFR*/
  //   Serial.print(" AFR Petrol: ");
  // if (lamda.validO2Read()!=true){//verify that the O2 sensor measurement is valid.//Compruebo que la medición del sensor de O2 es válida.
  //   Serial.print(AFRValue,2);
  // }else{
  //   Serial.print("------");
  // }
  
  // /*RPM*/
  // Serial.print("\t");
  // Serial.print(" rpm: ");
  // Serial.print(rpmValue);  
  // Serial.print("\t");
   
  // Serial.print("\n\r");  
  
}


void Lambda::setup() {
  lamda.SPIbeginsettings(500000);              // edite in SPI.begin to SPI.begin(SW_SCK, SW_MISO, SW_MOSI)
  // SPI.begin(SW_SCK, SW_MISO, SW_MOSI);  
  lamda.begin();                   
  lamda.rpmBegin();
    }

int Lambda::getRPM() {

  Serial.print("rpmValue: ");
  Serial.println(rpmValue);
  return rpmValue;
    }

float Lambda::getAF() { 
    Serial.print(" Estate: ");
    Serial.println(State_value);
    Serial.print("  %O2: ");
    Serial.println(O2Value);
    Serial.print("AFR value: ");
    Serial.println(AFRValue);
    return AFRValue;
     }



