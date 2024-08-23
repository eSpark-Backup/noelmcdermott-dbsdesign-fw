
#pragma once
#include<Arduino.h>
  
  #define RED_LED             38
  #define GREEN_LED           39
  #define STATUS_02_LED       40
  #define RUN_LED             41
  #define TEST_LED            42
  #define BUZZER_PIN          5
  #define KILL_RELAY_V10      4 // RELAY PIN
  #define DRIVER_POWER_V11    11 // Enable PIN
  #define DIR_PIN             10 // Direction
  #define STEP_PIN            9 // Step
  #define CS_PIN              15 // Chip select
  #define SW_MOSI             13 // Software Master Out Slave In (MOSI)
  #define SW_MISO             12 // Software Master In Slave Out (MISO)
  #define SW_SCK              14 // Software Slave Clock (SCK)
  
class DBS_LED
{
  public:
    void setup();
};  