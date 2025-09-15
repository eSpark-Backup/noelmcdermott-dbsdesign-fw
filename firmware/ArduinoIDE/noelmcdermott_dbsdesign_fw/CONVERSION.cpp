#include <Arduino.h>
#include "CONVERSION.hpp"
#include "variable_init.hpp"

float Conversion::current_mA()
{
  uint16_t sensorValue = analogRead(EXTERNAL_INPUT);
  // Map the sensor value from 4mA (819) to 20mA (3550) range
  float current_mA = map(sensorValue, minADCValue, maxADCValue, 0, 24000) / 1000.0f;
  current_mA = max((round(current_mA * 10.0f) / 10.0f), 0.0f);
  Serial.print("Sensor Current:");
  Serial.print(current_mA);
  Serial.println("mA");
  return current_mA;
}

float Conversion::voltage_V()
{
  uint16_t sensorValue = analogRead(EXTERNAL_INPUT);
  uint16_t sensorValue = 2048;
  // Map the sensor value from 0 (819) to 3.3 (4095) range
  float voltage = map(sensorValue, minADCValue, maxADCValue, 0, 3300) / 1000.0f;
  voltage = max((round(voltage * 10.0f) / 10.0f),0.0f);
  Serial.print("Sensor Voltage:");
  Serial.print(voltage);
  Serial.println("V");
  return voltage;
}

float Conversion::readExternalInput(Scale scale)
{
  if (scale == Scale::MilliAmp) {
    return current_mA();
  } else if (scale == Scale::Voltage) {
    return voltage_V();
  }
  return 0.0;
}