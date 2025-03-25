#pragma once
#include "DISPLAY.hpp"

class Events
{
  public:
    void setup(Display *dis);
    void errorEvents();
    void resetErrorEvent();

  private:
    unsigned long soundTimer = 0;
    
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
};  