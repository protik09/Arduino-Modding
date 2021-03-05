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
// #include <HardwareSerial.h>
#include "dht11.h"

volatile bool linelevel;
elapsedMillis timer_mil;
elapsedMicros timer_mic;
unsigned long response;

void setup()
{
    Serial.begin(115200);
    while (!Serial); // wait for Arduino Serial Monitor
    delay(500);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWriteFast(LED_BUILTIN, HIGH); //
    Serial.println("Micontroller setup complete");
}

void loop()
{
    // Request DHT11
    Serial.println("Sending initial ping to DHT11");
    pinMode(DHT11PIN, OUTPUT);
    digitalWriteFast(DHT11PIN, HIGH); //Initial pin high before pulling low
    digitalWriteFast(DHT11PIN, LOW);
    delay(18); // Wait 18ms
    digitalWriteFast(DHT11PIN, HIGH); //Initial pin high before pulling low
    delayMicroseconds(40); // Wait 40us
    // Listen to DHT11
    pinMode(DHT11PIN, INPUT);
    timer_mic = 0;
    while (digitalReadFast(DHT11PIN) == HIGH)
    {
        ;
    } 
}
