

#include "ERROR_HANDLER.hpp"

bool ErrorHandler::isError() {
  return ((OVER_CURRENT_V17 == 1) || (OVER_RATING_V18 == 1));
}

bool ErrorHandler::checkResetButton() {
  while (true) {
    buttonState = digitalRead(RESET_V9);
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
      break;
    }
  }
  return 1;
}