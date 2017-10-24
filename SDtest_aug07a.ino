#include <SD.h>

int CS_pin=10;
//int pow_pin=8;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Initializing Card");

  pinMode(CS_pin, OUTPUT);

  if (!SD.begin(CS_pin))
  {
      Serial.println("Card Failure");
      return;
  }
  Serial.println("Card Ready");

}

void loop() {
  // put your main code here, to run repeatedly:
  String dataString = "2333";

  //open file
  File dataFile = SD.open("test2333.txt", FILE_WRITE);
  if (dataFile)
  {
    dataFile.println(dataString);
    dataFile.close();
    Serial.println(dataString);
  }
  else
  {
    Serial.println("Couldn't open log file");
  }
  delay(5000);
}
