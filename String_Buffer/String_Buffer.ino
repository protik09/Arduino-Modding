// Buffer to store incoming commands from serial port
String inData;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("Serial connection started, waiting for instructions...");
}

void loop() {
  while (Serial1.available() > 0)
  {
    char recieved = Serial1.read();
    inData += recieved; 

        // Process message when new line character is recieved
        if (recieved == '#')
        {
          Serial.print("Arduino Received: ");
          Serial.println(inData);

            // You can put some if and else here to process the message juste like that:

            if(inData == "+++#"){ // DON'T forget to add "\n" at the end of the string.
            Serial.println("OK. Press h for help.");
          }   


            inData = ""; // Clear recieved buffer
          }
        }
      }
