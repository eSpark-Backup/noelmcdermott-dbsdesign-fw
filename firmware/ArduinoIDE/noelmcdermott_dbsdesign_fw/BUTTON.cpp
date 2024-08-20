#include "BUTTON.hpp"

Button::Button(uint8_t pin)
  : pin(pin) {}

void Button::setup() {
  pinMode(pin, INPUT);
}

bool Button::read() {
  int reading = digitalRead(pin);
  return reading;  // Return true if button is pressed
}