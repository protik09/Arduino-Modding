//TMP36 Pin Variables
int sensorPin = A5; //the analog pin the TMP36's Vout (sense) pin is connected to
                        //the resolution is 10 mV / degree centigrade with a
                        //500 mV offset to allow for negative temperatures
 
/*
 * setup() - this function runs once when you turn your Arduino on
 * We initialize the serial connection with the computer
 */
 
 #include <LiquidCrystal.h>

// all of our LCD pins
int lcdRSPin = 12;
int lcdEPin = 11;
int lcdD4Pin = 5;
int lcdD5Pin = 4;
int lcdD6Pin = 3;
int lcdD7Pin = 2;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(lcdRSPin, lcdEPin,
                  lcdD4Pin, lcdD5Pin, lcdD6Pin, lcdD7Pin);

void setup()
{
  Serial.begin(9600);  //Start the serial connection with the computer
                       //to view the result open the serial monitor
  while (!Serial) ;
  //pinMode(A0, INPUT); 
  // set up the LCD's number of columns and rows: 
    lcd.begin(16, 2);

    // Print a message to the LCD.
    //lcd.print("hello, world!");
}
 
void loop()                     // run over and over again
{
 //getting the voltage reading from the temperature sensor
 int reading = analogRead(A5);  
 
 // converting that reading to voltage, for 3.3v arduino use 3.3
 float voltage = reading * 5.00;
 voltage /= 1024.0; 
 
 // print out the voltage
 Serial.print(voltage); Serial.println(" volts");
 
 // now print out the temperature
 float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 Serial.print(temperatureC); Serial.println(" degrees C");
 
 // now convert to Fahrenheit
 float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
 Serial.print(temperatureF); Serial.println(" degrees F");
 
 // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0)
    lcd.setCursor(0, 1);

    // print the number of seconds since reset
    lcd.print(temperatureC);
 
 delay(1000);                                     //waiting a second
}
