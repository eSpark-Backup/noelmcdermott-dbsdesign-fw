#include "CONVERSION.hpp"


float Conversion::current_mA() {
  int sensorValue = analogRead(EXTERNAL_INPUT);
  // Map the sensor value from 4mA (819) to 20mA (4095) range
  float current = map(sensorValue, minADCValue, maxADCValue, 4, 20);
  return current;
}
float Conversion::voltage_V() {
  int sensorValue = analogRead(EXTERNAL_INPUT);
  // Map the sensor value from 0 (819) to 3.3 (4095) range
  float volatge = map(sensorValue, minADCValue, maxADCValue, 0, 3.3);
  return volatge;
}
float Conversion::readExternalInput(Scale scale) {
  if (scale == Scale::MilliAmp) {
    return current_mA();
  } else if (scale == Scale::Voltage) {
    return voltage_V();
  }
  return 0.0;
}