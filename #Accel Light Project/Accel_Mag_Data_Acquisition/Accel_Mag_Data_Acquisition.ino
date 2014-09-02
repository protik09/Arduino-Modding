#include <OneSheeld.h>

void setup() 
{
	OneSheeld.begin();
	Serial.begin(115200);
	Serial1.begin(9600);
	while(!Serial){;}
	Serial.println("Setup Complete");
}

void loop() 
{	
	float MagStr,MagX,MagY,MagZ,GravX,GravY,GravZ;
	MagStr = MagnetometerSensor.getMagneticStrength();
	MagX = MagnetometerSensor.getX();
	MagY = MagnetometerSensor.getY();
	MagZ = MagnetometerSensor.getZ();
	GravX = GravitySensor.getX();
	GravY = GravitySensor.getY();
	GravZ = GravitySensor.getZ();

	Serial.print("Magnetic Strength = "); Serial.println(MagStr);
	Serial.print("Magnetic Field in X Direction = "); Serial.println(MagX);
	Serial.print("Magnetic Field in Y Direction = "); Serial.println(MagY);
	Serial.print("Magnetic Field in Z Direction = "); Serial.println(MagZ);
	Serial.print("Gravitational Force in X Direction = "); Serial.println(GravX);
	Serial.print("Gravitational Force in Y Direction = "); Serial.println(GravY);
	Serial.print("Gravitational Force in Z Direction = "); Serial.println(GravX);
	delay(1000);
}
