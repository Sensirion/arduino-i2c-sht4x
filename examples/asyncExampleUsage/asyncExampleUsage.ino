/*
 * Non-blocking SHT4x Measurement Example
 * 
 * This example shows how to use asyncStartMeasurement() to run measurements
 * without blocking your program. This works for both heated and non-heated
 * measurements. Your device can perform other tasks while waiting for the
 * measurement to complete.
 * 
 * The pattern is simple:
 * 1. Start the measurement (heated or non-heated)
 * 2. Do other work while waiting
 * 3. Check if ready
 * 4. Read the results
 */

#include <Arduino.h>
#include "SensirionI2cSht4x.h"
#include <Wire.h>

// make sure that we use the proper definition of NO_ERROR
#ifdef NO_ERROR
#undef NO_ERROR
#endif
#define NO_ERROR 0

SensirionI2cSht4x sensor;
const unsigned long MEASUREMENT_INTERVAL_MS = 5000;
unsigned long lastMeasurementTime = 0;
int16_t measurementStatus = -1;  // -1=idle, 0=success, non-zero=error code

bool useHeater = false;  // Alternate between heated and non-heated measurements

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        delay(100);
    }
    
    Wire.begin(16,17);  // Using GPIO pins 16 (SDA) and 17 (SCL)
    sensor.begin(Wire, SHT41_I2C_ADDR_44);
    
    Serial.println("SHT4x Unified Async Example");
    Serial.println("============================");
    Serial.println("Alternates between heated and non-heated measurements");
    Serial.println();
}

void loop() {
    float temperature = 0.0;
    float humidity = 0.0;
    
    // Only start a new measurement every 5 seconds
    if (millis() - lastMeasurementTime >= MEASUREMENT_INTERVAL_MS) {
        // Step 1: Start a measurement (heated or non-heated)
        if (useHeater) {
            Serial.println("Starting HEATED measurement (medium long)...");
            measurementStatus = sensor.asyncStartMeasurement(SHT4X_HEATER_MEDIUM_LONG);
        } else {
            Serial.println("Starting NON-HEATED measurement (high precision)...");
            measurementStatus = sensor.asyncStartMeasurement(SHT4X_PRECISION_HIGH);
        }
        
        if (measurementStatus != 0) {
            Serial.println("Error starting measurement. Check sensor connection.");
            lastMeasurementTime = millis();  // Try again in 5 seconds
        } else {
            lastMeasurementTime = millis();
            useHeater = !useHeater;  // Alternate measurement type for next sample
        }
    }
    
    // Step 2: Do other work while the measurement runs
    for (int i = 0; i < 2; i++) {
        Serial.print("Working on other tasks... ");
        Serial.println(i);
        delay(400);  // Simulates doing other tasks
    }
    
    // Step 3: Check if the measurement is ready
    if (sensor.asyncIsMeasurementReady() && measurementStatus == 0) {
        // Step 4: Read the results
        measurementStatus = sensor.asyncReadMeasurement(temperature, humidity);

        if (measurementStatus == 0) {
            Serial.println();
            Serial.println("=== Results ===");
            if (useHeater) {
                Serial.print("Temperature: ");
                Serial.print(temperature);
                Serial.println(" °C");
            } else {
                Serial.println("Heating mode.  Temperature value ignored.");
            }
            Serial.print("Humidity:    ");
            Serial.print(humidity);
            Serial.println(" %RH");
            Serial.println();
            measurementStatus = -1;  // Reset status to idle
            delay(2000);  // Give user time to read results
        } else {
            Serial.println("Error reading measurement. Check sensor connection.");
            measurementStatus = -1;  // Explicitly reset status to idle
        }
    }
}
