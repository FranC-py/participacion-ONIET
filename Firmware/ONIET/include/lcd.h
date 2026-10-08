#ifndef LCD_H
#define LCD_H

#include <Arduino.h>

void init_lcd();
void escribir_lcd(const char* mensaje, int fila, int columna);
void borrar_lcd();

#endif