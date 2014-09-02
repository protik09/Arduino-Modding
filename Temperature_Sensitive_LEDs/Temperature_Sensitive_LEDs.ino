/*
 * Tutorial 1: Reading Temperature
 * 
 * Read the temperature in celcius over serial.
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

// the output pin of the LM35 temperature sensor
int lm35Pin = A0;
// an array of pin numbers to which LEDs are attached
// to add more LEDs just list them here in this array
int ledPins[] = {2,7,9,12};

void setup()
{
    // set up serial at 9600 baud   
    Serial.begin(9600);
    
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

    // read our temperature sensor
    analogValue = analogRead(lm35Pin);

    // convert the 10bit analog value to celcius
    temperature = float(analogValue) / 1023;
    temperature = temperature * 500;

    // print the temperature over serial
    Serial.print("Temp: ");
    Serial.print(temperature);
    Serial.println("C");
    
    //Read Temp and turn on corresponding LED
    
    if(temperature>18.0)
    {
      digitalWrite(2,HIGH);
      digitalWrite(7,LOW);
      digitalWrite(9,LOW);
      digitalWrite(12,LOW);
    }
    
    else if(temperature<=18&&temperature>14)
    {
      digitalWrite(7,HIGH);
      digitalWrite(2,LOW);
      digitalWrite(9,LOW);
      digitalWrite(12,LOW);
    }
    
    else if(temperature<=14&&temperature>10)
    {
      digitalWrite(9,HIGH);
      digitalWrite(7,LOW);
      digitalWrite(2,LOW);
      digitalWrite(12,LOW);
    }
    
    else if(temperature<10)
    {
      digitalWrite(12,HIGH);
      digitalWrite(2,LOW);
      digitalWrite(7,LOW);
      digitalWrite(9,LOW);
    }
    
    // wait 1s before reading the temperature again
    delay(1000);
}

