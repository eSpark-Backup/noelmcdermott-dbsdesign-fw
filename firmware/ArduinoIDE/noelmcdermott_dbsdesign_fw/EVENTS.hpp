#pragma once
#include "DISPLAY.hpp"
#include "Stepper_States.hpp"

class Events
{
  public:
    void setup(Display *dis, Stepper *step);
    void errorEvents();
    void resetErrorEvent();

  private:
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

    Display *display;
    Stepper *stepper_motor;
};  