#include "EVENTS.hpp"

int OVER_CURRENT_V17 = 0;
int OVER_RATING_V18 = 0;

void Events::setup(Display *dis) {
  display = dis;

}

void Events::errorEvents() {

  digitalWrite(DRIVER_POWER_V11, HIGH);
  digitalWrite(KILL_RELAY_V10, LOW);
  // Toggle LED and Buzzer
     if (millis() > soundTimer) {
        soundTimer = millis() + 1000;
        tone(TEST_LED, 500, 500);  //tone of 500 for 0.8 seconds 800 milliseconds
        tone(BUZZER_PIN, 500, 500);
        tone(RED_LED, 500, 500);
      }
  /*DISPALY MESSAGE */

  if (OVER_CURRENT_V17 == 1 && OVER_RATING_V18 == 0) {
    display->show("CRITICAL FAULT", 1);
    display->show("E1:OVERCURRENT", 2);
    display->show("MANUAL RESET REQD", 3);
    display->show("DRIVER POWER IS OFF", 4);
    delay(3000);
    display->clear();
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
    display->clear();
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
  display->clear();
  delay(1000);
  display->show("NORMAL OPERATION", 1);
  display->show("SELECT MODE RUN/TEST", 2);
}