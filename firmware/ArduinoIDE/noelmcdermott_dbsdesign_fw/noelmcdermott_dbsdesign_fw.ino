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
StepperState motor;
Events event;
Display show;
Encoder encodr;
Lambda lamda;
ErrorHandler errorHandler;

Button mode(MODE_SELECT_V12);

void setup() {
  show.init();
  event.setup(&show);
  Led.setup();
  lamda.setup();
  motor.setup(&show, &encodr, &errorHandler, &lamda);
  motor.overCurrentEvent();
  motor.outOfRangEvent();
  encodr.setup();
  delay(20000);
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
  /*  check the mode "Run" or "Test"  */
  if (mode.read() == 1) {
    /*Run Mode*/
    motor.homePosition();
    delay(1000);
    motor.run();
  } else if (mode.read() == 0) {
    /*Test mode */
    motor.test();
  } else if ((mode.read() == 0) && (motor.checkRPM() == true)) {
    motor.test();
  } else if ((mode.read() == 1) && (motor.checkRPM() == true)) {
    motor.run();
  }
}
