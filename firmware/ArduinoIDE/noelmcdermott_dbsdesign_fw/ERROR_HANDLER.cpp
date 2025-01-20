 
#include "ERROR_HANDLER.hpp"


/*third implmentations*/
volatile int pressCount = 0; // Counter for valid double presses
volatile unsigned long lastPressTime = 0; // Tracks the time of the last press
volatile bool buttonPressed = false; // Tracks if the button was pressed
const unsigned long debounceTime = 20; // Debounce time in ms
const unsigned long doublePressInterval = 2000; // Time window fo


bool ErrorHandler::isError() {
  return ((overCurrentV17 == 1) || (overRatingV18 == 1));
}

/*ISR */
void buttonPressISR() {
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  // Debounce check
  if (interruptTime - lastInterruptTime > debounceTime) {
    buttonPressed = true;  // Set flag for processing in loop
    lastInterruptTime = interruptTime;
  }
}

/*ISR Setup*/
void ErrorHandler::InterruptSetup(int pin){
  Serial.print("Interrupt setup");
  attachInterrupt(digitalPinToInterrupt(pin), buttonPressISR, FALLING);
}

/*CHeck double press implementation*/

bool ErrorHandler::checkResetButton(int pin) {
  if (buttonPressed) {
    unsigned long currentTime = millis();
    buttonPressed = false;

    if (currentTime - lastPressTime <= doublePressInterval && lastPressTime != 0) {
      pressCount++;
      Serial.println("Double press detected. Press count: TRUE ");

      lastPressTime = 0;
      pressCount = 0;
      return false;
    } else {
      // First press in sequence
      Serial.println("Single press detected.");
      lastPressTime = currentTime;
    }
  }
  return true;
}
