#include <OneSheeld.h>

#define LEFTLIGHT 7
#define BACKLIGHT 13

boolean pin1State=LOW;
boolean pin2State=LOW;

boolean flag1=LOW;

void setup() 
{
	/* Start communication. */
	OneSheeld.begin();
	/* Set the LED as output. */
	pinMode(LEFTLIGHT,OUTPUT);
	digitalWrite(LEFTLIGHT,LOW);
	pinMode(BACKLIGHT,OUTPUT);
	digitalWrite(BACKLIGHT,LOW);
}

void loop() 
{
	/* Check if the magnetic strength exceeded a certain value. */
	if (MagnetometerSensor.getMagneticStrength() > 70)
	{
		Buzzer.buzzOn();
		if(GravitySensor.getX()>8 && GravitySensor.getY()<4)
		{
			Light1Change();
			delay(1000);
		}

		else if(GravitySensor.getY()>8 && GravitySensor.getZ()<4)
		{
			Light2Change();
			delay(1000);
		}
	}

	else
	{
		Buzzer.buzzOff();
	}

}

void Light1Change()
{
	if (pin1State == LOW)
	{
		pin1State = HIGH;
		digitalWrite(LEFTLIGHT,pin1State);
		delay(5000);
		
	}
	else
	{
		pin1State = LOW;
		digitalWrite(LEFTLIGHT,pin1State);
		delay(5000);
	}
}

void Light2Change()
{
	IRBurst();
	delay(5000);
}

void IRBurst()
{
	digitalWrite(BACKLIGHT,HIGH);
	delay(150);
	digitalWrite(BACKLIGHT,LOW);
	delay(200);
	digitalWrite(BACKLIGHT,HIGH);
	delay(500);
	digitalWrite(BACKLIGHT,LOW);
}


