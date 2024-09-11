
#pragma once
#include<Arduino.h>
  
  #define RED_LED             38
  #define GREEN_LED           39
  #define STATUS_02_LED       40
  #define RUN_LED             41
  #define TEST_LED            42
  #define BUZZER_PIN          5
  #define KILL_RELAY_V10      4 // RELAY PIN
  #define LAMBDA_CS1_PIN      16  // CS pin for lambda sheet
  
class DBS_LED
{
  public:
    void setup();
};  