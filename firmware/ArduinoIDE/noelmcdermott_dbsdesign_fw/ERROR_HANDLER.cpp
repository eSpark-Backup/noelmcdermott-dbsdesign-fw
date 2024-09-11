 
#include "ERROR_HANDLER.hpp"

bool ErrorHandler::isError() {
  return ((overCurrentV17 == 1) || (overRatingV18 == 1));
}

bool ErrorHandler::checkResetButton(int pin) {

  static int lastButtonState = LOW;
  static unsigned long lastPressTime = 0;  
  static int pressCount = 0;

  // while (true) {
   static int buttonState = digitalRead(pin);
    if (buttonState == HIGH && lastButtonState == LOW) {
      // Button was pressed
      unsigned long currentTime = millis();

      if (currentTime - lastPressTime <= 2000) {
        // Second press within 2 s
        pressCount++;
      } else {
        // Reset count if time exceeds 500 ms
        pressCount = 1;
      }

      lastPressTime = currentTime;
    }

    lastButtonState = buttonState;

    if (pressCount == 2) {
      /*implement the reset functionality*/
      pressCount = 0;  // Reset count after action
      // break;
      return true;
    }
  // }
  // return 1;
  return false;
}