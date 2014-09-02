//TMP36 Pin Variables
int sensorPin = A0; //the analog pin the TMP36's Vout (sense) pin is connected to
                        //the resolution is 10 mV / degree centigrade with a
                        //500 mV offset to allow for negative temperatures
 
/*
 * setup() - this function runs once when you turn your Arduino on
 * We initialize the serial connection with the computer
 */

void setup()
{
  Serial.begin(9600);  //Start the serial connection with the computer
                       //to view the result open the serial monitor
  while (!Serial) ;
  //pinMode(A0, INPUT); 
}
 
void loop()                     // run over and over again
{
 //getting the voltage reading from the temperature sensor
 int reading = analogRead(A0);
 int reading2 = analogRead(A5); 
 
 // converting that reading to voltage, for 3.3v arduino use 3.3
 float voltage = reading * 5.00;
 voltage /= 1024.0; 
 float voltage2 = reading*5.00;
 voltage2/=1024.0;
 
 //Debugging Analog read
 
 Serial.print(reading); Serial.println(" bytes");
 Serial.print(reading2); Serial.println(" bytes");
 
 // print out the voltage
 Serial.print(voltage); Serial.println(" volts");
 Serial.print(voltage2); Serial.println(" volts");
 
 // now print out the temperature
 float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 float temperatureC2 = (voltage2 - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 Serial.print(temperatureC); Serial.println(" degrees C");
 Serial.print(temperatureC2); Serial.println(" degrees C");
 
 // now convert to Fahrenheit
 //float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
 //Serial.print(temperatureF); Serial.println(" degrees F");
 
 delay(5000);                                     //waiting a second
}
