/*======================================================
    INFRARED SENSOR COUNTER WITH 7 SEGMENT DISPLAY
========================================================
Description:
  This program reads a digital signal from an infrared
  obstacle sensor to count detected objects. The system
  increments the count from 0 to 99, resetting back to 0
  upon reaching 100, and outputs the real-time count
  onto a dual common-cathode 7-segment display.

Programmer: 
  Sergie D. Gomez

Date: 
  16 October 2026
------------------------------------------------------*/

const uint8_t OUT = 2;

const uint8_t TENS_PINS[] = {4, 16, 17, 5, 18, 19, 21};
const uint8_t ONES_PINS[] = {32, 33, 25, 26, 27, 14, 12};
const uint8_t NUM_SEG7 = sizeof(TENS_PINS) / sizeof(TENS_PINS[0]);

int Number_of_Object = 0;
int SensorState = 0;
int lastSensorState = 1;

#include "decoder.h"

void setup() {
  Serial.begin(9600);
  pinMode(OUT, INPUT);

  for (int i = 0; i < NUM_SEG7; i++) {
    pinMode(TENS_PINS[i], OUTPUT);
    pinMode(ONES_PINS[i], OUTPUT);
  }

  decoder(0);
}

void loop() {
  SensorState = digitalRead(OUT);
  if (SensorState == 0 && lastSensorState == 1) {
    Number_of_Object++;
    if (Number_of_Object > 99) {
      Number_of_Object = 0;
    }
    Serial.printf("Object detected! Total: %d\n", Number_of_Object);
    decoder(Number_of_Object);
    delay(200);
  }
  lastSensorState = SensorState;
}
