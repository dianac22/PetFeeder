#include <Arduino.h>
#include <HX711.h>

#define LOADCELL_DOUT_PIN 2
#define LOADCELL_SCK_PIN 3

HX711 scale;

//TO DO: calibration factor

void setup() {
    Serial.begin(9600);
    Serial.println("HX711 Demo");
    scale.begin(2, 3);
    scale.set_scale();
    scale.tare();
}

void loop() {
    if (scale.is_ready()) {
        long reading = scale.read();
        Serial.print("Reading: ");
        Serial.print(reading);
    }
    else {
        Serial.println("HX711 not found.");
    }
    delay(1000);
}