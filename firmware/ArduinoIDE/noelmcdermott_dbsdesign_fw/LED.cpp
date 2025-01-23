#include "LED.hpp"


void DBS_LED::setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(STATUS_02_LED, OUTPUT);
  pinMode(RUN_LED, OUTPUT);
  pinMode(TEST_LED, OUTPUT);
  //   pinMode(DRIVER_POWER_V11, OUTPUT);
  //   pinMode(KILL_RELAY_V10, OUTPUT);
  //   pinMode(BUZZER_PIN, OUTPUT);
  //   pinMode(CS_PIN, OUTPUT);
  pinMode(LAMBDA_CS1_PIN, OUTPUT);
}

void DBS_LED::O2StatusLED(){
  digitalWrite(STATUS_02_LED, LOW);
  delay(100);
  digitalWrite(STATUS_02_LED, HIGH);
  delay(100);
}