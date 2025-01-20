#include "CONVERSION.hpp"


float Conversion::current_mA() {
  int sensorValue = analogRead(EXTERNAL_INPUT);
  // Map the sensor value from 4mA (819) to 20mA (4095) range
  float current_mA = map(sensorValue, minADCValue, maxADCValue, 0, 24000);
  current_mA = current_mA / 1000.0f;
  Serial.print("current_mA of sensor:");
  Serial.println(current_mA);
  return current_mA;
}

float Conversion::voltage_V() {
  int sensorValue = analogRead(EXTERNAL_INPUT);
  // Map the sensor value from 0 (819) to 3.3 (4095) range
  float voltage = map(sensorValue, minADCValue, maxADCValue, 0, 3300);
  voltage = voltage / 1000.0f;
  Serial.print("Volages of sensor:");
  Serial.println(voltage);
  return voltage;
}

float Conversion::readExternalInput(Scale scale) {
  if (scale == Scale::MilliAmp) {
    return current_mA();
  } else if (scale == Scale::Voltage) {
    return voltage_V();
  }
  return 0.0;
}