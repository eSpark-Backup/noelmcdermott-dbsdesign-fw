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

void Task1(void *parameter) {
  while (true) {
    lamda.LambdaSetup();
    vTaskDelay(100);
  }
}

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
  event.initialization();
  errorHandler.InterruptSetup(RESET_V9);
  Led.setup();
  mode.setup();
  motor.stepperInitialize();
  motor.setup(&show, &encodr, &errorHandler, &lamda);
  lamda.setup();
  Serial.println("setup has done...");
  motor.overCurrentEvent();
  motor.outOfRangEvent();
  encodr.setup();

  xTaskCreate(
    Task1,                  // Function to implement the task
    "Initializing Lambda",  // Name of the task
    4096,                   // Stack size (in words, not bytes)
    NULL,                   // Task input parameter
    1,                      // Priority of the task
    &Task1Handle            // Task handle
  );

  delay(20000);             // CHANGE TO 20 SEC
}
void loop() {
  /* check over current and out of range event flag is high */
  if (errorHandler.isError()) {
      motor.stopStepper();
      event.errorEvents();
      if (digitalRead(RESET_V9) == 0) {  // if (errorHandler.checkResetButton(RESET_V9) == false) {
          event.resetErrorEvent();
          Serial.print("Reset button press\n");
          }
      }
else {
    motor.enableStepper();
    }
    
  if (HomePositionRun == false) {
      motor.homePosition();
      HomePositionRun = true;
      }

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
