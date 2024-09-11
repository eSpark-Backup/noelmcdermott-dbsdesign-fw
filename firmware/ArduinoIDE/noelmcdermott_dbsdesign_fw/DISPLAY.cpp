#include "DISPLAY.hpp"

Display::Display()
  : lcd(LCD_I2C_ADDR, LCD_X_DIM, LCD_Y_DIM) {
}

void Display::init() {
  lcd.begin();
  lcd.backlight();
}

void Display::show(const String &message, int line) {
  lcd.clear();                  // Clear previous message
  if (line >= 0 && line < LCD_Y_DIM) {  // Check if the line number is valid
    lcd.setCursor(0, line);     // Set cursor to the specified line
    lcd.print(message);         // Print the message
  }

  //For testing
  #if SERIAL_TEST
  Serial.println(message);
  #endif
  
}
void Display::clear() {
  lcd.clear();
}