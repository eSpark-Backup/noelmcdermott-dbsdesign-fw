#include <Arduino.h>
#include "variable_init.hpp"
#include "ERROR_HANDLER.hpp"

#define debounceTime          20
#define doublePressInterval  2000

/*third implmentations*/
volatile bool buttonPressed = false;

int DoublePressCount = 0;

/*ISR */
void buttonPressISR()
{
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  // Debounce check
  if (interruptTime - lastInterruptTime > debounceTime) {
    buttonPressed = true;
    lastInterruptTime = interruptTime;
  }
}

/*ISR Setup*/
void ErrorHandler::InterruptSetup(int pin)
{
  Serial.println("Interrupt setup");
  attachInterrupt(digitalPinToInterrupt(pin), buttonPressISR, FALLING);
}

/*Check double press implementation*/
bool ErrorHandler::checkResetButton(int pin)
{
  if (buttonPressed)
  {
    unsigned long currentTime = millis();
    buttonPressed = false;

    if (currentTime - ErrorHandler::lastPressTime <= doublePressInterval && ErrorHandler::lastPressTime != 0)
    {
      Serial.println("Double press detected. Press count: TRUE ");
      ErrorHandler::lastPressTime = 0;
      DoublePressCount = 2;
      return false;
    }
    else
    {
      // First press in sequence
      Serial.println("Single press detected.");
      lastPressTime = currentTime;

      return true;
    }
  }
  return true;
}
