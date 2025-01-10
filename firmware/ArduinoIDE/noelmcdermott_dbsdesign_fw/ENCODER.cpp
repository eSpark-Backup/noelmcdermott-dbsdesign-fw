#include "ENCODER.hpp"
// volatile long motor_position, encoder;

RotaryEncoder *encoderInstance = nullptr;


Encoder::Encoder()
  : encod(ENCODER_OUT_A, ENCODER_OUT_B, RotaryEncoder::LatchMode::TWO03) {}

IRAM_ATTR void Encoder::checkPositionInterrupt()
{
  encoderInstance->tick(); // just call tick() to check the state.
}

void Encoder::setup() {
  encoderInstance = new RotaryEncoder(ENCODER_OUT_A, ENCODER_OUT_B, RotaryEncoder::LatchMode::TWO03);
  attachInterrupt(digitalPinToInterrupt(ENCODER_OUT_A), checkPositionInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCODER_OUT_B), checkPositionInterrupt, CHANGE);

}

void Encoder::encoderTicks() {
  // encod.tick();
}

float Encoder::getEconderVoltage() {
 
  int position = encoderInstance->getPosition();

  position = min(position, MAX_ENCODER_VAL);

  Serial.print("the position of encoder is:");
  
  Serial.println(position);

  double positionfloat = (position * MAX_VOLTAGE) / MAX_ENCODER_VAL;
  
  positionfloat = min(positionfloat, MAX_VOLTAGE);

  Serial.print("the voltage of encoder is:");
  
  Serial.println(positionfloat);

  return positionfloat;
}



