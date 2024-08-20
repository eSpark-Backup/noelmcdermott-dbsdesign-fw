#include "CONVERSION.hpp"
#include "variable_init.hpp"

float MilliAmp_Conv::current_mA() {
  sensorValue = analogRead(EXTERNAL_INPUT);
  // Map the sensor value from 4mA (819) to 20mA (4095) range
  CONV_CURRENT_V14 = map(sensorValue, minADCValue, maxADCValue, 4, 20);
  return CONV_CURRENT_V14;
}
float MilliAmp_Conv::voltage_V() {
  sensorValue = analogRead(EXTERNAL_INPUT);
  // Map the sensor value from 4mA (1023) to 20mA (4095) range
  CONV_VOLTAGE_V14 = map(sensorValue, minADCValue, maxADCValue, 0, 3.3);
  return CONV_VOLTAGE_V14;
}
float MilliAmp_Conv::readExternalInput(Scale scale) {
  if (scale == Scale::MilliAmp) {
    return current_mA();
  } else if (scale == Scale::Voltage) {
    return voltage_V();
  }
  return 0.0;
}