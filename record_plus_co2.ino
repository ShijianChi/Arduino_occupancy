#include "kSeries.h"    //K30 meter
#include <SD.h>         //SD Card Library
#include <SPI.h>
#include <TMRpcm.h>

kSeries K_30(6,7); // Pin 6 as RX to KTX, Pin 7 as TX to KRX

//Chip select for SD
int CS_pin = 4;

long id = 1;

#define SD_ChipSelectPin 4  //using digital pin 4 on arduino nano 328, can use other pins

TMRpcm audio;   // create an object for use in this sketch 

char record[15];
int m =0;

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
  File logFile = SD.open("CO21.csv", FILE_WRITE);
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

  audio.CSPin = SD_ChipSelectPin;

}

void loop() {
  sprintf( record, "%d.wav", m);
  double co2 = K_30.getCO2('p');

  //convert the CO2 to string
  String dataString = String(id) + "," + String(co2);

  //record CO2 data into SD card
  File logFile = SD.open("CO21.csv", FILE_WRITE);
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
  delay(2000);
  audio.startRecording(record,10000,A0);
  delay(2000);
  audio.stopRecording(record);
  delay(2000);
  
  m++;
  
}
