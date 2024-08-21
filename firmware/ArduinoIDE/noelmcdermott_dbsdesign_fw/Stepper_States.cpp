#include "Stepper_States.hpp"


TMC2160Stepper driver(CS_PIN, R_SENSE);
MilliAmp_Conv converter;
// Encoder encoder;


void StepperState::homingState() {
  
}

void StepperState::setup(Display *dis, Encoder *enc, ErrorHandler *error) {
  // Setup the TMC2160 driver
  SPI.begin();                 // Initialize SPI
  driver.begin();              // Initialize driver with default settings
  driver.rms_current(500);     // Set motor RMS current
  driver.microsteps(16);       // Set microsteps
  driver.en_pwm_mode(true);    // Enable StealthChop for quiet movement
  driver.pwm_autoscale(true);  // Enable autoscaling of PWM frequency
}

void StepperState::test() {
  /*implementation of Test Mode*/
  ENCODER_VAL_IN_VOLT_V13 = MIN_VOLT_V14;
  while (digitalRead(MODE_SELECT_V12) == 0) {
    ENCODER_VAL_IN_VOLT_V13 = encoder->getEconderVoltage();
    if (errorHand->checkResetButton(ENCODER_BUTTON) == 1)  // press button for two second
    {
      digitalWrite(DRIVER_POWER_V11, LOW);
      digitalWrite(KILL_RELAY_V10, LOW);
      noTone(BUZZER_PIN);
      noTone(TEST_LED);
      noTone(RED_LED);
      digitalWrite(GREEN_LED, HIGH);

      /*IMPLEMENTATION OF RUNNING STEPPER IN PENDING*/
      encoder->encoderTicks();
      int targetPosition = map(ENCODER_VAL_IN_VOLT_V13, MIN_VOLT_V14, MAX_VOLT_V14, CLOCKWISE_STEP_FROM_HOME_V3, MAX_NUMB_STEP_FROM_HOME_V4);

      if (CURRENT_POSITION_FROM_HOME_V5 != targetPosition) {
        int stepsToMove = targetPosition - CURRENT_POSITION_FROM_HOME_V5;
        bool clockwise = stepsToMove > 0;

        digitalWrite(DIR_PIN, clockwise ? HIGH : LOW);
        int steps = abs(stepsToMove);

        for (int i = 0; i < steps; i++) {
          digitalWrite(STEP_PIN, HIGH);
          delayMicroseconds(1000000 / ROTATION_SPEED_STEP_PR_SEC_V6);  // Control speed based on V6
          digitalWrite(STEP_PIN, LOW);
          delayMicroseconds(1000000 / ROTATION_SPEED_STEP_PR_SEC_V6);
        }

        CURRENT_POSITION_FROM_HOME_V5 = targetPosition;  // Update current position to targetPosition
      }
      if (CURRENT_POSITION_FROM_HOME_V5 >= CLOCKWISE_STEP_FROM_HOME_V3 && CURRENT_POSITION_FROM_HOME_V5 <= MAX_NUMB_STEP_FROM_HOME_V4) {
        digitalWrite(KILL_RELAY_V10, LOW);  // Set kill relay to closed (active low)
        digitalWrite(TEST_LED, HIGH);       // Turn on Amber LED
        digitalWrite(GREEN_LED, LOW);       // Turn off Green LED
      } else {
        StepperState::outOfRangEvent();      // Print error message
        digitalWrite(KILL_RELAY_V10, HIGH);  // Set kill relay to open (inactive)
        digitalWrite(TEST_LED, LOW);         // Turn off Amber LED
        digitalWrite(GREEN_LED, HIGH);       // Turn on Green LED
      }

      /*Display*/
      display->show(". Mode = TEST", 1);
      String message1 = "ENCODER INPUT = " + String(ENCODER_VAL_IN_VOLT_V13, 2) + "V";
      display->show(message1, 2);
      String message2 = "RPM = " + String(HAL_SENSOR_CON_RPM_V8);  // NEED TO CALCULATE AND IMPLEMENTATION
      display->show(message2, 3);
      String message3 = "A/F = " + String(V7_CONV_AFR_V73);  // NEED TO CALCULATE AND IMPLEMENTATION
      display->show(message3, 4);

    } else {
      if (millis() > soundTimer) {
        soundTimer = millis() + 1000;
        tone(TEST_LED, 500, 500);  //tone of 500 for 0.8 seconds 800 milliseconds
        tone(BUZZER_PIN, 500, 500);
        tone(RED_LED, 500, 500);
      }
      digitalWrite(KILL_RELAY_V10, LOW);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RUN_LED, LOW);

      /*Display result*/
      if (ENCODER_VAL_IN_VOLT_V13 == MIN_VOLT_V14) {
        String message1 = "ENCODER INPUT = " + String(ENCODER_VAL_IN_VOLT_V13, 2) + "V";
        display->show(message1, 1);
        display->show("SET THE TARGET VALUE", 2);
        display->show("ROTATE KNOB", 3);
        display->show("TBA", 4);
      } else if (ENCODER_VAL_IN_VOLT_V13 > MIN_VOLT_V14) {
        display->show("TO ENABLE TEST MODE", 1);
        display->show("PRESS BUTTON TWICE", 2);
        String message1 = "ENCODER INPUT = " + String(ENCODER_VAL_IN_VOLT_V13, 2) + "V";
        display->show(message1, 3);
        display->show("TBA", 4);
      }
    }
  }
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
