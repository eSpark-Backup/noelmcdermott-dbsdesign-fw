#pragma once
#include <Arduino.h>
#include "EVENTS.hpp"

class Button {
public:
  Button(uint8_t pin);
  void setup();
  bool read();

private:
  uint8_t pin;
};
