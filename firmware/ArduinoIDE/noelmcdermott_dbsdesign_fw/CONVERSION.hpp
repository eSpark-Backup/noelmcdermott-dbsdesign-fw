
#pragma once
#include <Arduino.h>
#include "EVENTS.hpp"
#include "variable_init.hpp"

#define minADCValue 819   // Approximate value for 4mA
#define maxADCValue 4095  // Approximate value for 20mA

class MilliAmp_Conv {
public:
  enum class Scale {
    MilliAmp,
    Voltage
  };
  float current_mA();
  float voltage_V();
  float readExternalInput(Scale scale);
private:
  float sensorValue;
  float current = 0;
  float volatge = 0;
};
