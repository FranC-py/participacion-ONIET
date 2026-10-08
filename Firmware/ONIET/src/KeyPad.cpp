#include <Arduino.h>
#include "KeyPad.h"

void KeyPad::init() {
  const byte rowPins[] = {row1, row2, row3, row4};
  const byte colPins[] = {col1, col2, col3, col4};

  for (byte i = 0; i < 4; i++) {
    pinMode(rowPins[i], INPUT_PULLUP);
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }
}

char KeyPad::getKey() {
  const byte rowPins[] = {row1, row2, row3, row4};
  const byte colPins[] = {col1, col2, col3, col4};

  for (byte col = 0; col < 4; col++) {
    digitalWrite(colPins[col], LOW);

    for (byte row = 0; row < 4; row++) {
      if (digitalRead(rowPins[row]) == LOW) {
        digitalWrite(colPins[col], HIGH);
        return keys[row][col];
      }
    }

    digitalWrite(colPins[col], HIGH);
  }

  return '\0';
}