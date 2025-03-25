#pragma once

#define minADCValue 819   // Approximate value for 4mA
#define maxADCValue 4095  // Approximate value for 20mA

class Conversion {
public:
  enum class Scale {
    MilliAmp,
    Voltage
  };
  float readExternalInput(Scale scale);
private:
  float current_mA();
  float voltage_V();
};
