#ifndef KEYPAD_H
#define KEYPAD_H

#include <Arduino.h>

class KeyPad {
public:
  KeyPad(byte row1, byte row2, byte row3, byte row4,
         byte col1, byte col2, byte col3, byte col4);

  void init();
  char getKey();

private:
  byte rowPins[4];
  byte colPins[4];
  const char keys[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
  };
};

#endif
