#include "LED.hpp"
#include <Arduino.h>
#include "variable_init.hpp"

void DBS_LED::setup()
{
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(STATUS_02_LED, OUTPUT);
  pinMode(RUN_LED, OUTPUT);
  pinMode(TEST_LED, OUTPUT);
}

void DBS_LED::O2StatusLED()
{
  digitalWrite(STATUS_02_LED, LOW);
  delay(100);
  digitalWrite(STATUS_02_LED, HIGH);
  delay(100);
}