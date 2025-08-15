#include "BUTTON.hpp"
#include "CONVERSION.hpp"
#include "Stepper_States.hpp"

Conversion converter;
volatile bool modeTriggered = false;
static bool testModeActive = false;

static void generateTone(int pin, int frequency, int duration)
{
  int period = 1000000 / frequency;
  int cycles = (duration * 1000) / period;

  for (int i = 0; i < cycles; i++)
  {
    digitalWrite(pin, HIGH);
    delayMicroseconds(period / 2);
    digitalWrite(pin, LOW);
    delayMicroseconds(period / 2);
  }
}

static void generateTone_3(int pin1, int pin2, int frequency, int duration)
{
  int period = 1000000 / frequency;
  int cycles = (duration * 1000) / period;
  for (int i = 0; i < cycles; i++)
  {
    if (pin1 >= 0) { digitalWrite(pin1, HIGH);}
    if (pin2 >= 0) { digitalWrite(pin2, HIGH);}
    delayMicroseconds(period / 2);
    if (pin1 >= 0) { digitalWrite(pin1, LOW);}
    if (pin2 >= 0) { digitalWrite(pin2, LOW);}
    delayMicroseconds(period / 2);
  }
}

static void stopTone(int pin)
{
  digitalWrite(pin, LOW);
}

void Stepper::outOfRange()
{
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RUN_LED, HIGH);
  digitalWrite(TEST_LED, LOW);
  digitalWrite(KILL_RELAY_V10, HIGH);
}

void Stepper::inRange()
{
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RUN_LED, LOW);
  digitalWrite(TEST_LED, LOW);
  digitalWrite(KILL_RELAY_V10, LOW);
}

void Stepper::stepperInitialize()
{
  pinMode(DRIVER_POWER_V11, OUTPUT);
  pinMode(KILL_RELAY_V10, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(CS_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);   
}

void Stepper::homePosition()
{
  display->clear();
  display->show("  FIRMWARE  ", 0);
  display->show("  STARTED.. ", 1);
  Button limitSwitch(LIMIT_SWITCH);
  limitSwitch.setup();
  while (limitSwitch.read() == HIGH)
  {
    Stepper::moveAnticlockwise(FAST_SPEED_V2_1);
  }
  while (limitSwitch.read() == LOW)
  {
    Stepper::moveClockwise(SLOW_SPEEDV2_3);
  }
  display->clear();
  homePositionV2_5 = 0;
}

void Stepper::setEncoderButtonState(bool state)
{ 
  encoder.button_state = state;
}

/*implementation of Test Mode*/
void Stepper::test()
{
  modeTriggered = false;
  testModeActive = false;
  ENCODER_VAL_IN_VOLT_V13 = MIN_VOLT_V14;
  if (halSensorConRpmV8 > 0)
  {
    ENCODER_VAL_IN_VOLT_V13 = convVoltageV14;
    Serial.print("The halSensorConRpmV8 is greater than zero so ENCODER_VAL_IN_VOLT_V13 value is: ");
    Serial.println(ENCODER_VAL_IN_VOLT_V13);
  }
  else
  {
    ENCODER_VAL_IN_VOLT_V13 = encoder.getEncoderVoltage();
  }

  if(errorHand->checkResetButton(RESET_V9) == false || DoublePressCount == 2)
  {
    testModeActive = true;
  }

  if(testModeActive){ 
    encoder.button_state = 1;
    digitalWrite(KILL_RELAY_V10, LOW);
    stopTone(BUZZER_PIN);
    stopTone(TEST_LED);
    stopTone(RED_LED);
    digitalWrite(GREEN_LED, HIGH);

    v7ConvAfrV73 = lamd->getAF();
    halSensorConRpmV8 = lamd->getRPM();
    
    // ENCODER_VAL_IN_VOLT_V13 = encoder.getEncoderVoltage();
    /*Display*/
    display->clear();
    display->show("Mode = TEST", 0);
    String message1 = "ENCODER INPUT= " + String(ENCODER_VAL_IN_VOLT_V13, 2) + "V";
    display->show(message1, 1);
    String message2 = "RPM = " + String(halSensorConRpmV8);
    display->show(message2, 2);
    String message3 = "A/F = " + String(v7ConvAfrV73);
    display->show(message3, 3);

    /*IMPLEMENTATION OF RUNNING STEPPER IN PENDING*/
    int targetPosition = map(ENCODER_VAL_IN_VOLT_V13 * 1000, MIN_VOLT_V14, MAX_VOLT_V14 * 1000, CLOCKWISE_STEP_FROM_HOME_V3, MAX_NUMB_STEP_FROM_HOME_V4);
    Serial.print("Target position is:");
    Serial.println(targetPosition);

    if (currentPositionFromHomeV5 != targetPosition)
    {
      int stepsToMove = (targetPosition - currentPositionFromHomeV5) * 16;  //255
      Serial.print("The step to move is: ");
      Serial.println(stepsToMove);
      bool clockwise = stepsToMove > 0;
      digitalWrite(DIR_PIN, clockwise ? LOW : HIGH);
      runStepper(ROTATION_SPEED_STEP_PR_SEC_V6, abs(stepsToMove));
      currentPositionFromHomeV5 = targetPosition;  // Update current position to targetPosition
      Serial.print("The updated current position of V5 is: ");
      Serial.println(currentPositionFromHomeV5);
    }

    if (Stepper::outOfRangEvent())
    {
      digitalWrite(KILL_RELAY_V10, LOW);
      digitalWrite(TEST_LED, LOW);       
      digitalWrite(GREEN_LED, HIGH);     
    }
    else
    {
      digitalWrite(KILL_RELAY_V10, HIGH);
      digitalWrite(TEST_LED, HIGH);     
      digitalWrite(GREEN_LED, LOW);     
    }
    delay(300);
    display->clear();
  
  }
  else
  {
    if(!encoder.button_state)
    {
      if (millis() > soundTimer)
      {
        soundTimer = millis() + 1000;
        generateTone_3(TEST_LED, RED_LED, 1000, 800);
        generateTone(BUZZER_PIN, 500, 500);
      }
      digitalWrite(KILL_RELAY_V10, LOW);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RUN_LED, LOW);
    }

    /*Display result*/
    if (ENCODER_VAL_IN_VOLT_V13 == MIN_VOLT_V14)
    {
      String message1 = "ENCODER INPUT= " + String(ENCODER_VAL_IN_VOLT_V13, 2) + "V";
      display->show(message1, 0);
      display->show("SET THE TARGET VAL  ", 1);
      display->show("ROTATE KNOB         ", 2);
      display->show("TBA                 ", 3);

    }
    else if (ENCODER_VAL_IN_VOLT_V13 > MIN_VOLT_V14)
    {

      display->show("TO ENABLE TEST MODE ", 0);
      display->show("PRESS BUTTON TWICE  ", 1);
      String message1 = "ENCODER INPUT= " + String(ENCODER_VAL_IN_VOLT_V13, 2) + "V";
      display->show(message1, 2);
      display->show("TBA                 ", 3);
    }
  }
}

