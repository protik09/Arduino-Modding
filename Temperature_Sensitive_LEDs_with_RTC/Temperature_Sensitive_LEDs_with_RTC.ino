/* Read the temperature in celcius over serial.
 *
 *
 * To see this sketch in action open up the serial
 * monitor. Clamp your fingers over the LM35
 * sensor. The temperature will rise and then fall
 * as you remove your fingers.
 *
 * The circuit:
 * - LM35 to 5v, GND, and Vo to analog 0
 *
 */
 // Test Functions for  DS3231 RTC LIBRARY connected via I2C and Wire lib
//   Excellent for use with the macetech.com Chronodot
//
//  INCLUDES base code with detailed comments for setting up Timer0 or Timer1 as input counters.
//   These input counters are useful for more accurate interrupt-based timekeeping.
//
//
// CREDITS:
// Base for code thanks to Jeelabs on the DS1307
// Modified by Red Byer 7/25/2013 for DS3231   www.redstoyland.com   Find code on github  under mizraith
// Released to public domain.  Buy me a beer if you like or use the code.

// CONNECTIONS:
// DS3231 SDA --> A4    Don't forget to pullup (4.7k to VCC)
// DS3231 SCL --> A5    Don't forget to pullup (4.7k to VCC)
// SQW --->  D5 / T1 (pick this or 32kHz to test)  Don't forget to pullup (4.7k to 10k to VCC)
// 32k --->  D5 / T1  Don't forget to pullup (4.7k to 10k to VCC)

#include <Wire.h>
#include <SPI.h>
#include <RTClib.h>
#include <RTC_DS3231.h>

RTC_DS3231 RTC;

// the output pin of the LM35 temperature sensor
int lm35Pin = A0;
// an array of pin numbers to which LEDs are attached
// to add more LEDs just list them here in this array
int ledPins[] = {2,7,9,12};

void setup()
{
    // set up serial at 9600 baud   
    Serial.begin(9600);
    
    Wire.begin();
    RTC.begin();
    
    // Setup the LEDs as output
    pinMode(2,OUTPUT);
    pinMode(7,OUTPUT);
    pinMode(9,OUTPUT);
    pinMode(12,OUTPUT);
    
    // Set all digital pins to LOW
    
    digitalWrite(7,LOW);
    digitalWrite(2,LOW);
    digitalWrite(9,LOW);
    digitalWrite(12,LOW);
    
    
}

void loop()
{ 
    int analogValue;
    float temperature;
    
    //Read temperature sensor in RTC
    RTC.forceTempConv(true);  //DS3231 does this every 64 seconds, we are simply testing the function here
    float temp_float = RTC.getTempAsFloat();
    int16_t temp_word = RTC.getTempAsWord();
    int8_t temp_hbyte = temp_word >> 8;
    int8_t temp_lbyte = temp_word &= 0x00FF;

    // read our temperature sensor
    analogValue = analogRead(lm35Pin);

    // convert the 10bit analog value to celcius
    temperature = float(analogValue) / 1023;
    temperature = temperature * 500;

    // print the temperature over serial
    Serial.print("TempSensorLM35: ");
    Serial.print(temperature);
    Serial.println("C");
    
    //Display temps
    //Serial.print("Temp as float RTC: ");
    //Serial.print(temp_float, DEC);
    Serial.println();
    Serial.print("Temp as word RTC: ");
    Serial.print(temp_hbyte, DEC);
    Serial.print(".");
    Serial.print(temp_lbyte, DEC);
    Serial.println("C");
    
    Serial.println();
    
    //Calculating average temperature
    
    float tempav=(temp_float+temperature)/2;
    
    
    //Read Temp and turn on corresponding LED
    
    if(tempav>18.0)
    {
      digitalWrite(2,HIGH);
      digitalWrite(7,LOW);
      digitalWrite(9,LOW);
      digitalWrite(12,LOW);
    }
    
    else if(tempav<=18&&tempav>14)
    {
      digitalWrite(7,HIGH);
      digitalWrite(2,LOW);
      digitalWrite(9,LOW);
      digitalWrite(12,LOW);
    }
    
    else if(tempav<=14&&tempav>10)
    {
      digitalWrite(9,HIGH);
      digitalWrite(7,LOW);
      digitalWrite(2,LOW);
      digitalWrite(12,LOW);
    }
    
    else if(tempav<10)
    {
      digitalWrite(12,HIGH);
      digitalWrite(2,LOW);
      digitalWrite(7,LOW);
      digitalWrite(9,LOW);
    }
    
    // wait 1s before reading the temperature again
    delay(1000);
}

