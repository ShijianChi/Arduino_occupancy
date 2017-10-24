
#include <SD.h>         //SD Card Library
#include "kSeries.h"    //K30 meter

//Chip select for SD
int CS_pin = 10;
//K30 to pin6,7
kSeries K_30(6,7);

long id = 1;

void setup() {
  
  Serial.begin(9600);
  Serial.println("Initializing Card");
  //CS Pin is an output
  pinMode(CS_pin, OUTPUT);
  
  //Initialize Card
  if (!SD.begin(CS_pin))
  {
      Serial.println("Card Failure");
      return;
  }
  Serial.println("Card Ready");

   //Write Log File Header
  File logFile = SD.open("CO2.csv", FILE_WRITE);
  if (logFile)
  {
    logFile.println(","); //Just a leading blank line, incase there was previous data
    String header = "ID, CO2 in ppm";
    logFile.println(header);
    logFile.close();
    Serial.println(header);
  }
  else
  {
    Serial.println("Couldn't open log file");
  }

}

void loop() {
  double co2 = K_30.getCO2('p');

  //convert the CO2 to string
  String dataString = String(id) + "," + String(co2);

  //record CO2 data into SD card
  File logFile = SD.open("CO2.csv", FILE_WRITE);
  if (logFile)
  {
    logFile.println(dataString);
    logFile.close();
    Serial.println(dataString);
  }
  else
  {
    Serial.println("Couldn't open log file");
  }

  //increment id
  id++;
  // Wait 1 seconds
  delay(1000);
  
}
