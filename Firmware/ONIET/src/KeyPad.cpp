#include <Arduino.h>
#include "KeyPad.h"

void KeyPad::init() {
  pinMode(row1, INPUT_PULLUP);
  pinMode(row2, INPUT_PULLUP);
  pinMode(row3, INPUT_PULLUP);
  pinMode(row4, INPUT_PULLUP);
  pinMode(col1, OUTPUT);
  pinMode(col2, OUTPUT);
  pinMode(col3, OUTPUT);
  pinMode(col4, OUTPUT);
  digitalWrite(col1, HIGH);
  digitalWrite(col2, HIGH);
  digitalWrite(col3, HIGH);
  digitalWrite(col4, HIGH);
}
void KeyPad::getKey() {
  for (int col = 0; col < 5; col++) {
    digitalWrite(col1 + col, LOW);
    for (int row = 0; row < 5; row++) {
      if (digitalRead(row1 + row) == LOW) {
        digitalWrite(col1 + col, HIGH);
        return keys[row][col];
      }
    }
    digitalWrite(col1 + col, HIGH);
  }
  return NO_KEY;
}