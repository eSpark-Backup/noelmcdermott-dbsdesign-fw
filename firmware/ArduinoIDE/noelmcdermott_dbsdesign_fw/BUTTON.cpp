#include "BUTTON.hpp"

Button::Button(uint8_t pin)
  : pin(pin) {}

void Button::setup() {
  pinMode(pin, INPUT);
  // pinMode(LIMIT_SWITCH, INPUT);
  // pinMode(RESET_V9, INPUT);
}

bool Button::read() {
  return digitalRead(pin);  // Return true if button is pressed
}