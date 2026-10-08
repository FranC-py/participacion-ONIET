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
  char keys[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
  };

  void init();
  char getKey();
};

#endif
