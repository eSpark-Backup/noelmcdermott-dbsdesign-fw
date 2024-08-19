#pragma once
#include<Arduino.h>
#include <Wire.h>  
#include <LiquidCrystal_I2C.h> 



class Display
{
  public:
  void init();
  void show(const String &message,int line);
  void clearLCD();
};

