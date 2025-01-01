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

Button mode(MODE_SELECT_V12);

enum Modes {
           TEST_MODE = 0,
           RUN_MODE = 1
           };

void setup() {
  Serial.begin(115200);
  Serial.println("Starting setup...");
  show.init();
  event.setup(&show);
  Led.setup();
  mode.setup();
  lamda.setup();
  motor.setup(&show, &encodr, &errorHandler, &lamda);
  Serial.println("setup has done...");
  motor.overCurrentEvent();
  motor.outOfRangEvent();
  encodr.setup();
  motor.stepperInitialize();
  delay(1000);     // CHANGE TO 20 SEC
}
void loop() {
  /* check over current and out of range event flag is high */
  if (errorHandler.isError()) {
    motor.stopStepper();
    event.errorEvents();
    if (errorHandler.checkResetButton(RESET_V9) == 1) {
      event.resetErrorEvent();
    }
  }

  else {
    motor.enableStepper();
  }

    /* Check the mode "Run" or "Test" */
  Modes currentMode = static_cast<Modes>(mode.read());
  Serial.println("MODE SELECTION...");
  Serial.println(currentMode);

  /*  check the mode "Run" or "Test"  */
  if (currentMode == RUN_MODE) {
    /*Run Mode*/
    Serial.println("SELECTED RUN MODE.");
    motor.homePosition();
    delay(1000);
    motor.run();
  } else if (currentMode == TEST_MODE) {
    /*Test mode */
    delay(1000);
    motor.test();
  } else if ((currentMode == TEST_MODE) && (motor.checkRPM() == true)) {
    motor.test();
  } else if ((currentMode == RUN_MODE) && (motor.checkRPM() == true)) {
    motor.run();
  }
}
