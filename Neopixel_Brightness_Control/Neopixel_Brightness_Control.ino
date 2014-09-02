#include <Adafruit_NeoPixel.h>

#define PIN 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, PIN, NEO_GRB + NEO_KHZ800);

int fadeControl = 255;//will hold the current brightness level
int fadeDirection = -1;//change sigen to fade up or down
int fadeStep = 10;//delay between updates

void setup() 
{
  strip.begin();
  strip.show();
}

void loop() 
{
  strip.setPixelColor(0, 255, 192, 255);//set the pixel colour
  strip.setBrightness(fadeControl);//set the pixel brightness
  strip.show();
  fadeControl = fadeControl + fadeDirection;//increment the brightness value
  if (fadeControl <0 || fadeControl > 255)
  //If the brightness value has gone past its limits...
  {
    fadeDirection = fadeDirection * -1;//change the direction...
    fadeControl = fadeControl + fadeDirection;//...and start back.
  } 
  delay(fadeStep);//wait a bit before doing it again.
}
