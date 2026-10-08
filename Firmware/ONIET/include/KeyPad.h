#ifndef KEYPAD_H
#define KEYPAD_H

#include <Arduino.h>

class KeyPad {
public:
  int row1;
  int row2;
  int row3;
  int row4;
  int col1;
  int col2;
  int col3;
  int col4;
  char keys[4][4];

  static constexpr char NO_KEY = '\0';

  void init();
  char getKey();
};

#endif