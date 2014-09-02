const int sampleWindow = 1000; // Sample window width in mS (50 mS = 20Hz)
unsigned int sample;
boolean pinState;

void setup() 
{
   Serial.begin(9600);
   pinMode(4,OUTPUT);
   pinState = LOW;
   digitalWrite(4, pinState );
}


void loop()
{
   unsigned long startMillis= millis();  // Start of sample window
   unsigned int peakToPeak = 0;   // peak-to-peak level

   unsigned int signalMax = 0;
   unsigned int signalMin = 1024;

   // collect data for 50 mS
   while (millis() - startMillis < sampleWindow)
   {
      sample = analogRead(0);
      if (sample < 1024)  // toss out spurious readings
      {
         if (sample > signalMax)
         {
            signalMax = sample;  // save just the max levels
         }
         else if (sample < signalMin)
         {
            signalMin = sample;  // save just the min levels
         }
      }
   }
   peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
   double volts = (peakToPeak * 5) / 1024;  // convert to volts

   if(volts>=2)
   {
   	LightChange();
   	digitalWrite(4, pinState);
   	delay(2000);
   }

  //Serial.println(volts);
}

void LightChange()
{
	if (pinState == LOW)
	{
		pinState = HIGH;
		
	}
	else
	{
		pinState = LOW;
	}
}
