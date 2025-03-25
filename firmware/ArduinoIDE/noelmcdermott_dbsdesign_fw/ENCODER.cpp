#include "LED.hpp"
#include "EVENTS.hpp"
#include "ENCODER.hpp"
#include "variable_init.hpp"

RotaryEncoder *encoderInstance = nullptr;

Encoder::Encoder()
  : encod(ENCODER_OUT_A, ENCODER_OUT_B, RotaryEncoder::LatchMode::TWO03) {}

IRAM_ATTR void Encoder::checkPositionInterrupt()
{
  encoderInstance->tick();
}

void Encoder::setup()
{
  encoderInstance = new RotaryEncoder(ENCODER_OUT_A, ENCODER_OUT_B, RotaryEncoder::LatchMode::TWO03);
  attachInterrupt(digitalPinToInterrupt(ENCODER_OUT_A), checkPositionInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_OUT_B), checkPositionInterrupt, CHANGE);
}

float Encoder::getEncoderVoltage()
{
  int position = encoderInstance->getPosition();
  position = min(position, MAX_ENCODER_VAL);
  Serial.print("The position of encoder is:");
  Serial.println(position);
  
  double positionfloat = (position * MAX_VOLTAGE) / MAX_ENCODER_VAL;
  positionfloat = min(positionfloat, MAX_VOLTAGE);
  Serial.print("The voltage of encoder is:");
  Serial.println(positionfloat);

  return positionfloat;
}