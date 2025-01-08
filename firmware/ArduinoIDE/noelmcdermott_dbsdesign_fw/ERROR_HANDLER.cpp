 
#include "ERROR_HANDLER.hpp"

  // static int lastButtonState = true;
  // static unsigned long lastPressTime = 0;  
  // static int pressCount = 0;
  // unsigned long currentTime = millis();

  volatile int pressCount = 0;  // Make pressCount volatile since it is used in an ISR
  volatile unsigned long lastPressTime = 0;  // Used to debounce the button

bool ErrorHandler::isError() {
  return ((overCurrentV17 == 1) || (overRatingV18 == 1));
}

// bool ErrorHandler::checkResetButton(int pin) {
  

//   static int lastButtonState = true;
//   static unsigned long lastPressTime = 0;  
//   static int pressCount = 0;

//   // while (false) {
//    bool buttonState = digitalRead(pin);
//     if (buttonState == false && lastButtonState == true) {
//       // Button was pressed
//       unsigned long currentTime = millis();
//       Serial.print("button press\n");

//       if (currentTime - lastPressTime <= 2000) {
//         // Second press within 2 s
//         pressCount++;
//         Serial.print("button press count: ");
//         Serial.print(pressCount);
//         Serial.print("\n");
//       } else {
//         // Reset count if time exceeds 500 ms
//         pressCount = 1;
//         Serial.print("button press only one time\n");
//       }

//       lastPressTime = currentTime;
//     }

//     lastButtonState = buttonState;

//     if (pressCount == 2) {
//       /*implement the reset functionality*/
//       pressCount = 0;  // Reset count after action
//       lastPressTime = 0;
//       // break;
//       return false;
//     }
//   // }
//   // return 1;
//   return true;
// }
void buttonPressISR() {
  unsigned long currentTime = millis();

  // Debounce logic: only register a press if the time since the last press is above a threshold
  if (currentTime - lastPressTime > 500) {  // 50 ms debounce time
    pressCount++;
    lastPressTime = currentTime;
  }
}

void ErrorHandler::InterruptSetup(int pin){
  Serial.print("Interrupt setup");
  attachInterrupt(digitalPinToInterrupt(pin), buttonPressISR, FALLING);
}



bool ErrorHandler::checkResetButton(int pin) {
  static int localPressCount = 0;  // Keep track of local presses handled
  // static unsigned long lastPressTime = 0;  // Time of the last button press
  bool actionTriggered = true;

  unsigned long currentTime = millis();

  if (pressCount > localPressCount) {
    // A new button press was detected
    Serial.print("Button press count: ");
    Serial.println(pressCount);

    if (currentTime - lastPressTime <= 2000) {
      // Second press detected within 2 seconds
      localPressCount = pressCount;  // Update the local counter
    } else {
      // Timeout: Reset the press count if more than 2 seconds elapsed
      Serial.println("Button press timeout, resetting press count");
      pressCount = 1;  // Reset to 1 for the current press
      localPressCount = 1;
    }

    lastPressTime = currentTime;  // Update the last press time

    if (pressCount >= 2) {
      // Implement the reset functionality
      Serial.println("Reset action triggered");
      pressCount = 0;  // Reset count after action
      localPressCount = 0;  // Reset local counter
      actionTriggered = false;  // Indicate reset action was triggered
    }
  } else if (currentTime - lastPressTime > 2000) {
    // Reset press count if no press within 2 seconds
    pressCount = 0;
    localPressCount = 0;
  }

  return actionTriggered;
}



//  bool ErrorHandler::checkResetButton(int pin) {

//   // attachInterrupt(digitalPinToInterrupt(pin), buttonPressISR, FALLING);

//   static int localPressCount = 0;  // Keep track of local presses handled
//   bool actionTriggered = true;
  

//   if (pressCount > localPressCount) {
//     // A new button press was detected
//     Serial.print("Button press count: ");
//     Serial.println(pressCount);

//     localPressCount = pressCount;  // Update the local counter

//     if (pressCount >= 2) {
//       // Implement the reset functionality
//       Serial.println("Reset action triggered");
//       pressCount = 0;  // Reset count after action
//       localPressCount = 0;  // Reset local counter
//       actionTriggered = false;  // Indicate reset action was triggered
//     }
//   }

//   return actionTriggered;
// }


