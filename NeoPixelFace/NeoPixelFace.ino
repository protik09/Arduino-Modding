#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(25, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

int smile[18] = {0, 1, 2, 3, 4, 5, 6, 11, 12, 13, 14, 19, 20, 21, 22, 23, 24};
int frown[18] = {0, 1, 2, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 23, 24};

void setup()
{
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() 
{
  happysmile();
  delay(500);
  sadfrown();
  delay(500);
  calibrationface();
  delay(500);

}

void happysmile() //Activate green smileyface
{
  for (uint16_t i = 0; i < 18; i++)
  {
    strip.setPixelColor(smile[i], strip.Color(0, 255, 0));
    strip.show();
    delay(50);
  }
}

void sadfrown()  //Activate red frowny face
{
  for (uint16_t i = 0; i < 18; i++)
  {
    strip.setPixelColor(frown[i], strip.Color(255, 0, 0));
    strip.show();
    delay(50);
  }
}

void calibrationface() //Cycle through rainbow face while calibrating
{
  uint16_t k, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (k = 0; k < 18; k++)
    {
      strip.setPixelColor(k, Wheel(((k * 256 / 18) + j) & 255));
    }
    strip.show();
    delay(100);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos)
{
  if (WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
