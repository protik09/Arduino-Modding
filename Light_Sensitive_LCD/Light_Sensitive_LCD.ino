/*
 * Tutorial 8: Using the LCD
 * 
 * Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 * library works with all LCD displays that are compatible with the 
 * Hitachi HD44780 driver. There are many of them out there, and you
 * can usually tell them by the 16-pin interface.
 *
 * Adjust the LCDs contrast with the Potentiometer until you
 * can see the characters on the LCD.
 *
 * The circuit:
 * - LCD RS pin to digital pin 12
 * - LCD Enable pin to digital pin 11
 * - LCD D4 pin to digital pin 2
 * - LCD D5 pin to digital pin 3
 * - LCD D6 pin to digital pin 4
 * - LCD D7 pin to digital pin 5
 * - LCD R/W pin to ground
 * - 10K potentiometer divider for LCD pin VO:
 * - 330ohm resistor betweenm LCD pin A and 5v
 * - LCD pin K to ground
 *
 * The Ultrasonic Rangefinder circuit:
 * - 5v, ground connected to Ultrasonic sensor
 * - digital pin 6 conneceted to Ultrasonic sensor echo pin
 * - digital pin 7 conneceted to Ultrasonic sensor trig pin
 *
 * Library originally added 18 Apr 2008
 * by David A. Mellis
 * library modified 5 Jul 2009
 * by Limor Fried (http://www.ladyada.net)
 * example added 9 Jul 2009
 * by Tom Igoe
 * modified 22 Nov 2010
 * by Tom Igoe
 * modified 31 March 2014
 * by Protik Banerji
 *
 * This example code is in the public domain.
 *
 * Derivative work from:
 * http://www.arduino.cc/en/Tutorial/LiquidCrystal
 *
 */

// include the library
#include <LiquidCrystal.h>

// all of our LCD pins
int lcdRSPin = 12;
int lcdEPin = 11;
int lcdD4Pin = 2;
int lcdD5Pin = 3;
int lcdD6Pin = 4;
int lcdD7Pin = 5;
int backlightPin=9;

// the pins connected to the Ultrasonic sensor
int echoPin = 7;
int trigPin = 6;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(lcdRSPin, lcdEPin,
                  lcdD4Pin, lcdD5Pin, lcdD6Pin, lcdD7Pin);
                  

// the photocell voltage divider pin
int photocellPin = A0;

//The 10K Digital Potentiometer for LED brightness
int lightpotpin = A5;

//Initialise PWM values

const byte PWMmax=255,PWMmin=0;


void setup()
{
    Serial.begin(9600);
    // set the pinmode for the backlight
    pinMode(backlightPin,OUTPUT);
    
    // set the pinmode on our ultrasonic echo, and tric pins
    pinMode(echoPin, INPUT);
    pinMode(trigPin, OUTPUT);
    
    // set up the LCD's number of columns and rows: 
    lcd.begin(16, 2);

    // Print a message to the LCD.
    lcd.print("hello, world!");
}


void loop()
{   
    float distanceCentimeters;
    int pulseLenMicroseconds;

    // bit-bang a small square wave
    // on the trig pin to start the range
    // finder
    digitalWrite(trigPin, LOW);
    delayMicroseconds(20);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(trigPin, LOW);

    // measure the pulse length from the echo pin
    pulseLenMicroseconds = pulseIn(echoPin, HIGH);

    // calculate the distance using the speed of sound
    distanceCentimeters = pulseLenMicroseconds / 29.387 / 2;
    
    int ambientlight,lightpot;float distance;      
   
    ambientlight = analogRead(photocellPin); // read our photocell
    Serial.print("Photoresistor =");        //Debug ambientlight values
    Serial.println(ambientlight);
    //delay(1000);
        
    lightpot = analogRead(lightpotpin); //Light potentiometer reading
    Serial.print("LightPot =");        //Debug lightpot values
    Serial.println(lightpot);
    //delay(2);
    
    
    distance = distanceCentimeters;  // read our range finder
    Serial.print("Range =");        //Debug distance values
    Serial.println(distance);
    
    int backlight;  
    
    //backlight = map(ambientlight, 1000,1023, PWMmin, PWMmax);    //if it gets darker decrease backlight to compensate using photoresistor
    //backlight = map(lightpot,0,1024,PWMmin,PWMmax);          //if it gets darker deccrease backlight to compensate using POTENTIOMETER
    backlight = map(distance, 4.0,15.0, PWMmin, PWMmax);
    
    analogWrite(backlightPin,backlight);
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0)
    lcd.setCursor(0, 1);

    // print the number of seconds since reset
    lcd.print(backlight);
    Serial.print("Backlight =");        //Debug lightpot values
    Serial.println(distance);
    delay(1);
    
}
