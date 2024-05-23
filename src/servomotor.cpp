#include <Arduino.h>
#include <Servo.h>

#define SERVO_PIN 3

Servo servo;

void setup() {
  servo.attach(SERVO_PIN);
}

void loop() {
    servo.write(0);
    delay(1000);
    servo.write(90);
    delay(3000);
}