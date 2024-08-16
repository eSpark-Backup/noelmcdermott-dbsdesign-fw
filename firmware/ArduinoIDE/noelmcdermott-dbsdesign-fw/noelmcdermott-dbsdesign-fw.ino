#include <Arduino.h>
#include <TMCStepper.h>
#include "LED.hpp"
#include "EVENTS.hpp"  
#include "Stepper_States.hpp"
#include "variable_init.hpp"

DBS_LED Led;
StepperState motor;
Events event;

unsigned long lastPressTime = 0;
unsigned long lastButtonPress = 0;
const unsigned long DOUBLE_PRESS_INTERVAL = 2000; // 2 seconds
bool resetPressed = false;

void setup()

 {
  event.setup();
  Led.setup();
  motor.setup();
  motor.overCurrentEvent();
}

void loop() {
  delay(20000);

  /* check over current and out of range event flag is high */
if ((OVER_CURRENT_V17 == 1) || (OVER_RATING_V18 == 1)) {
    motor.stopStepper();
    event.errorEvents();

   /*implement button press twice time */

   /*implement the reset functionality*/
   event.resetErrorEvent();
  }
else {
    motor.enableStepper();
     }

  /*  check the mode "Run" or "Test"  */

  if (MODE_SELECT_V12 == 1) {
    motor.homingState();
    delay(1000);
    motor.run();
  }

  else if (MODE_SELECT_V12 == 0) {
    motor.test();
  }
}
