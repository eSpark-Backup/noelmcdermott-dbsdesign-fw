#include "LED.hpp"


void DBS_LED::setup()
{
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(AMBER_LED, OUTPUT);
  pinMode(STATUS_02_LED, OUTPUT);
  pinMode(DRIVER_POWER_V11, OUTPUT);
  pinMode(KILL_RELAY_V10, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}