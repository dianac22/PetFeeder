#include <Arduino.h>
#include "lcd.cpp"
#include "rtc.cpp"

void setup() {
  Wire.begin();
  lcd.init();
  lcd.backlight();

  if (!rtc.begin()) {
    lcd.setCursor(0, 0);
    lcd.print("RTC failed");
    while (1);
  }

  lcd.setCursor(0, 0);
  lcd.print("Current time: ");
}

void loop() {
  DateTime now = rtc.now();

  lcd.setCursor(0, 1); 
  lcd.print(String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()));

  delay(1000);
}