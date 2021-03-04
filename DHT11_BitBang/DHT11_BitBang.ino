/**
 * @file DHT11_BitBang.ino
 * 
 * @author Protik Banerji (protik09@gmail.com)
 * @brief Bit Bang the DHT11 Protocol with a Teensy 4.0
 * @version 0.1
 * @date 2021-03-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */


void setup()
{
    Serial.begin(115200);
    while (!Serial); // wait for Arduino Serial Monitor
    delay(500);
}

void loop()
{

}
