#include <Streaming.h>

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	int A0_1 = analogRead(A0);
	int A0_2 = analogRead(A0);
	Serial<< A0_1 <<" "<< A0_2 << endl;
	delay(100);
}