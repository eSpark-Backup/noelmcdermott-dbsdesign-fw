
#ifndef ERROR_HANDLER_HPP
#define ERROR_HANDLER_HPP

class ErrorHandler {
  public:
    bool checkResetButton(int pin);
    void InterruptSetup(int pin);
  private:
    unsigned long lastPressTime = 0;
};

#endif  // ERROR_HANDLER_HPP