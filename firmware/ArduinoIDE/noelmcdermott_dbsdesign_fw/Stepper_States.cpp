#include "Stepper_States.hpp"

TMC2160Stepper driver(CS_PIN, R_SENSE);
MilliAmp_Conv converter;

void StepperState::homingState() {
}

void StepperState::setup(Display *dis) {
  // Setup the TMC2160 driver
  SPI.begin();                 // Initialize SPI
  driver.begin();              // Initialize driver with default settings
  driver.rms_current(500);     // Set motor RMS current
  driver.microsteps(16);       // Set microsteps
  driver.en_pwm_mode(true);    // Enable StealthChop for quiet movement
  driver.pwm_autoscale(true);  // Enable autoscaling of PWM frequency
}


/*RUN MODE*/
void StepperState::run() {
  float currentInput = converter.readExternalInput(MilliAmp_Conv::Scale::MilliAmp);
  float voltageInput = converter.readExternalInput(MilliAmp_Conv::Scale::Voltage);

  if (currentInput >= 4.0f && currentInput < 20.0f) {
    // Move clockwise
    moveClockwise();
  } else if (currentInput > 20.0f && currentInput <= 40.0f) {
    // Move anticlockwise
    moveAnticlockwise();
  }
  /* Display the result*/

  display->show("Mode = Run ", 1);
  String message1 = "MICROSQUIRT INPUT = " + String(voltageInput, 2) + "V";
  display->show(message1, 2);
  String message2 = "RPM = " + String(HAL_SENSOR_CON_RPM_V8);  // NEED TO CALCULATE AND IMPLEMENTATION
  display->show(message2, 3);
  String message3 = "A/F = " + String(V7_CONV_AFR_V73);  // NEED TO CALCULATE AND IMPLEMENTATION
  display->show(message3, 4);
}
void StepperState::moveClockwise() {
  driver.shaft(1);  // Set direction to clockwise

  // Generate steps to move the motor
  for (int i = 0; i < STEPS_PER_REV_V1; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(100);  // Adjust speed with delay
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(100);
  }
}

void StepperState::moveAnticlockwise() {
  driver.shaft(0);  // Set direction to anticlockwise

  // Generate steps to move the motor
  for (int i = 0; i < STEPS_PER_REV_V1; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(100);  // Adjust speed with delay
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(100);
  }
}

void StepperState::test() {
  /*implementation of Test Mode*/
}

float StepperState::getMotorCurrent() {
  uint8_t cs_actual = driver.cs_actual();  // Current scale (0-31)
  // Calculate the current in mA
  float V_fs = 0.325;  // Full-scale voltage across sense resistor (for default settings)
  float I_rms = (V_fs * cs_actual / 32.0) / R_SENSE;
  // Convert I_rms to I_tripmax (peak current)
  float motorCurrent = I_rms * 1.41 * 1000;
  return motorCurrent;  // Return current in mA
}

bool StepperState::overCurrentEvent() {
  float current_mA = getMotorCurrent();  // Assuming this function returns the current in milliamps
  if (current_mA > MAX_DRIVER_CURRENT_V16) {
    OVER_CURRENT_V17 = true;  // Set to true if overcurrent
  } else {
    OVER_CURRENT_V17 = false;  // Set to false otherwise
  }
  return OVER_CURRENT_V17;  // Return the boolean indicating overcurrent status
}

bool StepperState::outOfRangEvent() {
  /*implementation out of range event*/
  return false;
}

void StepperState::stopStepper() {
  driver.toff(0);
}
void StepperState::enableStepper() {
  driver.toff(5);
}
