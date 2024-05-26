#ifndef LCD_H
#define LCD_H

#include <LiquidCrystal_I2C.h>

void setupLCD();
void updateLCD(const char* time, const char* date);

#endif 
