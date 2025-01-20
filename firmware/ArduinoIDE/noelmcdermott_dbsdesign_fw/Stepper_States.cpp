#include "Stepper_States.hpp"

Conversion converter;
TaskHandle_t Task2Handle;
TaskHandle_t Task3Handle;

void generateTone(int pin, int frequency, int duration) {
  int period = 1000000 / frequency;  // Period in microseconds
  int cycles = (duration * 1000) / period;

  for (int i = 0; i < cycles; i++) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(period / 2);
    digitalWrite(pin, LOW);
    delayMicroseconds(period / 2);
  }
}

void generateTone(int pin1, int pin2, int frequency, int duration) {
  
  int period = 1000000 / frequency;  // Period in microseconds
  int cycles = (duration * 1000) / period;
  for (int i = 0; i < cycles; i++) {
    if (pin1 >= 0) { digitalWrite(pin1, HIGH);}
    if (pin2 >= 0) { digitalWrite(pin2, HIGH);}
    delayMicroseconds(period / 2);
    if (pin1 >= 0) { digitalWrite(pin1, LOW);}
    if (pin2 >= 0) { digitalWrite(pin2, LOW);}
    delayMicroseconds(period / 2);
  }
}

void stopTone(int pin) {
    digitalWrite(pin, LOW);  // Ensure the pin is turned off
}


void Stepper::setup(Display *dis, Encoder *enc, ErrorHandler *error, Lambda *lam) {}


void Stepper::homePosition() {
  display->show("  FIRMWARE  ", 0);
  display->show("  STARTED.. ", 1);
  int countStep = 0;
  Button limitSwitch(LIMIT_SWITCH);
  limitSwitch.setup();
  while (limitSwitch.read() == HIGH) {

    Stepper::moveAnticlockwise(FAST_SPEED_V2_1);
  }
  while (limitSwitch.read() == LOW) {
    Stepper::moveClockwise(SLOW_SPEEDV2_3);
    countStep++;
  }
  display->clear();
  homePositionV2_5 = countStep;
  // homePositionV2_5 = 0;
}
              /*implementation of Test Mode*/
void Stepper::test() {

  ENCODER_VAL_IN_VOLT_V13 = MIN_VOLT_V14;
  display->clear();
  while (digitalRead(MODE_SELECT_V12) == 0) {

    if (halSensorConRpmV8 > 0)                    // check if rpm(v8) greater than 0 its mean switch to test from run;
    {
      // convVoltageV14 = converter.readExternalInput(MilliAmp_Conv::Scale::Voltage);
      ENCODER_VAL_IN_VOLT_V13 = convVoltageV14;
      Serial.println(" The halSensorConRpmV8 is greater than zero so ENCODER_VAL_IN_VOLT_V13 value is: ");
      Serial.println(ENCODER_VAL_IN_VOLT_V13);
    } else {
      ENCODER_VAL_IN_VOLT_V13 = encoder->getEconderVoltage();
    }

    if (errorHand->checkResetButton(RESET_V9) == false)  // press button for two second
    {
      v7ConvAfrV73 = lamd->getAF();
      halSensorConRpmV8 = lamd->getRPM();
      /*Display*/
      display->clear();
      display->show("Mode = TEST", 0);
      String message1 = "ENCODER INPUT= " + String(ENCODER_VAL_IN_VOLT_V13, 2) + "V";
      display->show(message1, 1);
      String message2 = "RPM = " + String(halSensorConRpmV8);  // NEED TO CALCULATE AND IMPLEMENTATION
      display->show(message2, 2);
      String message3 = "A/F = " + String(v7ConvAfrV73);  // NEED TO CALCULATE AND IMPLEMENTATION
      display->show(message3, 3);
      digitalWrite(KILL_RELAY_V10, LOW);
      stopTone(BUZZER_PIN);
      stopTone(TEST_LED);
      stopTone(RED_LED);
      digitalWrite(GREEN_LED, HIGH);

      /*IMPLEMENTATION OF RUNNING STEPPER IN PENDING*/
      int targetPosition = map(ENCODER_VAL_IN_VOLT_V13 * 1000, MIN_VOLT_V14, MAX_VOLT_V14 * 1000, CLOCKWISE_STEP_FROM_HOME_V3, MAX_NUMB_STEP_FROM_HOME_V4);
      Serial.print("Target position is:");
      Serial.println(targetPosition);

      if (currentPositionFromHomeV5 != targetPosition) {

        int stepsToMove = (targetPosition - currentPositionFromHomeV5) * 16;  //255
        Serial.print("the step to move is: ");
        Serial.print(stepsToMove);
        Serial.print("\n");
        bool clockwise = stepsToMove > 0;
        digitalWrite(DIR_PIN, clockwise ? LOW : HIGH);
        int steps = abs(stepsToMove);
        Serial.print("the step is: ");
        Serial.print(steps);
        Serial.print("\n");
        for (int i = 0; i < steps; i++) {
          digitalWrite(STEP_PIN, HIGH);
          delayMicroseconds(100000 / ROTATION_SPEED_STEP_PR_SEC_V6);  // Control speed based on V6
          digitalWrite(STEP_PIN, LOW);
          delayMicroseconds(100000 / ROTATION_SPEED_STEP_PR_SEC_V6);
        }
        currentPositionFromHomeV5 = targetPosition;  // Update current position to targetPosition
        Serial.print("the updated current position of V5 is: ");
        Serial.println(currentPositionFromHomeV5);
      }
      if (Stepper::outOfRangEvent() == 0) {
        digitalWrite(KILL_RELAY_V10, LOW);            // Set kill relay to closed (active low)
        digitalWrite(TEST_LED, HIGH);                 // Turn on Amber LED
        digitalWrite(GREEN_LED, LOW);                 // Turn off Green LED
      } else {
        digitalWrite(KILL_RELAY_V10, HIGH);           // Set kill relay to open (inactive)
        digitalWrite(TEST_LED, LOW);                  // Turn off Amber LED
        digitalWrite(GREEN_LED, HIGH);                // Turn on Green LED
      }
      delay(3000);
      display->clear();
    } else {
      if (millis() > soundTimer) {
        soundTimer = millis() + 1000;
        generateTone(TEST_LED, RED_LED, 1000, 800);
        generateTone(BUZZER_PIN, 500, 500);
      }
      digitalWrite(KILL_RELAY_V10, LOW);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RUN_LED, LOW);

      /*Display result*/
      if (ENCODER_VAL_IN_VOLT_V13 == MIN_VOLT_V14) {

        String message1 = "ENCODER INPUT= " + String(ENCODER_VAL_IN_VOLT_V13, 2) + "V";
        display->show(message1, 0);
        display->show("SET THE TARGET VAL  ", 1);
        display->show("ROTATE KNOB         ", 2);
        display->show("TBA                 ", 3);

      } else if (ENCODER_VAL_IN_VOLT_V13 > MIN_VOLT_V14) {

        display->show("TO ENABLE TEST MODE ", 0);
        display->show("PRESS BUTTON TWICE  ", 1);
        String message1 = "ENCODER INPUT= " + String(ENCODER_VAL_IN_VOLT_V13, 2) + "V";
        display->show(message1, 2);
        display->show("TBA                 ", 3);
      }
    }
  }
}

