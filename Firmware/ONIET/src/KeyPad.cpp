#include <Arduino.h>
#include "KeyPad.h"

KeyPad::KeyPad(byte row1, byte row2, byte row3, byte row4,
               byte col1, byte col2, byte col3, byte col4)
    : rowPins{row1, row2, row3, row4},
      colPins{col1, col2, col3, col4} {}

void KeyPad::init() {
  for (byte i = 0; i < 4; i++) {
    pinMode(rowPins[i], INPUT_PULLUP);
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }
}

char KeyPad::getKey() {
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