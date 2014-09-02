int LEDPin = 3;
 
void setup() 
{ 
  pinMode(LEDPin, OUTPUT);
  Serial.begin(9600);
  while (! Serial);
  Serial.println("Speed 0 to 255");
} 
 
 
void loop() 
{ 
  if (Serial.available())
  {
    int brightness = Serial.parseInt();
    if (brightness >= 0 && brightness <= 255)
    {
      analogWrite(LEDPin, brightness);
    }
  }
} 