/*RUN MODE*/
void Stepper::run() {

  display->clear();
  while (digitalRead(MODE_SELECT_V12) == 1) {
    // lamd->LambdaSetup();
    convCurrentV14 = converter.readExternalInput(Conversion::Scale::MilliAmp);
    convVoltageV14 = converter.readExternalInput(Conversion::Scale::Voltage);

    if (convCurrentV14 >= 4.0f && convCurrentV14 < 20.0f) {
      // Move clockwise
      vTaskSuspend(Task3Handle);
      vTaskResume(Task2Handle);

    } else if (convCurrentV14 > 20.0f && convCurrentV14 <= 40.0f) {
      // Move anticlockwise
      vTaskSuspend(Task2Handle);
      vTaskResume(Task3Handle);
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

    v7ConvAfrV73 = lamd->getAF();
    halSensorConRpmV8 = lamd->getRPM();

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
  driver.shaft(0);  // Set direction to clockwise
  Serial.print("Running motor clockwise\n");
  // Generate steps to move the motor
  for (int i = 0; i < STEPS_PER_REV_V1; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(100000 / speed);  // Adjust speed with delay
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(100000 / speed);
  }
}

void Stepper::moveAnticlockwise(int speed) {
  driver.shaft(1);                                // Set direction to anticlockwise
  Serial.print("Running motor anticlockwise\n");
  for (int i = 0; i < STEPS_PER_REV_V1; i++) {    // Generate steps to move the motor
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(100000 / speed);           // Adjust speed with delay
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(100000 / speed);
  }
}


float Stepper::getMotorCurrent() {
  uint8_t cs_actual = driver.cs_actual();           // Current scale (0-31)
  // Calculate the current in mA
  float V_fs = 0.325;                             // Full-scale voltage across sense resistor (for default settings)
  float I_rms = (V_fs * cs_actual / 32.0) / R_SENSE;
  // Convert I_rms to I_tripmax (peak current)
  float motorCurrent = I_rms * 1.41 * 1000;
  return motorCurrent;                          // Return current in mA
}

bool Stepper::overCurrentEvent() {
  float current_mA = getMotorCurrent();      // Assuming this function returns the current in milliamps
  if (current_mA > MAX_DRIVER_CURRENT_V16) {
    overCurrentV17 = true;                  // Set to true if overcurrent
  } else {
    overCurrentV17 = false;                // Set to false otherwise
  }
  return overCurrentV17;                  // Return the boolean indicating overcurrent status
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

float Stepper::getConvCurrentV14() const {
        return convCurrentV14;
    }

void Task2(void *parameter) {
  Stepper *stepper = static_cast<Stepper *>(parameter);
  while (1) {
    while ((digitalRead(MODE_SELECT_V12) == 1) && (stepper->getConvCurrentV14() >= 4.0f && stepper->getConvCurrentV14() <= 20.0f)) {
      stepper->moveClockwise(ROTATION_SPEED_STEP_PR_SEC_V6);
    }
    vTaskDelay(10);
  }
}

void Task3(void *parameter) {
  Stepper *stepper = static_cast<Stepper *>(parameter);
  while (1) {
    while ((digitalRead(MODE_SELECT_V12) == 1) && (stepper->getConvCurrentV14() > 20.0f && stepper->getConvCurrentV14() <= 40.0f)) {
      stepper->moveAnticlockwise(ROTATION_SPEED_STEP_PR_SEC_V6);
    }
      vTaskDelay(10);
  }
}

void Stepper::stepperInitialize()
{
  pinMode(DRIVER_POWER_V11, OUTPUT);
  pinMode(KILL_RELAY_V10, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(CS_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);  

  xTaskCreate(Task2, "Clockwise Rotation", 4096, this , 1 , &Task2Handle);   // Name of the task
  xTaskCreate(Task3, "Anticlockwise Rotation", 4096, this , 1,  &Task3Handle);   // Name of the task
  vTaskSuspend( Task2Handle );
  vTaskSuspend( Task3Handle );
     
}
