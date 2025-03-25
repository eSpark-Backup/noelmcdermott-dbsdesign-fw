#include "LED.hpp"
#include <Arduino.h>
#include "EVENTS.hpp"
#include "variable_init.hpp"

bool overRatingV18  = false;
bool overCurrentV17 = false;

void Events::setup(Display *dis)
{
  display = dis;
  pinMode(RESET_V9, INPUT);
  pinMode(LIMIT_SWITCH, INPUT);
}

Events::FaultEvent Events::getEvent()
{
  if (overCurrentV17 == 1 && overRatingV18 == 0)
  {
    return OVER_CURRENT_ONLY;
  }
  else if (overCurrentV17 == 0 && overRatingV18 == 1)
  {
    return OVER_RATING_ONLY;
  }
  else if (overCurrentV17 == 1 && overRatingV18 == 1)
  {
    return BOTH_FAULTS;
  }
  else
  {
    return NO_FAULT;
  }
}

void Events::errorEvents()
{
  digitalWrite(DRIVER_POWER_V11, HIGH);
  digitalWrite(KILL_RELAY_V10, LOW);

  // Toggle LED and Buzzer
  if (millis() > soundTimer)
  {
    soundTimer = millis() + 1000;
    tone(TEST_LED, 500, 500);
    tone(BUZZER_PIN, 500, 500);
    tone(RED_LED, 500, 500);
  }

  // Handle Faults
  switch(getEvent())
  {
    case OVER_CURRENT_ONLY:
      handleOverCurrentOnly();
    break;
    case OVER_RATING_ONLY:
      handleOverRatingOnly();
    break;
    case BOTH_FAULTS:
      handleBothFaults();
    break;
    default:
    break;
  }
}

void Events::resetErrorEvent()
{
  overCurrentV17 = 0;
  overRatingV18 = 0;

  // Add Master Reset Functionality
  digitalWrite(DRIVER_POWER_V11, LOW);
  digitalWrite(KILL_RELAY_V10, HIGH);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(GREEN_LED, HIGH);

  // Display Message
  display->clear();
  delay(1000);
  display->show("NORMAL OPERATION", 1);
  display->show("SELECT MODE RUN/TEST", 2);
}

void Events::handleOverCurrentOnly()
{
  display->show("CRITICAL FAULT", 0);
  display->show("E1:OVERCURRENT", 1);
  display->show("MANUAL RESET REQD", 2);
  display->show("DRIVER POWER IS OFF", 3);
  delay(3000);
  display->clear();
  display->show("E1:OVERCURRENT", 0);
  display->show("MANUAL RESET REQD", 1);
  display->show("TURN MASTER PWR OFF", 2);
  display->show("CHECK BALLSCREW", 3);
  delay(3000);
}

void Events::handleOverRatingOnly()
{
  display->show("CRITICAL FAULT", 0);
  display->show("E2:PAST V3/V4 LIMITS", 1);
  display->show("MANUAL RESET REQD", 2);
  display->show("DRIVER POWER IS OFF", 3);
  delay(3000);
  display->clear();
  display->show("CRITICAL FAULT", 0);
  display->show("MANUAL RESET REQD", 1);
  display->show("TURN MASTER PWR OFF", 2);
  display->show("CHK VALUES V3/V4/V5", 3);
}

void Events::handleBothFaults()
{
  display->show("CRITICAL FAULT", 0);
  display->show("FAULT: E1 and/or E2", 1);
  display->show("MANUAL RESET REQD", 2);
  display->show("PRESS BUTTON TWICE", 3);
  delay(3000);
}
