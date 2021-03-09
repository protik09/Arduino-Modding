#pragma once
/**
 * @file dht11.h
 * 
 * @author Protik Banerji (protik09@gmail.com)
 * @brief Bit Bang the DHT11 Protocol with a Teensy 4.0
 * @version 0.1
 * @date 2021-03-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

// Since the smallest bit received from the DHT11 takes 24us, we can assume a communication rate of 41666 bps.

#define DHT11PIN 8u
#define DHT11_BITRATE 41666 // 41666.67 bps
// #define DHT11_MICROS_PER_BIT (float(1 / DHT11_BITRATE) * 1000000)
#define DHT11_ACK_RESPONSE1 55u
#define DHT11_ACK_RESPONSE2 80u
#define ACK HIGH
// #define Serial Serial1 // Remove before compile. Hack for vscode linting
// #define NO_ACK LOW

extern volatile bool linelevel;

// Function definitions
bool startup();
void exit(int exit_code = 0);

// Class Definitions
class Dht11
{
    private:
        uint8_t sensor_pin;
    public:
        Dht11::Dht11(uint8_t sensor_pin);
        void Request();
        bool Ack();
};

Dht11::Dht11(uint8_t _sensor_pin)
{
    sensor_pin = _sensor_pin;
    pinMode(sensor_pin, OUTPUT);
    digitalWriteFast(sensor_pin, HIGH);  //Initial pin high to sensor
    delay(1000); // Wait 1s after powerup to get good readings
}

void Dht11::Request()
{
    pinMode(sensor_pin, OUTPUT);
    digitalWriteFast(sensor_pin, LOW);
    delay(20);                           // Wait > 18ms 
    digitalWriteFast(sensor_pin, HIGH);  //Initial pin high before pulling low
    delayMicroseconds(13);               // Wait at least 10-20us
}

bool Dht11::Ack()
{
    uint16_t low_counter = 0, high_counter = 0;
    uint16_t timeout = 100;
    elapsedMicros time_count = 0;
    pinMode(sensor_pin, INPUT);

    uint16_t old_time = 0;
    // Read ACK low
    while (digitalReadFast(sensor_pin) == LOW)
    {
        if ((low_counter < timeout) && (time_count > old_time))
        {
            low_counter++;
        }
        else if (low_counter == timeout)
        {
            Serial.println("ERROR: Timed out on receive LOW. Low Counter: " + String(low_counter));
            return !ACK;
        }
        else
        {
            ;// Do nothing
        }
        
        old_time = time_count;
    }

    // Read ACK high
    old_time = 0;
    if (low_counter <= 81)
    {
        while (digitalReadFast(sensor_pin) == HIGH)
        {
            if ((high_counter < timeout) && (time_count > old_time))
            {
                high_counter++;
            }
            else if(high_counter == timeout)
            {
                Serial.println("ERROR: Timed out on receive HIGH. High Counter: " + String(high_counter));
                return !ACK;
            }
            else
            {
                ; // Do Nothing
            }
        }
        old_time = time_count;
    }
    else
    {
            Serial.println("ERROR: DHT11 Took too long to reply. Low Counter: " + String(low_counter));
            return !ACK;
    }
    

    // Check low and high count
    if ((low_counter <= 81) && (high_counter <= 81))
    {
        return ACK;
    }
    else
    {
        Serial.println("ERROR: DHT11 Took too long to reply. Low Counter: " + String(low_counter));
        Serial.println("ERROR: DHT11 Took too long to reply. High Counter: " + String(high_counter));
        return !ACK;
    }
}

