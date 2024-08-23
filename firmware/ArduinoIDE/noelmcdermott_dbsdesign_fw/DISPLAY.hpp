#pragma once
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_I2C_ADDR 0x27
#define LCD_X_DIM 20
#define LCD_Y_DIM 4
class Display {
public:
  Display();
  void init();
  void show(const String &message, int line);
  void clear();
private:
  LiquidCrystal_I2C lcd;
};
