#ifndef DHT11_H
#define DHT11_H

#include <Arduino.h>

void init_dht11();
float read_temperature();
float read_humidity();

#endif