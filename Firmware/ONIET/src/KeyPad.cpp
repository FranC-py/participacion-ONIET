#include <Arduino.h>
#include "KeyPad.h"

void KeyPad::init() {
  const int rowPins[] = {row1, row2, row3, row4};
  const int colPins[] = {col1, col2, col3, col4};

  for (int i = 0; i < 4; i++) {
    pinMode(rowPins[i], INPUT_PULLUP);
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }
}

char KeyPad::getKey() {
  const int rowPins[] = {row1, row2, row3, row4};
  const int colPins[] = {col1, col2, col3, col4};

  for (int col = 0; col < 4; col++) {
    digitalWrite(colPins[col], LOW);
    for (int row = 0; row < 4; row++) {
      if (digitalRead(rowPins[row]) == LOW) {
        digitalWrite(colPins[col], HIGH);
        return keys[row][col];
      }
    }
    digitalWrite(colPins[col], HIGH);
  }

  return NO_KEY;
}