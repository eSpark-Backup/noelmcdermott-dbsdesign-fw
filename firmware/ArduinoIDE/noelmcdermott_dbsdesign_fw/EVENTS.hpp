#pragma once
#include<Arduino.h>
#include <TMCStepper.h>
#include "LED.hpp"
#include "Stepper_States.hpp"
#include "variable_init.hpp"
#include"DISPLAY.hpp"



#define MODE_SELECT_V12                 5               //mode selection switch state (“Run” = 1, “Test” = 0)
#define EXTERNAL_INPUT                  A0               //EXTERNAL INPUT
#define LIMIT_SWITCH                     6               //LIMIT SWITCH
#define RESET_V9                         7               //RESET PUSH BUTTTON

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
  // event_t events;
};  