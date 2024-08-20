
#pragma once
#include<Arduino.h>

  #define RED_LED             1
  #define GREEN_LED           2
  #define AMBER_LED           3
  #define STATUS_02_LED       4
  #define BUZZER_PIN          0
  #define DRIVER_POWER_V11    38 // Enable PIN
  #define KILL_RELAY_V10      39 // RELAY PIN
  #define DIR_PIN             55 // Direction
  #define STEP_PIN            54 // Step
  #define CS_PIN              42 // Chip select
  #define SW_MOSI             66 // Software Master Out Slave In (MOSI)
  #define SW_MISO             44 // Software Master In Slave Out (MISO)
  #define SW_SCK              64 // Software Slave Clock (SCK)
  
class DBS_LED
{
  public:
    void init();
    void setup();
};  