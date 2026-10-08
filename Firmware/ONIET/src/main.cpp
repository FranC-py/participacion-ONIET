#include <Arduino.h>
#include <lcd.h>
#include <dth11.h>

bool estado = true; // True = Activo, False = Bloqueado
int psw = 1234; // Contraseña de acceso

void sensarDHT11(void *pvParameters) {
  float temperatura, humedad;
  while(true) {
    while(estado) {
      temperatura = read_temperature();
      humedad = read_humidity();
      Serial.print("Temperatura: ");
      Serial.print(temperatura);
      Serial.print(" °C, Humedad: ");
      Serial.print(humedad);
      Serial.println(" %");
      vTaskDelay(pdMS_TO_TICKS(2000));
    }
  }
}

void ingresarClave(void *pvParameters) {
  int claveIngresada = 0;
  while(true) {
    while(!estado) {
      claveIngresada
      if(claveIngresada == psw) {
        estado = true; // Desbloquear el sistema
        Serial.println("Sistema desbloqueado");
      } else {
        Serial.println("Clave incorrecta");
      }
      vTaskDelay(pdMS_TO_TICKS(5000)); // Esperar antes del próximo intento
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht11_init();
  lcd_init();

}

void loop() {
}
