#include "BUTTON.hpp"
#include "EVENTS.hpp"

Button::Button(uint8_t pin)
  : pin(pin) {}

void Button::setup() {
  pinMode(pin, INPUT);
}

bool Button::read() {
  return digitalRead(pin);
}