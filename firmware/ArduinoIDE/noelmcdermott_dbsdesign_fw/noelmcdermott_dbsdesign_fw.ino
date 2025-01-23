#include <Arduino.h>
#include <TMCStepper.h>
#include <RotaryEncoder.h>
#include "LED.hpp"
#include "EVENTS.hpp"
#include "Stepper_States.hpp"
#include "variable_init.hpp"
#include "DISPLAY.hpp"
#include "ERROR_HANDLER.hpp"
#include "BUTTON.hpp"
#include "ENCODER.hpp"
#include "LAMBDA_RPM.hpp"


DBS_LED Led;
Stepper motor;
Events event;
Display show;
Encoder encodr;
Lambda lamda;
ErrorHandler errorHandler;
TaskHandle_t Task1Handle;

bool HomePositionRun = false;
volatile unsigned long lastcounttime = 0;
unsigned long startTime;

Button mode(MODE_SELECT_V12);

void heatingUpO2Sensor() {
  lastcounttime = millis();
  while (millis() - lastcounttime <= 30000) {
    lamda.LambdaSetup();
    Led.O2StatusLED();
    Serial.print("Counting time: ");
    Serial.println(millis() - lastcounttime);
  }
}

void checkingErrors()
{ 
  if (errorHandler.isError()) {
      motor.stopStepper();
      event.errorEvents();
      while(digitalRead(RESET_V9) == 0) {  // if (errorHandler.checkResetButton(RESET_V9) == false) {
          event.resetErrorEvent();
          Serial.print("Reset button press\n");
          }
      }else {
      motor.enableStepper();
      }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting setup...");
  show.init();
  event.setup(&show);
  errorHandler.InterruptSetup(RESET_V9);
  Led.setup();
  mode.setup();
  motor.stepperInitialize();
  motor.setup(&show, &encodr, &errorHandler, &lamda);
  lamda.setup();
  Serial.println("setup has done...");
  encodr.setup();
  heatingUpO2Sensor();
  checkingErrors();
  motor.homePosition();
      
}
void loop() {

  /* Check the mode "Run" or "Test" */
  Modes currentMode = static_cast<Modes>(mode.read());
  Serial.println("MODE SELECTION...");
  Serial.println(currentMode);
  /*  check the mode "Run" or "Test"  */
  if (currentMode == RUN_MODE) {
    /*Run Mode*/
      Serial.println("SELECTED RUN MODE.");
      motor.run();
  } else if (currentMode == TEST_MODE) {
    /*Test mode */
      Serial.println("SELECTED RUN MODE.");
      motor.test();
  } else if ((currentMode == TEST_MODE) && (motor.checkRPM() == true)) {
      motor.test();
  } else if ((currentMode == RUN_MODE) && (motor.checkRPM() == true)) {
      motor.run();
  }
}
