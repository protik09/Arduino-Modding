int serInLen = 25;
char serInString[25];
void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop()
{
  Serial.println("#S|T|[]#");
  readSerialString(serInString, 5000);
  Serial1.println(serInString);
  Serial1.println("Serial1");
  delay(1000);
}

//read a string from the serial and store it in an array
//you must supply the array variable - will return if timeOut ms passes before the sting is read so you should
//check the contents of the char array before making any assumptions.
void readSerialString (char *strArray,long timeOut) 
{
   long startTime=millis();
   int i;

   while (!Serial.available()) {
      if (millis()-startTime >= timeOut) {
         return;
      }
   }
   while (Serial.available() && i < serInLen) {
      strArray[i] = Serial.read();
      i++;
   }
}

