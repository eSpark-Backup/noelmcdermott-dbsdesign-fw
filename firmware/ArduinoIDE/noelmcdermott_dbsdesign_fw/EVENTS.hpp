#pragma once
#include<Arduino.h>
#include <TMCStepper.h>
#include "LED.hpp"
#include "Stepper_States.hpp"
#include "variable_init.hpp"
#include"DISPLAY.hpp"



#define MODE_SELECT_V12                 6               //mode selection switch state (“Run” = 1, “Test” = 0)
#define EXTERNAL_INPUT                  1               //EXTERNAL INPUT
#define LIMIT_SWITCH                    47               //LIMIT SWITCH                                 //pin left
#define RESET_V9                        48               //RESET PUSH BUTTTON                     

enum FaultEvent {
  NO_FAULT,
  OVER_CURRENT_ONLY,
  OVER_RATING_ONLY,
  BOTH_FAULTS
};

// typedef struct event {
//   int v1, v2, v3;
// } event_t;

class Events
{
  public:
    void setup(Display *dis);
    void errorEvents();
    void resetErrorEvent();
    // event_t* getEvents(){
    //   return &events;
    // }
  private:
  Display *display;
  
  enum FaultEvent {
    NO_FAULT,
    OVER_CURRENT_ONLY,
    OVER_RATING_ONLY,
    BOTH_FAULTS
  };

  FaultEvent getEvent();
  void handleOverCurrentOnly();
  void handleOverRatingOnly();
  void handleBothFaults();

  unsigned long soundTimer = 0;
};  