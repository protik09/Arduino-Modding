#define IRLED 3

void setup()
{
  digitalWrite(IRLED, LOW);
  Serial.begin(9600);
  Serial.println("Ready to generate Signal");
}

void loop()
{
  long time1=millis();
  int ApplePlaySignal[] = {
    // ON, OFF (in 10's of microseconds)
    912, 438,
    68, 48,
    68, 158,
    68, 158,
    68, 158,
    68, 48,
    68, 158,
    68, 158,
    68, 158,
    70, 156,
    70, 158,
    68, 158,
    68, 48,
    68, 46,
    70, 46,
    68, 46,
    68, 160,
    68, 158,
    70, 46,
    68, 158,
    68, 46,
    70, 46,
    68, 48,
    68, 46,
    68, 48,
    66, 48,
    68, 48,
    66, 160,
    66, 50,
    66, 160,
    66, 50,
    64, 160,
    66, 50,
    66, 3950,
    908, 214,
    66, 3012,
    908, 212,
    68, 0
  };
  digitalWrite(13, HIGH);
  for (int i = 0; i < 76; i++)
  {
    digitalWrite(IRLED, HIGH);
    delayMicroseconds(ApplePlaySignal[i]);
    i = i + 1;
    digitalWrite(IRLED, LOW);
    delayMicroseconds(ApplePlaySignal[i]);
  }
  int time;
  time = millis()-time1;
  digitalWrite(13, LOW);
  Serial.print("Time to complete run: ");Serial.println(time);
  delay(3000);
}

