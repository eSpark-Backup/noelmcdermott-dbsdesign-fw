
#include <Wire.h>
#include "DISPLAY.hpp"

Display::Display()
  : lcd(LCD_I2C_ADDR, LCD_X_DIM, LCD_Y_DIM) {
}

void Display::init() {
  Wire.setPins(18, 17);
  lcd.begin();
  lcd.backlight();
}

void Display::show(const String &message, int line)
{
  if (line >= 0 && line < LCD_Y_DIM)
  {
    lcd.setCursor(0, line);             
    lcd.print(message);                 
  }

//For testing
#if SERIAL_TEST
  Serial.println(message);
#endif
}

void Display::clear()
{
  lcd.clear();
}