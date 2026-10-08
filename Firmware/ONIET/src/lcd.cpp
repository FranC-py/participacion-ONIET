#include <Arduino.h>
#include <liquidcrystal_I2C.h>

#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2
#define SDA_PIN 8
#define SCL_PIN 9

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

void init_lcd(){

    lcd.init();
    lcd.backlight();
}

void escribir_lcd(const char* mensaje, int fila, int columna){
    lcd.setCursor(columna, fila);
    lcd.print(mensaje);
}

void borrar_lcd(){
    lcd.clear();
}