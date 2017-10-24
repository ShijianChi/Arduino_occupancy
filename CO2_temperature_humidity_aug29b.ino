#include "kSeries.h"    //K30 meter
#include <SD.h>         //SD Card Library
#include "Adafruit_Si7021.h"

kSeries K_30(6,7); // Pin 6 as RX to KTX, Pin 7 as TX to KRX
Adafruit_Si7021 sensor = Adafruit_Si7021();
//Chip select for SD
int CS_pin = 10;

long id = 1;

void setup() {
  
  Serial.begin(9600);
  sensor.begin();
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
  File logFile = SD.open("data_8.csv", FILE_WRITE);
  if (logFile)
  {
    logFile.println(", , ,"); //Just a leading blank line, incase there was previous data
    String header = "ID, humidity, temperature, CO2";
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
  double t = millis();
  double CO2 = K_30.getCO2('p');
  double humidity = sensor.readHumidity();
  double temp = sensor.readTemperature();
  
  String dataString = String(id) + "," + String(humidity) + "," + String(temp) + "," + String(CO2);

  //record all data into SD card
  File logFile = SD.open("data_8.csv", FILE_WRITE);
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
  t = millis()-t;
  Serial.println(t);
}
