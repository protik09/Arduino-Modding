/* 
 ###########################################################
 Title:       Arduino Oscilloscope
 Purpose:     Use a Nokia 3310 GLCD screen with the arduino
 Created by:  Fileark. see Fileark.com for more info.
 Note:        Please reuse, repurpose, and redistribute this code.
 Note:        This code uses the Adafruit PDC8544 LCD library  
 ###########################################################
 */
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

// pin 2 - Serial clock out (SCLK)
// pin 3 - Serial data out (DIN)
// pin 4 - Data/Command select (D/C)
// pin 5 - LCD chip select (CS)
// pin 6 - LCD reset (RST)
Adafruit_PCD8544 nokia = Adafruit_PCD8544(2, 3, 4, 5, 6);

// a bitmap of a 16x16 fruit icon
static unsigned char __attribute__ ((progmem)) logo16_glcd_bmp[]={
  0x06, 0x0D, 0x29, 0x22, 0x66, 0x24, 0x00, 0x01, 0x87, 0x00, 0x27, 0x6C, 0x20, 0x23, 0x06, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };
#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

int channelAI = A1;      // select the input pin for the Oscilioscope
int scaleYAI = A2;       // select the input pin for the Y (horizontal) potentiometer
int scaleXAI = A3;       // select the input pin for the X (Vertical) potentiometer
int offsetXAI = A4;       // select the input pin for the X (Vertical) potentiometer

int delayVariable = 0;   // define a variable for the Y scale / delay
int xVariable = 0;       // define a variable for the x scale 
int yCtr = 0;            // define a variable for the y counter used to collect y position into array
int posy = 0;            // define a variable for the y position of the dot 
int myArray[85];         // define an array to hold the data coming in 
int offsetX = 0;
int fiveV = 1023;


void setup(void) 
{

  nokia.begin();
  nokia.setContrast(50);

  // show splashscreen
  nokia.display();
  delay(500);
  nokia.clearDisplay();
}

void loop() 
{  
  delayVariable = analogRead(scaleYAI);
  delayVariable = (delayVariable);
  delayVariable = map (delayVariable, 0, 1023, 0, 10);
  xVariable = analogRead(scaleXAI);
  xVariable = map (xVariable, 0, 1023, 0, 100); 
  offsetX = analogRead(offsetXAI);
  offsetX = map(offsetX, 0, 1023, -100, 100);

  for(yCtr = 0; yCtr < 43; yCtr += 1)   // the for loop runs from 0 and < 85, it fills the array with 84 records
  {                                 
    posy = analogRead(channelAI);       // read the value from the sensor:
    posy = map (posy, 0, 1023, 1023, 0); 
    myArray[yCtr] = (posy/xVariable);   // scale the value based on the x scale potentiometer      
    delay (delayVariable);           // scale the y collection of data using the delay from the y potentiometer   
  }

  yCtr == 0;                           // set the counter to zero so we can use it again
  nokia.clearDisplay();                       // clear the LCD screen so we can draw new pixels

  for(yCtr = 0; yCtr < 43; yCtr += 1)  // for loop runs 84 times
  {
    nokia.drawLine((yCtr*2)-2, myArray[yCtr-1]-offsetX, yCtr*2, myArray[yCtr]-offsetX, BLACK); // draw the 84 pixels on the screen

  }
  yCtr == 0;
  
  for(yCtr = 0; yCtr < 85; yCtr += 3){
    nokia.drawPixel(yCtr, (fiveV/xVariable)-offsetX, BLACK); // Draw 5V Line
    nokia.drawPixel(yCtr, (fiveV/xVariable/2)-offsetX, BLACK); // Draw 2,5V Line
    nokia.drawPixel(yCtr, 0-offsetX, BLACK); // Draw 0V Line
  }
  
  nokia.display();                     // show the changes to the buffer
  yCtr == 0;                           // set the counter to zero so we can use it again

} 




