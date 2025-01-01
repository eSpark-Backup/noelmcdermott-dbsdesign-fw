#include "Stepper_States.hpp"


Conversion converter;

Stepper::Stepper() : driver(CS_PIN, R_SENSE) {  // Initialize the driver with CS_PIN and R_SENSE
    // Initialize other members if needed
}

void Stepper::stepperInitialize()
{
  pinMode(DRIVER_POWER_V11, OUTPUT);
  pinMode(KILL_RELAY_V10, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(CS_PIN, OUTPUT);
  // pinMode(LAMBDA_CS1_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  
}
void Stepper::setup(Display *dis, Encoder *enc, ErrorHandler *error, Lambda *lam) {
  // Setup the TMC2160 driver
  SPI.begin();                          // Initialize SPI
  driver.begin();                       // Initialize driver with default settings
  driver.rms_current(500);              // Set motor RMS current
  driver.microsteps(16);                // Set microsteps
  driver.en_pwm_mode(true);             // Enable StealthChop for quiet movement
  driver.pwm_autoscale(true);           // Enable autoscaling of PWM frequency
  digitalWrite(DRIVER_POWER_V11, LOW);  // enable pin is low
  
}

void Stepper::homePosition() {

  moveAnticlockwise(FAST_SPEED_V2_1);
  Button limitSwitch(LIMIT_SWITCH);
  limitSwitch.setup(); 
  while (limitSwitch.read() == HIGH) {}
  // positionV2_2 = driver.TSTEP();  // Store position at first approach
  // driver.TCOOLTHRS(0);              // Set threshold for slow speed
  Stepper::moveClockwise(SLOW_SPEEDV2_3);
  while (limitSwitch.read() == LOW) {}

  positionV2_4 = driver.TSTEP();
  homePositionV2_5 = 0;
}

void Stepper::test() {
  /*implementation of Test Mode*/
  ENCODER_VAL_IN_VOLT_V13 = MIN_VOLT_V14;

  while (digitalRead(MODE_SELECT_V12) == 0) {
    if (halSensorConRpmV8 > 0)  // check if rpm(v8) greater than 0 its mean switch to test from run;
    {
      // convVoltageV14 = converter.readExternalInput(MilliAmp_Conv::Scale::Voltage);
      ENCODER_VAL_IN_VOLT_V13 = convVoltageV14;
    } else {
      ENCODER_VAL_IN_VOLT_V13 = encoder->getEconderVoltage();
    }

    if (errorHand->checkResetButton(RESET_V9) == 1)  // press button for two second
    {
      digitalWrite(KILL_RELAY_V10, LOW);
      noTone(BUZZER_PIN);
      noTone(TEST_LED);
      noTone(RED_LED);
      digitalWrite(GREEN_LED, HIGH);

      /*IMPLEMENTATION OF RUNNING STEPPER IN PENDING*/
      encoder->encoderTicks();
      int targetPosition = map(ENCODER_VAL_IN_VOLT_V13, MIN_VOLT_V14, MAX_VOLT_V14, CLOCKWISE_STEP_FROM_HOME_V3, MAX_NUMB_STEP_FROM_HOME_V4);

      if (currentPositionFromHomeV5 != targetPosition) {
        int stepsToMove = targetPosition - currentPositionFromHomeV5;
        bool clockwise = stepsToMove > 0;

        digitalWrite(DIR_PIN, clockwise ? HIGH : LOW);
        int steps = abs(stepsToMove);

        for (int i = 0; i < steps; i++) {
          digitalWrite(STEP_PIN, HIGH);
          delayMicroseconds(1000000 / ROTATION_SPEED_STEP_PR_SEC_V6);  // Control speed based on V6
          digitalWrite(STEP_PIN, LOW);
          delayMicroseconds(1000000 / ROTATION_SPEED_STEP_PR_SEC_V6);
        }
        currentPositionFromHomeV5 = targetPosition;  // Update current position to targetPosition
      }
      if (Stepper::outOfRangEvent() == 0) {
        digitalWrite(KILL_RELAY_V10, LOW);  // Set kill relay to closed (active low)
        digitalWrite(TEST_LED, HIGH);       // Turn on Amber LED
        digitalWrite(GREEN_LED, LOW);       // Turn off Green LED
      } else {
        // Stepper::outOfRangEvent();      // Print error message
        digitalWrite(KILL_RELAY_V10, HIGH);  // Set kill relay to open (inactive)
        digitalWrite(TEST_LED, LOW);         // Turn off Amber LED
        digitalWrite(GREEN_LED, HIGH);       // Turn on Green LED
      }

      // halSensorConRpmV8 = Stepper::rpmStepper();
      halSensorConRpmV8 = lamd->getRPM();
      v7ConvAfrV73 = lamd->getAF();
      /*Display*/
      display->show(". Mode = TEST", 0);
      String message1 = "ENCODER INPUT = " + String(ENCODER_VAL_IN_VOLT_V13, 2) + "V";
      display->show(message1, 1);
      String message2 = "RPM = " + String(halSensorConRpmV8);  // NEED TO CALCULATE AND IMPLEMENTATION
      display->show(message2, 2);
      String message3 = "A/F = " + String(v7ConvAfrV73);  // NEED TO CALCULATE AND IMPLEMENTATION
      display->show(message3, 3);

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
      display->clear();
      if (ENCODER_VAL_IN_VOLT_V13 == MIN_VOLT_V14) {
        String message1 = "ENCODER INPUT = " + String(ENCODER_VAL_IN_VOLT_V13, 2) + "V";
        display->show(message1, 0);
        display->show("SET THE TARGET VAL", 1);
        display->show("ROTATE KNOB", 2);
        display->show("TBA", 3);
      } else if (ENCODER_VAL_IN_VOLT_V13 > MIN_VOLT_V14) {
        display->show("TO ENABLE TEST MODE", 0);
        display->show("PRESS BUTTON TWICE", 1);
        String message1 = "ENCODER INPUT = " + String(ENCODER_VAL_IN_VOLT_V13, 2) + "V";
        display->show(message1, 2);
        display->show("TBA", 3);
      }
    }
  }

}
/*RUN MODE*/
void Stepper::run() {
  while (digitalRead(MODE_SELECT_V12) == 1) {
    convCurrentV14 = converter.readExternalInput(Conversion::Scale::MilliAmp);
    convVoltageV14 = converter.readExternalInput(Conversion::Scale::Voltage);

    if (convCurrentV14 >= 4.0f && convCurrentV14 < 20.0f) {
      // Move clockwise
      moveClockwise(ROTATION_SPEED_STEP_PR_SEC_V6);
    } else if (convCurrentV14 > 20.0f && convCurrentV14 <= 40.0f) {
      // Move anticlockwise
      moveAnticlockwise(ROTATION_SPEED_STEP_PR_SEC_V6);
    }
    /* Display the result*/
    if (Stepper::outOfRangEvent() == 0) {
      digitalWrite(RED_LED, LOW);
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(RUN_LED, HIGH);
      digitalWrite(TEST_LED, LOW);
      digitalWrite(KILL_RELAY_V10, HIGH);
    } else {
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RUN_LED, LOW);
      digitalWrite(TEST_LED, LOW);
      digitalWrite(KILL_RELAY_V10, LOW);
    }
    // halSensorConRpmV8 = Stepper::rpmStepper();
    halSensorConRpmV8 = lamd->getRPM();
    v7ConvAfrV73 = lamd->getAF();
    display->clear();
    display->show("Mode = Run", 0);
    String message1 = "MICROSQ.INPUT= " + String(convVoltageV14, 2) + "V";
    display->show(message1, 1);
    String message2 = "RPM = " + String(halSensorConRpmV8);  // NEED TO CALCULATE AND IMPLEMENTATION
    display->show(message2, 2);
    String message3 = "A/F = " + String(v7ConvAfrV73);  // NEED TO CALCULATE AND IMPLEMENTATION
    display->show(message3, 3);
  }

}
void Stepper::moveClockwise(int speed) {
  driver.shaft(1);  // Set direction to clockwise
  // Generate steps to move the motor
  for (int i = 0; i < STEPS_PER_REV_V1; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(1000000 / speed);  // Adjust speed with delay
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(1000000 / speed);
  }
}

