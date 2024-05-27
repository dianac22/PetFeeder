#ifndef LOADCELL_H
#define LOADCELL_H

#include "HX711.h"

#define calibration_factor 5500.0 // Value obtained using a calibration sketch
#define LOADCELL_DOUT_PIN  3
#define LOADCELL_SCK_PIN  2

extern HX711 scale;

void setupCell();
float getWeight();

#endif 
