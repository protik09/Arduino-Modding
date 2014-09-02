// include the library code:
#include <Wire.h>
#include <Adafruit_MCP23017.h>
#include <Adafruit_RGBLCDShield.h>

// The shield uses the I2C SCL and SDA pins. On classic Arduinos
// this is Analog 4 and 5 so you can't use those for analogRead() anymore
// However, you can connect other I2C sensors to the I2C bus and share
// the I2C bus.
Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

// These #defines make it easy to set the backlight color
#define RED 0x1
#define YELLOW 0x3
#define GREEN 0x2
#define TEAL 0x6
#define BLUE 0x4
#define VIOLET 0x5
#define WHITE 0x7

void setup() 
{
  // clear the screen
  lcd.clear();
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
}

void loop() {
 // Print a message to the LCD.
 lcd.print("www.tehnic.go.ro");
 delay(2000);
  // scroll 16 positions (string length) to the left 
  // to move it offscreen left:
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) 
  {
    // scroll one position left:
    lcd.scrollDisplayLeft(); 
    // wait a bit:
    delay(300);
  }
  delay (2000);
  // scroll 16 positions (string length + display length) to the right
  // to move it offscreen right:
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) 
  {
    // scroll one position right:
    lcd.scrollDisplayRight(); 
    // wait a bit:
    delay(300);
  }
  
  delay (2000);
  // scroll 34 positions (string length + display length) to the right
  // to move it offscreen right:
  for (int positionCounter = 17; positionCounter < 34; positionCounter++) 
  {
    // scroll one position right:
    lcd.scrollDisplayRight(); 
    // wait a bit:
    delay(300);  
  }
  delay (2000);  
    // scroll 17 positions (display length + string length) to the left
    // to move it back to center:
    for (int positionCounter = 0; positionCounter < 17; positionCounter++) 
    {
    // scroll one position left:
    lcd.scrollDisplayLeft(); 
    // wait a bit:
    delay(300);
  }
  delay (1000);
  lcd.setCursor(0, 1);
  lcd.print("   by niq_ro"); 
  // delay at the end of the full loop:
  delay(4000);
 // clear the screen
 lcd.clear();
}