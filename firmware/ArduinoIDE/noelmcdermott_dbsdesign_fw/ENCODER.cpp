#include "ENCODER.hpp"
// volatile long motor_position, encoder;

Encoder* Encoder::instance = nullptr;

void Encoder::setup() {

  pinMode(OUT_A, INPUT);
  pinMode(OUT_B, INPUT);
  digitalWrite(OUT_A, HIGH);
  digitalWrite(OUT_B, HIGH);

  instance = this;

  attachInterrupt(0, encoderPinChangeA, CHANGE);
  attachInterrupt(1, encoderPinChangeB, CHANGE);
  encoder_val = 0;
}

void Encoder::encoderPinChangeA() {
  if (digitalRead(OUT_A) == digitalRead(OUT_B)) {
    instance->encoder_val--;
  } else {
    instance->encoder_val++;
  }
}

void Encoder::encoderPinChangeB() {
  if (digitalRead(OUT_A) != digitalRead(OUT_B)) {
    instance->encoder_val--;
  } else {
    instance->encoder_val++;
  }
}


void Encoder::encoderRunning() {
  //do stuff dependent on encoder position here
  //such as move a stepper motor to match encoder position
  //if you want to make it 1:1 ensure the encoder res matches the motor res by dividing/multiplying
  if (encoder_val > 0) {
    digitalWrite(DIR_PIN, HIGH);
    digitalWrite(STEP_PIN, HIGH);
    digitalWrite(STEP_PIN, LOW);
    delay(200);
    motor_position++;
    encoder_val = 0;
  } else if (encoder_val < 0) {
    digitalWrite(DIR_PIN, LOW);
    digitalWrite(STEP_PIN, HIGH);
    digitalWrite(STEP_PIN, LOW);
    delay(200);
    motor_position--;
    encoder_val = 0;
  }
}

float Encoder::getEncoderValue()
{
    float encoder_valu = (encoder_val / MAX_ENCODER_VAL) ;
    encoder_valu = encoder_valu * MAX_VOLTAGE; 
    return encoder_valu;
}



