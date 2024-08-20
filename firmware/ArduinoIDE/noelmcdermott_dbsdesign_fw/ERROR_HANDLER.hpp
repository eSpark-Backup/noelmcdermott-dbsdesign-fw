
#pragma once
#include <Arduino.h>
#include "EVENTS.hpp"


class ErrorHandler {
public:
  bool isError();
  bool checkResetButton();

private:
  int buttonState;                  // Current state of the button
  int lastButtonState = LOW;        // Previous state of the button
  unsigned long lastPressTime = 0;  // Time of the last button press
  int pressCount = 0;
};