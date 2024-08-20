#include <Arduino.h>
#include <TMCStepper.h>
#include "LED.hpp"
#include "EVENTS.hpp"
#include "Stepper_States.hpp"
#include "variable_init.hpp"
#include "DISPLAY.hpp"
#include "ERROR_HANDLER.hpp"
#include "BUTTON.hpp"
#include "ENCODER.hpp"

DBS_LED Led;
StepperState motor;
Events event;
Display show;
Encoder encodr;
ErrorHandler errorHandler;
Button mode(MODE_SELECT_V12);
void setup()

{
  show.init();
  event.setup(&show);
  Led.setup();
  motor.setup(&show, &encodr);
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
    if (errorHandler.checkResetButton() == 1) {
      event.resetErrorEvent();
    }
  }

  else {
    motor.enableStepper();
  }

  /*  check the mode "Run" or "Test"  */

  if (mode.read() == 1) {
    /*Run Mode*/
    motor.homingState();
    delay(1000);
    motor.run();
  }

  else if (mode.read() == 0) {
    /*Test mode */
    motor.test();
  }
}
