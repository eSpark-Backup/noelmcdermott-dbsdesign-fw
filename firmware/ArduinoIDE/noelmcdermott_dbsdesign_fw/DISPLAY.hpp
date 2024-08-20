#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>



class Display {
public:
  Display();
  void init();
  void show(const String &message, int line);
  void clearLCD();
private:
  uint8_t LCD_I2C_ADDR = 0x27;
  uint8_t LCD_X_DIM = 20;
  uint8_t LCD_Y_DIM = 4;

  LiquidCrystal_I2C lcd;
};
