  #include "EVENTS.hpp"

int OVER_CURRENT_V17 = 0;
int OVER_RATING_V18 = 0;

void Events::setup()
{
 pinMode(MODE_SELECT_V12,INPUT);
 pinMode(LIMIT_SWITCH,INPUT);
 pinMode(RESET_V9,INPUT);
//  pinMode(V17,INPUT);
//  pinMode(V18,INPUT);
 
}

void Events::errorEvents() {
  digitalWrite(DRIVER_POWER_V11, HIGH);
  digitalWrite(KILL_RELAY_V10, LOW);

  // Toggle LED and Buzzer
  static unsigned long previousMillis = 0;
  const long interval = 500;  // Interval at which to toggle (milliseconds)

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Save the last time you toggled the LED/buzzer
    previousMillis = currentMillis;

    // Read the current state of LED and buzzer
    int ledState = digitalRead(RED_LED);
    int buzzerState = digitalRead(BUZZER_PIN);

    // Toggle the state
    digitalWrite(RED_LED, !ledState);
    digitalWrite(BUZZER_PIN, !buzzerState);
  }

    /*DISPALY MESSAGE */



}

void Events::resetErrorEvent()
{
  OVER_CURRENT_V17 = 0 ;          
  OVER_RATING_V18  = 0 ;  


  /*ADD MASTER RESET FUNCTIONALITY*/

 /* ADD LED AND BUZZER STATUS*/
  digitalWrite(DRIVER_POWER_V11, LOW);
  digitalWrite(KILL_RELAY_V10, HIGH);
  digitalWrite(RED_LED,LOW);
  digitalWrite(BUZZER_PIN,LOW);
  digitalWrite(GREEN_LED,HIGH);

/*DISPALY MESSAGE */

}