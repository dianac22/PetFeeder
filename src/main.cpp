#include <Arduino.h>
#include <Servo.h>
#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "lcd.h"
#include "rtc.h"

const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {4, 5, 6, 7};
byte colPins[COLS] = {8, 9, 10, 11};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

Servo myServo;
int servoPin = 12;
int gateOpen = 90;
int gateClose = 0;

int setHour = -1, setMinute = -1;
bool timeSet = false;

const int buttonPin = 13;
int buttonState = 0;

int buzzerPin = 14;

void handleKeypadInput();
void openGate();

void setup() {
  Serial.begin(9600);
  setupLCD();
  setupRTC();
  myServo.attach(servoPin);
  myServo.write(gateClose); // Initially the gate is closed
  pinMode(buttonPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    handleKeypadInput();
  } else {
    DateTime now = getRTCTime();

    char timeStr[16]; 
    sprintf(timeStr, "%02d:%02d:%02d", now.hour(), now.minute(), now.second());

    char dateStr[16]; 
    sprintf(dateStr, "%02d/%02d/%04d", now.day(), now.month(), now.year());

    updateLCD(timeStr, dateStr);

    // Print to Serial Monitor for debugging
    Serial.print("Time: ");
    Serial.println(timeStr);
    Serial.print("Date: ");
    Serial.println(dateStr);

    if (timeSet) {
      Serial.print("Set Feeding Time: ");
      Serial.print(setHour);
      Serial.print(":");
      Serial.println(setMinute);

      if (now.hour() == setHour && now.minute() == setMinute && now.second() == 0) {
        openGate();
      }
    }

    delay(1000);
  }
}

void handleKeypadInput() {
  static String input = "";
  static int inputState = 0;
  char key;
  bool inputComplete = false;

  while (!inputComplete) {
    key = keypad.getKey();
    if (key) {
      if (key >= '0' && key <= '9') {
        input += key;
        updateLCD(input.c_str(), "Enter feeding time");
        Serial.print("Input: ");
        Serial.println(input);
      }

      if (key == 'A' && inputState == 0) {
        setHour = input.toInt();
        input = "";
        inputState = 1;
        updateLCD("Hour set", "");
        Serial.print("Hour set: ");
        Serial.println(setHour);
      } else if (key == 'B' && inputState == 1) {
        setMinute = input.toInt();
        input = "";
        inputComplete = true;
        timeSet = true;
        inputState = 0; // Reset state for next input
        updateLCD("Minute set", "");
        Serial.print("Minute set: ");
        Serial.println(setMinute);
      }
    }
  }
}

void soundBuzzer(int frequency) {
  tone(buzzerPin, frequency);  
  delay(500);                   
  noTone(buzzerPin);           
}

void openGate() {
  Serial.println("Gate is opening...");
  myServo.write(gateOpen);
  soundBuzzer(1000);
  delay(2000);
  myServo.write(gateClose);
  Serial.println("Gate is closed.");
}