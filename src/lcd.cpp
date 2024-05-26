#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "lcd.h"
#include <Arduino.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setupLCD() {
    lcd.init();
    lcd.backlight();
    lcd.clear();
}

void updateLCD(const char* time, const char* date) {
    lcd.setCursor(0, 0);
    lcd.print(time);
    lcd.setCursor(0, 1);
    lcd.print(date);
}