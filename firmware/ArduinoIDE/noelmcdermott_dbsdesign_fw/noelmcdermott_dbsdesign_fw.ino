#include "LED.hpp"
#include "EVENTS.hpp"
#include "BUTTON.hpp"
#include "ENCODER.hpp"
#include "DISPLAY.hpp"
#include "LAMBDA_RPM.hpp"
#include "variable_init.hpp"
#include "ERROR_HANDLER.hpp"
#include "Stepper_States.hpp"

TaskHandle_t lambdaTaskHandle;
#define INITIAL_DELAY (21*1000)
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

Button mode(MODE_SELECT_V12);

// Task function to read lambda data
void lambdaTask(void *parameter){
  while(true){
    lamda.LambdaSetup();
    vTaskDelay(10);
  }
}

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

bool checkingErrors()
{
  if (motor.overCurrentEvent() || motor.outOfRangEvent())
  {
    Serial.println("Errors found!");
    motor.stopStepper();
    event.errorEvents();

    int pressCount = 0;
    unsigned long firstPressTime = 0;

    while (pressCount < 2)
    {
      if (digitalRead(RESET_V9) == LOW)  // Assuming LOW means pressed
      {
        while (digitalRead(RESET_V9) == LOW); // Wait for button release
        delay(20); // debounce

        if (pressCount == 0)
        {
          firstPressTime = millis();
        }

        pressCount++;
        Serial.print("Press count: ");
        Serial.println(pressCount);
      }

      // Timeout after 2 seconds
      if (pressCount > 0 && millis() - firstPressTime > 2000)
      {
        Serial.println("Double press timeout!");
        break;
      }
    }

    if (pressCount == 2)
    {
      Serial.println("Double press detected!");
      event.resetErrorEvent();  // Call reset only if button pressed twice
    }

    return true;
  }
  else
  {
    Serial.println("No Errors found!");
    motor.enableStepper();
    return false;
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting setup...");
  UI.init();
  event.setup(&UI, &motor);
  errorHandler.InterruptSetup(RESET_V9);
  Led.setup();
  mode.setup();
  motor.stepperInitialize();
  lamda.setup();
  Serial.println("setup has done...");
  encodr.setup();
  heatingUpO2Sensor();
  delay(3000);
  while(1)
  {
    if(checkingErrors()) {
    }
    else {
      motor.homePosition();
      break;
    }
  }
      // Create the FreeRTOS task
  xTaskCreate(
    lambdaTask,         // Task function
    "Lambda Task",      // Name
    4096,               // Stack size
    NULL,               // Parameters
    5,                  // Priority
    &lambdaTaskHandle   // Task handle
  );
}

void loop()
{
  
  if(checkingErrors())
  {
    Serial.println("Fault State!");
  }
  else
  {
    switch(static_cast<Modes>(mode.read()))
    {
      case TEST_MODE:
        /*Test mode */
        Serial.println("SELECTED TEST MODE.");
        motor.test();
      break;
      case RUN_MODE:
        /*Run Mode*/
        Serial.println("SELECTED RUN MODE.");
        motor.run();
      break;
      default:
      break;
    }
  }
  delay(100);
}