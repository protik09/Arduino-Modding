#include <Adafruit_NeoPixel.h>

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(15, PIN, NEO_GRB + NEO_KHZ800);



int fadeStep = 10;//delay between updates
int potPin = A0;

void setup()
{
  //Serial.begin(9600); //Serial Output for Debugging
  randomSeed(analogRead(5));int rand1=random(1,255);
  randomSeed(analogRead(4));int rand2=random(1,255);
  randomSeed(analogRead(3));int rand3=random(1,255);
  randomSeed(analogRead(2));int rand4=random(1,255);
  randomSeed(analogRead(1));int rand5=random(1,255);
  randomSeed(analogRead(3));int rand6=random(1,255);
  
  strip.begin();
  strip.setPixelColor(4, rand1, rand2, rand3);//set the pixel colour
  strip.setPixelColor(3, rand4, rand5, rand6);//set the pixel colour
  strip.show();
  

}

void loop()
{  int analogValue;int fadeControl=255;
  //strip.setBrightness(fadeControl);
  //strip.show();
  // reads the value of the potentiometer (value between 0 and 1023)
  analogValue = analogRead(potPin);
  Serial.print("PotValue = "); Serial.println(analogValue);

  // scale it to use it with the servo (value between 0 and 180)
  fadeControl = map(analogValue, 0, 1023, 1, 255);
  //Serial.print("FadeValue = "); Serial.println(fadeControl);
  strip.setBrightness(fadeControl);//set the pixel brightness
  
  strip.show();
  //delay(fadeStep);//wait a bit before doing it again.
}
