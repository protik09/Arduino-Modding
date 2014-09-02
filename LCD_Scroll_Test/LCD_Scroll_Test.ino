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
  Serial.begin(9600);
  // clear the screen
  lcd.clear();
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
}

void loop()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  LCDWrite1("Lorem ipsum dolor sit amet consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.");
} 

void LCDWrite1(char inString1[200])  // LCD write to top line of display
{
  if (strlen(inString1)>17 && strlen(inString1)<41)
  {
    // Print a message to the LCD.
    lcd.print(inString1);
    Serial.println(strlen(inString1));
    delay(2000);
    // scroll 16 positions (string length) to the left 
    // to move it offscreen left:
    for (int positionCounter = 0; positionCounter < (strlen(inString1)+1); positionCounter++) 
    {
      // scroll one position left:
      lcd.scrollDisplayLeft(); 
      // wait a bit:
      delay(300);
    }

    delay (2000);
  }

  else if(strlen(inString1)>41)
  {
    lcd.print("Line 0 Overflow");
    delay(300);
  }

  else
  {
    lcd.print(inString1);
  }
}