/*RUN MODE*/
void Stepper::run()
{ 
  DoublePressCount = 0;
  convVoltageV14 = converter.readExternalInput(Conversion::Scale::Voltage);
  int targetPos= map(convVoltageV14 * 1000, MIN_VOLT_V14, MAX_VOLT_V14 * 1000, CLOCKWISE_STEP_FROM_HOME_V3, MAX_NUMB_STEP_FROM_HOME_V4);
  Serial.print("Target Positions:");
  Serial.println(targetPos);
  if(!modeTriggered){
    display->clear();
    modeTriggered = true;
  }
  if (currentPositionFromHomeV5 != targetPos)
  {

    int stepsToMove = (targetPos - currentPositionFromHomeV5) * 16;  //255
    Serial.print("The steps to move are: ");
    Serial.println(stepsToMove);
    currentPositionFromHomeV5 = targetPos;
    /* Display the result*/

    digitalWrite(DIR_PIN, (stepsToMove > 0) ? LOW : HIGH);
    runStepper(ROTATION_SPEED_STEP_PR_SEC_V6, abs(stepsToMove));
    Serial.print("The updated current position of V5 is: ");
    Serial.println(currentPositionFromHomeV5);
  }
      if (Stepper::outOfRangEvent() == 0)
    {
      outOfRange();
    }
    else
    {
      inRange();
    }
  v7ConvAfrV73 = lamd->getAF();
  halSensorConRpmV8 = lamd->getRPM();
  display->show("Mode = Run", 0);
  String message1 = "MICROSQ.INPUT= " + String(convVoltageV14, 1) + "V";
  display->show(message1, 1);
  String message2 = "RPM = " + String(halSensorConRpmV8);
  display->show(message2, 2);
  String message3 = "A/F = " + String(v7ConvAfrV73);
  display->show(message3, 3);
}

void Stepper::moveClockwise(int speed)
{
  driver.shaft(0);
  Serial.println("Running motor clockwise");
  for (int i = 0; i < STEPS_PER_REV_V1; i++)
  {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(100000 / speed);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(100000 / speed);
  }
}

void Stepper::moveAnticlockwise(int speed)
{
  driver.shaft(1);
  Serial.println("Running motor anticlockwise");
  for (int i = 0; i < STEPS_PER_REV_V1; i++)
  {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(100000 / speed);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(100000 / speed);
  }
}

void Stepper::runStepper(int speed, int step)
{
  Serial.println("Running motor....");
  for (int i = 0; i < step; i++)
  {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(100000 / speed);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(100000 / speed);
  }
}

float Stepper::getMotorCurrent()
{
  uint8_t cs_actual = driver.cs_actual();
  float motorCurrent = ((0.325 * cs_actual / 32.0) / R_SENSE) * 1.41 * 1000;
  return motorCurrent;
}

bool Stepper::overCurrentEvent() 
{
  float current_mA = getMotorCurrent();
  Serial.print("over current is :");
  Serial.println(current_mA);
  if (current_mA > MAX_DRIVER_CURRENT_V16)
  {
    overCurrentV17 = true;
  }
  else
  {
    overCurrentV17 = false;
  }
  return overCurrentV17;
}

bool Stepper::outOfRangEvent()
{

  if (currentPositionFromHomeV5 < CLOCKWISE_STEP_FROM_HOME_V3 * 0 || currentPositionFromHomeV5 > MAX_NUMB_STEP_FROM_HOME_V4)
  {
    overRatingV18 = true;
  }
  else
  {
    overRatingV18 = false;
  }
  return overRatingV18;
}

bool Stepper::getoverCurrentV17()
{
  return overCurrentV17;
}

bool Stepper::getoverRatingV18()
{
  return overRatingV18;
}

void Stepper::setoverCurrentV17(bool state)
{
  overCurrentV17 = state;
}

void Stepper::setoverRatingV18(bool state)
{
  overRatingV18 = state;
}


void Stepper::stopStepper()
{
  driver.toff(0);
}

void Stepper::enableStepper()
{
  driver.toff(5);
}

bool Stepper::checkRPM()
{
  if (halSensorConRpmV8 > 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}