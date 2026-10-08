/**
 * @file hardware_tasks.h
 * @brief Base task definitions for ESP32 hardware components using FreeRTOS.
 * 
 * Provides template tasks for concurrent execution of hardware drivers.
 * Adjust pin definitions according to the specific hardware layout.
 */

#ifndef HARDWARE_TASKS_H
#define HARDWARE_TASKS_H

#include <Arduino.h>

// ----------------------------------------------------------------------------
// DHT Sensor Configuration
// ----------------------------------------------------------------------------
#include <DHT.h>

#define DHT_DATA_PIN 4
#define DHT_TYPE     DHT11  // Update to DHT22 if applicable

DHT dht(DHT_DATA_PIN, DHT_TYPE);

/**
 * @brief Task for reading temperature and humidity periodically.
 * Executes on a 2000ms interval due to DHT sensor timing constraints.
 */
void dht_task(void *pvParameters) {
    dht.begin();
    
    for (;;) {
        float humidity = dht.readHumidity();
        float temperature = dht.readTemperature();

        if (!isnan(humidity) && !isnan(temperature)) {
            Serial.printf("[DHT] Temp: %.1f C, Hum: %.1f %%\n", temperature, humidity);
        }
        
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

// ----------------------------------------------------------------------------
// LiquidCrystal I2C Configuration
// ----------------------------------------------------------------------------
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

/**
 * @brief Initializes the LCD. Must be called in setup().
 */
void init_lcd() {
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("System Ready");
}

/**
 * @brief Task for updating the UI asynchronously.
 */
void display_task(void *pvParameters) {
    for (;;) {
        lcd.setCursor(0, 1);
        lcd.print(millis() / 1000);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// ----------------------------------------------------------------------------
// Matrix Keypad Configuration
// ----------------------------------------------------------------------------
#include <Keypad.h>

const byte KEYPAD_ROWS = 4;
const byte KEYPAD_COLS = 4;

char keys[KEYPAD_ROWS][KEYPAD_COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[KEYPAD_ROWS] = {9, 10, 11, 12}; 
byte colPins[KEYPAD_COLS] = {13, 14, 15, 16}; 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLS);

/**
 * @brief Task for non-blocking keypad polling.
 */
void keypad_task(void *pvParameters) {
    for (;;) {
        char key = keypad.getKey();
        if (key) {
            Serial.printf("[KEYPAD] Key pressed: %c\n", key);
        }
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

// ----------------------------------------------------------------------------
// Relay Configuration
// ----------------------------------------------------------------------------
#define RELAY_PIN 5

/**
 * @brief Example task for controlling relay states.
 */
void relay_task(void *pvParameters) {
    pinMode(RELAY_PIN, OUTPUT);
    
    for (;;) {
        digitalWrite(RELAY_PIN, HIGH);
        vTaskDelay(pdMS_TO_TICKS(3000));
        
        digitalWrite(RELAY_PIN, LOW);
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

// ----------------------------------------------------------------------------
// Button Configuration
// ----------------------------------------------------------------------------
#define BUTTON_PIN 6

/**
 * @brief Task for debouncing and reading digital inputs.
 */
void button_task(void *pvParameters) {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    
    for (;;) {
        if (digitalRead(BUTTON_PIN) == LOW) {
            Serial.println("[BUTTON] Triggered");
            vTaskDelay(pdMS_TO_TICKS(200)); // Basic debounce
        }
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

// ----------------------------------------------------------------------------
// Buzzer Configuration
// ----------------------------------------------------------------------------
#define BUZZER_PIN 7

/**
 * @brief Task for handling active buzzer sequences.
 */
void active_buzzer_task(void *pvParameters) {
    pinMode(BUZZER_PIN, OUTPUT);
    for (;;) {
        digitalWrite(BUZZER_PIN, HIGH);
        vTaskDelay(pdMS_TO_TICKS(100));
        digitalWrite(BUZZER_PIN, LOW);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

/**
 * @brief Task for handling passive buzzer tones.
 */
void passive_buzzer_task(void *pvParameters) {
    for (;;) {
        tone(BUZZER_PIN, 1000);
        vTaskDelay(pdMS_TO_TICKS(200));
        noTone(BUZZER_PIN);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

/**
 * @section FreeRTOS_Usage_Guide
 * @brief Reference for instantiating and managing tasks.
 * 
 * CORE CONCEPTS:
 * 1. Infinite Loops: A FreeRTOS task must never return. It must contain an 
 *    infinite loop (e.g., for(;;)). If a task needs to end, it MUST call 
 *    vTaskDelete(NULL) instead of returning.
 * 
 * 2. Non-blocking Delays: NEVER use Arduino's delay(). It halts the CPU.
 *    Always use vTaskDelay(pdMS_TO_TICKS(ms)). This tells the RTOS scheduler 
 *    to yield the CPU to other tasks while waiting.
 * 
 * 3. Dual-Core Allocation (ESP32): The ESP32-S3 has two cores (Core 0 & Core 1).
 *    Use xTaskCreatePinnedToCore to assign heavy tasks (like I/O or displays) 
 *    to Core 0, and critical sensor reads to Core 1.
 * 
 * @example setup_tasks
 * @code
 * void setup() {
 *     // Example of Task Creation:
 *     // xTaskCreatePinnedToCore(
 *     //     TaskFunction,  // Function pointer to the task
 *     //     "TaskName",    // String name for debugging
 *     //     2048,          // Stack size in words (2048 is usually safe)
 *     //     NULL,          // Task input parameter
 *     //     1,             // Priority (0 = lowest, 24 = highest)
 *     //     NULL,          // Task handle (for suspending/resuming)
 *     //     1              // Core ID (0 or 1)
 *     // );
 * 
 *     xTaskCreatePinnedToCore(dht_task, "DHT_Task", 2048, NULL, 1, NULL, 1);
 *     xTaskCreatePinnedToCore(keypad_task, "Keypad_Task", 2048, NULL, 1, NULL, 0);
 * }
 * @endcode
 */

#endif // HARDWARE_TASKS_H
