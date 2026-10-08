#include <Arduino.h>
#include <DHT.h>

#define DHT_PIN 11
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

void init_dht11(){
    dht.begin();
}

float read_temperature(){
    return dht.readTemperature();
}

float read_humidity(){
    return dht.readHumidity();
}