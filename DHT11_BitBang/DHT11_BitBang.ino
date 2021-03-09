/**
 * @file DHT11_BitBang.ino
 *
 * @author Protik Banerji (protik09@gmail.com)
 * @brief Bit Bang the DHT11 Protocol with a Teensy 4.0
 * @version 0.1
 * @date 2021-03-04
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <Arduino.h>
#include "dht11.h"

// Globals
bool exitFlag = false;
Dht11 dht11(DHT11PIN); // Init DHT11 object

// SETUP
void setup()
{
    // Calculate DHT11 datarate
    uint32_t dht11_micros_per_bit = uint32_t(float(1 / DHT11_BITRATE) * 1000000);

    // Starup serial port
    Serial.begin(115200);
    while (!Serial); // wait for Arduino Serial Monitor

    delay(500);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWriteFast(LED_BUILTIN, HIGH);
    Serial.println("Micontroller setup complete");
    Serial.println("The sensor data rate is set to " + String(dht11_micros_per_bit) + "us per bit");
    delay(2000);

    // Probably only useful with teensy till I test otherwise
    // while(!startup())
    // {
    //     // Do nothing till user action is received.
    // };
    // digitalWriteFast(LED_BUILTIN, HIGH);
}

// Infinite loop
void loop()
{
    // Request DHT11
    dht11.Request();

    // Listen to DHT11
    if (dht11.Ack() == true)
    {
        Serial.println("SUCCESS: Sensor Replied to your dulcet tones.");
    }
    else
    {
        exit();// Do nothing since error handling is done in the class.
    }
}

// Exit loop
void exit(int exit_code)
{
    digitalWriteFast(LED_BUILTIN, LOW);
    Serial.println("Program Ended. Exit code: " + String(exit_code));
    while (true)
    {
        ; // Do nothing program halt
    }
    
}