// Initialise and define global variables and pins
#define echoPin 7
#define trigPin 5

bool flag = 0;
bool BlueoothIncomingByte;
byte SmallLightPin = 6;

void setup()
{
	Serial.begin(9600);
	while (!Serial)
	{
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  pinMode(SmallLightPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  digitalWrite(SmallLightPin, LOW);
}

void loop()
{
	// send data only when you receive data:
	if (Serial.available() > 0) 
	{
		BlueoothIncomingByte = Serial.parseInt();
    Serial.print("Command Received = "); Serial.println(BlueoothIncomingByte); // read the incoming byte
    flag = BlueoothIncomingByte;
    Serial.println("Bluetooth Data Received");
  }

  UltraSonicSensor();
  LightSwitch();
}

void LightSwitch()
{
	if(flag==0)
	{
		digitalWrite(SmallLightPin, HIGH);
	} 
	else 
	{
		digitalWrite(SmallLightPin, LOW);
	}
}

void UltraSonicSensor()
{
	float distanceCentimeters;
	int pulseLenMicroseconds;

	// bit-bang a small square wave on the trig pin to start the range finder
	digitalWrite(trigPin, LOW);
	delayMicroseconds(20);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(100);
	digitalWrite(trigPin, LOW);

  // measure the pulse length from the echo pin
  pulseLenMicroseconds = pulseIn(echoPin, HIGH);

  // calculate the distance using the speed of sound
  distanceCentimeters = pulseLenMicroseconds / 29.387 / 2;

  // print it out over serial
  //Serial.println(distanceCentimeters);

  if(distanceCentimeters<50.0 && distanceCentimeters>0.0)  // Throw an object near the lamp to tuen it on or off
  {
  	if(flag == 0)
  	{
  		flag = 1; 	// If light is on, turn it off
  		delay(1000);
  	}
  	else
  	{
  		flag = 0;		// If light is off, turn it on
  		delay(100);
  	}
  }

  delay(100);
}