#include "LoadCell.h"
#include <Arduino.h>

HX711 scale;

void setupCell() {
  Serial.begin(9600);
  Serial.println("HX711 scale demo");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor); // This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); // Assuming there is no weight on the scale at start up, reset the scale to 0

  Serial.println("Readings:");
}

float getWeight() {
  return scale.get_units(10); // Average 10 readings
}