void Stepper::moveAnticlockwise(int speed) {
  driver.shaft(0);  // Set direction to anticlockwise

  // Generate steps to move the motor
  for (int i = 0; i < STEPS_PER_REV_V1; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(1000000 / speed);  // Adjust speed with delay
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(1000000 / speed);
  }
}


float Stepper::getMotorCurrent() {
  uint8_t cs_actual = driver.cs_actual();  // Current scale (0-31)
  // Calculate the current in mA
  float V_fs = 0.325;  // Full-scale voltage across sense resistor (for default settings)
  float I_rms = (V_fs * cs_actual / 32.0) / R_SENSE;
  // Convert I_rms to I_tripmax (peak current)
  float motorCurrent = I_rms * 1.41 * 1000;
  return motorCurrent;  // Return current in mA
}

bool Stepper::overCurrentEvent() {
  float current_mA = getMotorCurrent();  // Assuming this function returns the current in milliamps
  if (current_mA > MAX_DRIVER_CURRENT_V16) {
    overCurrentV17 = true;  // Set to true if overcurrent
  } else {
    overCurrentV17 = false;  // Set to false otherwise
  }
  return overCurrentV17;  // Return the boolean indicating overcurrent status
}

bool Stepper::outOfRangEvent() {
  /*implementation out of range event*/
  if (currentPositionFromHomeV5 >= CLOCKWISE_STEP_FROM_HOME_V3 && currentPositionFromHomeV5 <= MAX_NUMB_STEP_FROM_HOME_V4) {
    overRatingV18 = false;
  } else {
    overRatingV18 = true;
  }
  return overRatingV18;
}

void Stepper::stopStepper() {
  driver.toff(0);
}
void Stepper::enableStepper() {
  driver.toff(5);
}

bool Stepper::checkRPM() {
  if (halSensorConRpmV8 > 0) {
    return true;
  } else {
    return false;
  }
}
