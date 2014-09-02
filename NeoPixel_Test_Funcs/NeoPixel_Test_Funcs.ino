#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

int fadeControl = 255;//will hold the current brightness level
int fadeDirection = -1;//change sigen to fade up or down
int fadeStep = 10;//delay between updates

void setup()
{ //Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop()
{
  colorWipe(strip.Color(0, 255, 0), 50); // Green
  //strip.show();
  //delay(1000);


}

void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++)
  {
    rainbowCycle(200);
    strip.setBrightness(20);//set the pixel brightness
    strip.show();
    fadeControl = fadeControl + fadeDirection;//increment the brightness value
    if (fadeControl < 0 || fadeControl > 255)
      //If the brightness value has gone past its limits...
    {
      fadeDirection = fadeDirection * -1;//change the direction...
      fadeControl = fadeControl + fadeDirection;//...and start back.
    }
    delay(fadeStep);//wait a bit before doing it again.
    //strip.setPixelColor(i, c);
    //strip.setPixelColor(4, strip.Color(86, 125, 175));
    //strip.show();

  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
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

void Fadecolors(uint8_t wait)
{
  uint16_t r = 0;
  uint16_t g = 0;
  uint16_t b = 0;
  for (uint16_t i = 0; i < strip.numPixels(); i++)
  {
    strip.setPixelColor(i, r, g, b);//set the pixel colour
    delay(wait);
    for (r = 0; r < 255; r++)
    {
      break;
    }
  }
}

void rainbowCycle(uint8_t wait)
{
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}
