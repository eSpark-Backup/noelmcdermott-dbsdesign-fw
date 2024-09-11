#include "ENCODER.hpp"
// volatile long motor_position, encoder;

Encoder::Encoder()
  : encod(ENCODER_OUT_A, ENCODER_OUT_B, RotaryEncoder::LatchMode::TWO03) {}

void Encoder::setup() {
}

float Encoder::getEcoderPosition() {
    return encod.getPosition();

}

void Encoder::encoderTicks() {
  encod.tick();
}

float Encoder::getEconderVoltage() {
  float position = Encoder::getEcoderPosition();
  position = (position / MAX_ENCODER_VAL);
  position = position * MAX_VOLTAGE;
  return position;
}

