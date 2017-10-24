/****************************************
  Example Sound Level Sketch for the
  Adafruit Microphone Amplifier
****************************************/
#include <SD.h>

int CS_pin = 10;

unsigned int sample;
//long id = 1;

void setup()
{
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


void loop()
{
  unsigned long time = micros();
  sample = analogRead(0);
  double volts = (sample * 5.0) / 1024;  // convert to volts
  
  String dataString = String(volts);

  File logFile = SD.open("Sound.csv", FILE_WRITE);
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
  //id++;
  time = micros() - time;
  //Serial.println(volts);
  //Serial.println(sample);
  Serial.println(time);
  //delay(1000);
}
