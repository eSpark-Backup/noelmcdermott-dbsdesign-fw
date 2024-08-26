#include "CONVERSION.hpp"


float MilliAmp_Conv::current_mA() {
  sensorValue = analogRead(EXTERNAL_INPUT);
  // Map the sensor value from 4mA (819) to 20mA (4095) range
  current = map(sensorValue, minADCValue, maxADCValue, 4, 20);
  return current;
}
float MilliAmp_Conv::voltage_V() {
  sensorValue = analogRead(EXTERNAL_INPUT);
  // Map the sensor value from 4mA (1023) to 20mA (4095) range
  volatge = map(sensorValue, minADCValue, maxADCValue, 0, 3.3);
  return volatge;
}
float MilliAmp_Conv::readExternalInput(Scale scale) {
  if (scale == Scale::MilliAmp) {
    return current_mA();
  } else if (scale == Scale::Voltage) {
    return voltage_V();
  }
  return 0.0;
}