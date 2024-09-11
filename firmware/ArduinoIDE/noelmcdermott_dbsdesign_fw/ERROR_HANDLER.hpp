
#ifndef ERROR_HANDLER_HPP
#define ERROR_HANDLER_HPP
#include <Arduino.h>
#include "EVENTS.hpp"

class ErrorHandler {
public:
  bool isError();
  bool checkResetButton(int pin);
  
};

#endif // ERROR_HANDLER_HPP