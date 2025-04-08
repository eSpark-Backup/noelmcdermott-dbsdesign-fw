#include "LED.hpp"
#include "EVENTS.hpp"
#include "BUTTON.hpp"
#include "ENCODER.hpp"
#include "DISPLAY.hpp"
#include "LAMBDA_RPM.hpp"
#include "variable_init.hpp"
#include "ERROR_HANDLER.hpp"
#include "Stepper_States.hpp"

#define INITIAL_DELAY (5*1000)

unsigned long startTime;
bool HomePositionRun = false;
volatile unsigned long lastcounttime = 0;

DBS_LED Led;
Stepper motor;
Events event;
Display UI;
Encoder encodr;
Lambda lamda;
ErrorHandler errorHandler;
TaskHandle_t Task1Handle;

Button mode(MODE_SELECT_V12);

void heatingUpO2Sensor()
{
  lastcounttime = millis();
  while (millis() - lastcounttime <= INITIAL_DELAY)
  {
    lamda.LambdaSetup();
    Led.O2StatusLED();
    Serial.print("Counting time: ");
    Serial.println(millis() - lastcounttime);
  }
}

void checkingErrors()
{ 
  if (errorHandler.isError())
  {
    motor.stopStepper();
    event.errorEvents();
    while(digitalRead(RESET_V9) == 0)
    {
      event.resetErrorEvent();
      Serial.print("Reset button press\n");
    }
  }
  else
  {
    motor.enableStepper();
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting setup...");
  UI.init();
  event.setup(&UI);
  errorHandler.InterruptSetup(RESET_V9);
  Led.setup();
  mode.setup();
  motor.stepperInitialize();
  lamda.setup();
  Serial.println("setup has done...");
  encodr.setup();
  heatingUpO2Sensor();
  checkingErrors();
  motor.homePosition();
}

void loop()
{
  /* Check the mode "Run" or "Test" */
  Modes currentMode = static_cast<Modes>(mode.read());
  Serial.println("MODE SELECTION...");
  Serial.println(currentMode);
  /*  check the mode "Run" or "Test"  */
  if (currentMode == RUN_MODE)
  {
    /*Run Mode*/
    Serial.println("SELECTED RUN MODE.");
    motor.run();
  }
  else if (currentMode == TEST_MODE)
  {
    /*Test mode */
    Serial.println("SELECTED TEST MODE.");
    motor.test();
  }
  // switch(static_cast<Modes>(mode.read()))
  // {
  //   case TEST_MODE:
  //   break;
  //   case RUN_MODE:
  //   break;
  //   default:
  //   break;
  // }
  // else if ((currentMode == TEST_MODE) && (motor.checkRPM() == true))
  // {
  //   motor.test();
  // }
  // else if ((currentMode == RUN_MODE) && (motor.checkRPM() == true))
  // {
  //   motor.run();
  // }
  // delay(1000);
}