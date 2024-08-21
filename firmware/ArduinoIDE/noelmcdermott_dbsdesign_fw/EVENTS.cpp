#include "EVENTS.hpp"

int OVER_CURRENT_V17 = 0;
int OVER_RATING_V18 = 0;

void Events::setup(Display *dis) {
  display = dis;
  pinMode(LIMIT_SWITCH, INPUT);
  pinMode(RESET_V9, INPUT);
  pinMode(ENCODER_BUTTON,INPUT);
}

void Events::errorEvents() {

  digitalWrite(DRIVER_POWER_V11, HIGH);
  digitalWrite(KILL_RELAY_V10, LOW);

  // Toggle LED and Buzzer
  static unsigned long previousMillis = 0;
  const long interval = 500;  // Interval at which to toggle (milliseconds)


  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Save the last time you toggled the LED/buzzer
    previousMillis = currentMillis;

    // Read the current state of LED and buzzer
    int ledState = digitalRead(RED_LED);
    int buzzerState = digitalRead(BUZZER_PIN);

    // Toggle the state
    digitalWrite(RED_LED, !ledState);
    digitalWrite(BUZZER_PIN, !buzzerState);
  }

  /*DISPALY MESSAGE */

  if (OVER_CURRENT_V17 == 1 && OVER_RATING_V18 == 0) {
    display->show("CRITICAL FAULT", 1);
    display->show("E1:OVERCURRENT", 2);
    display->show("MANUAL RESET REQD", 3);
    display->show("DRIVER POWER IS OFF", 4);
    delay(3000);
    display->clearLCD();
    display->show("E1:OVERCURRENT", 1);
    display->show("MANUAL RESET REQD", 2);
    display->show("TURN MASTER PWR OFF", 3);
    display->show("CHECK BALLSCREW", 4);
    delay(3000);
  } else if (OVER_CURRENT_V17 == 0 && OVER_RATING_V18 == 1) {
    display->show("CRITICAL FAULT", 1);
    display->show("E2:PAST V3/V4 LIMITS", 2);
    display->show("MANUAL RESET REQD", 3);
    display->show("DRIVER POWER IS OFF", 4);
    delay(3000);
    display->clearLCD();
    display->show("CRITICAL FAULT", 1);
    display->show("MANUAL RESET REQD", 2);
    display->show("TURN MASTER PWR OFF", 3);
    display->show("CHK VALUES V3/V4/V5", 4);
  } else if (OVER_CURRENT_V17 == 1 && OVER_RATING_V18 == 1) {
    display->show("CRITICAL FAULT", 1);
    display->show("FAULT: E1 and/or E2", 2);
    display->show("MANUAL RESET REQD", 3);
    display->show("PRESS BUTTON TWICE", 4);
    delay(3000);
  }
}

void Events::resetErrorEvent() {
  OVER_CURRENT_V17 = 0;
  OVER_RATING_V18 = 0;

  /*ADD MASTER RESET FUNCTIONALITY*/

  /* ADD LED AND BUZZER STATUS*/
  digitalWrite(DRIVER_POWER_V11, LOW);
  digitalWrite(KILL_RELAY_V10, HIGH);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(GREEN_LED, HIGH);

  /*DISPALY MESSAGE */
  display->clearLCD();
  delay(1000);
  display->show("NORMAL OPERATION", 1);
  display->show("SELECT MODE RUN/TEST", 2);
}