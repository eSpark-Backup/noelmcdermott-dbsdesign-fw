#include <Arduino.h>
#include <TMCStepper.h>
#include "LED.hpp"
#include "EVENTS.hpp"  
#include "Stepper_States.hpp"
#include "variable_init.hpp"
#include"DISPLAY.hpp"
#include"ERROR_HANDLER.hpp"

DBS_LED Led;
StepperState motor;
Events event;
Display show;
ErrorHandler errorHandler;


void setup()

 {
  show.init();
  event.setup(&show);
  Led.setup();
  motor.setup(&show);
  motor.overCurrentEvent();
  motor.outOfRangEvent();
  delay(20000);
}

void loop() {
  /* check over current and out of range event flag is high */
if ((OVER_CURRENT_V17 == 1) || (OVER_RATING_V18 == 1)) {
    motor.stopStepper();
    event.errorEvents();
    if(errorHandler.checkResetButton() == 1)
    {
      event.resetErrorEvent();
    }
  } 

else {
    motor.enableStepper();
     }

  /*  check the mode "Run" or "Test"  */

  if (MODE_SELECT_V12 == 1) {
  /*Run Mode*/
    motor.homingState();
    delay(1000);
    motor.run();
  }

  else if (MODE_SELECT_V12 == 0) {
    /*Test mode */
    motor.test();
  }
}
