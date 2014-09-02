//#include <Stepper.h>

// include the library
#include <LiquidCrystal.h>

// all of our LCD pins
int lcdRSPin = 6;
int lcdEPin = 7;
int lcdD4Pin = 8;
int lcdD5Pin = 9;
int lcdD6Pin = 10;
int lcdD7Pin = 11;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(lcdRSPin, lcdEPin,lcdD4Pin, lcdD5Pin, lcdD6Pin, lcdD7Pin);
// the piezo is connected to analog pin 0
const int knockSensor = A0;

// Pin definitions
                                    // Piezo sensor on pin 0.
const int programSwitch = 2;       // If this is high we program a new code.
//const int lockMotor = 3;           // Gear motor used to turn the lock.
const int redLED = 4;              // Status LED
const int greenLED = 5;            // Status LED

// Tuning constants.  Could be made vars and hoooked to potentiometers for soft configuration, etc.
const int threshold = 3;           // Minimum signal from the piezo to register as a knock
const int rejectValue = 25;        // If an individual knock is off by this percentage of a knock we don't unlock..
const int averageRejectValue = 15; // If the average timing of the knocks is off by this percent we don't unlock.
const int knockFadeTime = 150;     // milliseconds we allow a knock to fade before we listen for another one. (Debounce timer.)
//const int lockTurnTime = 650;      // milliseconds that we run the motor to get it to go a half turn.

const int maximumKnocks = 20;       // Maximum number of knocks to listen for.
const int knockComplete = 1200;     // Longest time to wait for a knock before we assume that it's finished.

//Initialise Stepper Motor
//int stepIN1Pin = 8;
//int stepIN2Pin = 9;
//int stepIN3Pin = 10;
//int stepIN4Pin = 11;

//int stepsPerRevolution = 2048;

//Stepper myStepper(stepsPerRevolution,stepIN1Pin, stepIN3Pin,stepIN2Pin, stepIN4Pin);

// Variables.
int secretCode[maximumKnocks] = {50, 25, 25, 50, 100, 50, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  // Initial setup: "Shave and a Hair Cut, two bits."
int knockReadings[maximumKnocks];   // When someone knocks this array fills with delays between knocks.
int knockSensorValue = 0;           // Last reading of the knock sensor.
int programButtonPressed = false;   // Flag so we remember the programming button setting at the end of the cycle.

void setup()
{    
    // set up the LCD's number of columns and rows: 
    lcd.begin(16, 2);

    // Print a message to the LCD.
    lcd.print("hello, world!");
    
    // set the RPM
    //myStepper.setSpeed(6);
    
    // use the serial port
    Serial.begin(9600);
    Serial.println("Program start.");  			
    // but feel free to comment them out after it's working right.
    
    // set up our LED
    pinMode(redLED, OUTPUT);
    pinMode(greenLED, OUTPUT);
    pinMode(programSwitch, INPUT);
}

void loop()
{
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0)
    //lcd.setCursor(0, 1);

    // print the number of seconds since reset
    //lcd.print(millis() / 1000);  
  
    // read the sensor and store it in the variable sensorReading:
    knockSensorValue = analogRead(knockSensor);

    //attach program buttom pressed to switch digital input2
    programButtonPressed = digitalRead(programSwitch);
    
    // if the sensor reading is greater than the threshold:
    if (knockSensorValue >= threshold)
    {    
        listenToSecretKnock();
        // send the string "Knock!" back to the computer, followed by newline
        Serial.println("Knock!");

        // turn on our LED
        digitalWrite(redLED, HIGH);
        // we have to wait before turning it off so you can see it light up
        delay(50);
        digitalWrite(redLED, LOW);
        
        // delay to avoid overloading the serial port buffer
    delay(100);  
  
    }
    
}

