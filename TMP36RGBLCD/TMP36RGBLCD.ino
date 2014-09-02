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

//Initialise global variables
int prevbutton = 1; //The last button pressed
uint8_t buttons; //Initialise buttons on LCD Shield

void setup()
{
  // Debugging output
  Serial.begin(9600);
  //while (!Serial) ;
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  // Print a message to the LCD. We track how long it takes since
  // this library has been optimized a bit and we're proud of it :)
  //int time = millis();
  lcd.print("LEFT IS C");
  lcd.setCursor(0, 1);
  lcd.print("RIGHT IS F");
  //time = millis() - time;
  //Serial.print("Took "); Serial.print(time); Serial.println(" ms");
  lcd.setBacklight(WHITE);
  Serial.println("Setup Successful");
}


void loop()                     // run over and over again
{
  lcd.clear();
  buttons = lcd.readButtons();
  Serial.println(buttons);
  lcd.clear();
  
  while (prevbutton == BUTTON_UP || prevbutton == BUTTON_DOWN || prevbutton == BUTTON_SELECT)
  {
    //lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("LEFT IS C");
    lcd.setCursor(0, 1);
    lcd.print("RIGHT IS F");
    lcd.setBacklight(WHITE);
    prevButton();
  }

  while (prevbutton == BUTTON_LEFT)
  {  
    prevButton(); //speed up button acquisition
    float Centigrade = readTempC();
    lcd.clear();
    //lcd.setCursor(0, 0);
    lcd.print("Centigrade");
    lcd.setCursor(0, 1);
    lcd.print(Centigrade); lcd.print(" C");
    lcd.setBacklight(GREEN);
    prevButton();
    delay(500);
  }

  while (prevbutton == BUTTON_RIGHT)
  {
    prevButton(); //speed up button acquisition
    float Farenheit = readTempF();
    lcd.clear();
    //lcd.setCursor(0, 0);
    lcd.print("Farenheit");
    lcd.setCursor(0, 1);
    lcd.print(Farenheit); lcd.print(" F");
    lcd.setBacklight(RED);
    prevButton();
    delay(500);
  }

  delay(10);      //waiting a few milliseconds

}

float readTempC()
{
  //getting the voltage reading from the temperature sensor
  uint16_t reading = analogRead(A0);

  // converting that reading to voltage, for 3.3v arduino use 3.3
  float voltage = reading * 5.00;
  voltage /= 1024.0;

  // print out the voltage
  //Serial.print(voltage); Serial.println(" volts");

  // now print out the temperature
  float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset to degrees ((voltage - 500mV) times 100)
  Serial.print(temperatureC); Serial.println(" degrees C");
  return temperatureC;

}

float readTempF()
{
  //getting the voltage reading from the temperature sensor
  uint16_t reading = analogRead(A0);

  // converting that reading to voltage, for 3.3v arduino use 3.3
  float voltage = reading * 5.00;
  voltage /= 1024.0;

  // print out the voltage
  //Serial.print(voltage); Serial.println(" volts");

  // now print out the temperature
  float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                                //to degrees ((voltage - 500mV) times 100)
  Serial.print(temperatureC); Serial.println(" degrees C");

  // now convert to Fahrenheit
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  Serial.print(temperatureF); Serial.println(" degrees F");

  return temperatureF;

}

void prevButton()
{
  buttons = lcd.readButtons();
  if (buttons > 0)
  {
    prevbutton = buttons;
  }
  else
  {
    prevbutton = prevbutton;
  }
}
