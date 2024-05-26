#include <Wire.h>
#include <RTClib.h>
#include "rtc.h"

RTC_DS3231 rtc;

void setupRTC() {
    if (!rtc.begin()) {
        while (1) {
            Serial.println("Couldn't find RTC");
        }
    }
    if (rtc.lostPower()) {
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    //rtc.adjust(DateTime(2024, 5, 26, 17, 07, 0));
}

DateTime getRTCTime() {
    return rtc.now();
}