void listenToSecretKnock()
{
  Serial.println("knock starting");   

  int i = 0;
  // First lets reset the listening array.
  for (i=0;i<maximumKnocks;i++){
    knockReadings[i]=0;
  }
  
  int currentKnockNumber=0;         			// Incrementer for the array.
  int startTime=millis();           			// Reference for when this knock started.
  int now=millis();
  
  digitalWrite(greenLED, LOW);      			// we blink the LED for a bit as a visual indicator of the knock.
  if (programButtonPressed==true){
     digitalWrite(redLED, LOW);                         // and the red one too if we're programming a new knock.
  }
  delay(knockFadeTime);                       	        // wait for this peak to fade before we listen to the next one.
  digitalWrite(greenLED, HIGH);  
  if (programButtonPressed==true){
     digitalWrite(redLED, HIGH);                        
  }
  do {
    //listen for the next knock or wait for it to timeout. 
    knockSensorValue = analogRead(knockSensor);
    if (knockSensorValue >=threshold){                   //got another knock...
      //record the delay time.
      Serial.println("knock.");
      now=millis();
      knockReadings[currentKnockNumber] = now-startTime;
      currentKnockNumber ++;                             //increment the counter
      startTime=now;          
      // and reset our timer for the next knock
      digitalWrite(greenLED, LOW);  
      if (programButtonPressed==true){
        digitalWrite(redLED, LOW);                       // and the red one too if we're programming a new knock.
      }
      delay(knockFadeTime);                              // again, a little delay to let the knock decay.
      digitalWrite(greenLED, HIGH);
      if (programButtonPressed==true){
        digitalWrite(redLED, HIGH);                         
      }
    }

    now=millis();
    
    //did we timeout or run out of knocks?
  } while ((now-startTime < knockComplete) && (currentKnockNumber < maximumKnocks));
  
  //we've got our knock recorded, lets see if it's valid
  if (programButtonPressed==false){             // only if we're not in progrmaing mode.
    if (validateKnock() == true){
      triggerDoorUnlock(); 
    } else {
      Serial.println("Secret knock failed.");
      digitalWrite(greenLED, LOW);  		// We didn't unlock, so blink the red LED as visual feedback.
      for (i=0;i<4;i++){					
        digitalWrite(redLED, HIGH);
        delay(100);
        digitalWrite(redLED, LOW);
        delay(100);
      }
      digitalWrite(greenLED, HIGH);
    }
  } else { // if we're in programming mode we still validate the lock, we just don't do anything with the lock
    validateKnock();
    // and we blink the green and red alternately to show that program is complete.
    Serial.println("New lock stored.");
    digitalWrite(redLED, LOW);
    digitalWrite(greenLED, HIGH);
    for (i=0;i<3;i++){
      delay(100);
      digitalWrite(redLED, HIGH);
      digitalWrite(greenLED, LOW);
      delay(100);
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, HIGH);      
    }
  }
}


// Runs the motor (or whatever) to unlock the door.
void triggerDoorUnlock()
{
  Serial.println("Door unlocked!");
  
  //stepper();
  
  }
  
//void stepper()
//{  
  // step one revolution in one direction
    //myStepper.step(stepsPerRevolution*2);
    
    // step one revolution in the other direction
    //myStepper.step(-stepsPerRevolution*2);
    // wait a second
  
//}  

// Sees if our knock matches the secret.
// returns true if it's a good knock, false if it's not.
// todo: break it into smaller functions for readability.
boolean validateKnock()
{
  int i=0;
 
  // simplest check first: Did we get the right number of knocks?
  int currentKnockCount = 0;
  int secretKnockCount = 0;
  int maxKnockInterval = 0;          			// We use this later to normalize the times.
  
  for (i=0;i<maximumKnocks;i++)
  {
    if (knockReadings[i] > 0)
    {
      currentKnockCount++;
    }
    if (secretCode[i] > 0)
    {  					//todo: precalculate this.
      secretKnockCount++;
    }
    
    if (knockReadings[i] > maxKnockInterval)
    { 	// collect normalization data while we're looping.
      maxKnockInterval = knockReadings[i];
    }
  }
  
  // If we're recording a new knock, save the info and get out of here.
  if (programButtonPressed==true)
  {
      for (i=0;i<maximumKnocks;i++)
      { // normalize the times
        secretCode[i]= map(knockReadings[i],0, maxKnockInterval, 0, 100); 
      }
      // And flash the lights in the recorded pattern to let us know it's been programmed.
      digitalWrite(greenLED, LOW);
      digitalWrite(redLED, LOW);
      delay(1000);
      digitalWrite(greenLED, HIGH);
      digitalWrite(redLED, HIGH);
      delay(50);
      for (i = 0; i < maximumKnocks ; i++)
      {
        digitalWrite(greenLED, LOW);
        digitalWrite(redLED, LOW);  
        // only turn it on if there's a delay
        if (secretCode[i] > 0)
        {                                   
          delay( map(secretCode[i],0, 100, 0, maxKnockInterval)); // Expand the time back out to what it was.  Roughly. 
          digitalWrite(greenLED, HIGH);
          digitalWrite(redLED, HIGH);
        }
        delay(50);
      }
	  return false; 	// We don't unlock the door when we are recording a new knock.
  }
  
  if (currentKnockCount != secretKnockCount)
  {
    return false; 
  }
  
  /*  Now we compare the relative intervals of our knocks, not the absolute time between them.
      (ie: if you do the same pattern slow or fast it should still open the door.)
      This makes it less picky, which while making it less secure can also make it
      less of a pain to use if you're tempo is a little slow or fast. 
  */
  int totaltimeDifferences=0;
  int timeDiff=0;
  for (i=0;i<maximumKnocks;i++)
  { // Normalize the times
    knockReadings[i]= map(knockReadings[i],0, maxKnockInterval, 0, 100);      
    timeDiff = abs(knockReadings[i]-secretCode[i]);
    if (timeDiff > rejectValue)
    { // Individual value too far out of whack
      return false;
    }
    totaltimeDifferences += timeDiff;
  }
  // It can also fail if the whole thing is too inaccurate.
  if (totaltimeDifferences/secretKnockCount>averageRejectValue){
    return false; 
  }
  
  return true;
  
}
