#include "daisy7.h"

Daisy7 daisy7;

char gps_line[82];
int gps_slength = 0;

void setup() {

  Serial.begin(115200);
  Serial1.begin(115200);

  while (!Serial) ; //Needed for native USB
  Serial.println("Start!");  
  daisy7.begin();
}

void loop() {

  //Accelerator
  if (daisy7.accelerator.available()) {
    Serial.print("acc: x=");
    Serial.print(daisy7.accelerator.X());
    Serial.print(" y=");
    Serial.print(daisy7.accelerator.Y());
    Serial.print(" z=");
    Serial.println(daisy7.accelerator.Z());
    }

  //Gyroscope
  if (daisy7.gyroscope.available()) {
    Serial.print("gyro: x=");
    Serial.print(daisy7.gyroscope.X());
    Serial.print(" y=");
    Serial.print(daisy7.gyroscope.Y());
    Serial.print(" z=");
    Serial.println(daisy7.gyroscope.Z());
    }

  //Compass
  if (daisy7.compass.available()) {
    Serial.print("compass: x=");
    Serial.print(daisy7.compass.X());
    Serial.print(" y=");
    Serial.print(daisy7.compass.Y());
    Serial.print(" z=");
    Serial.println(daisy7.compass.Z());
    }

  //Barometer
  Serial.print("barometer: temp=");
  Serial.print(daisy7.barometer.Temperature());
  Serial.print(" press=");
  Serial.print(daisy7.barometer.Pressure());  
  Serial.print(" altitude=");
  Serial.println(daisy7.barometer.Altitude());  

  //GPS
  if (Serial1.available()) {
    daisy7.gps.update(Serial1.read());
    
    if (daisy7.gps.available()) {
      char* gps_data = daisy7.gps.GetLine();
      for (byte i = 0; i < daisy7.gps.GetLength(); i++)
        Serial.write(gps_data[i]);
      }
    }
}

