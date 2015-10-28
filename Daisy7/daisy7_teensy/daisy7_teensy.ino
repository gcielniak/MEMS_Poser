#include "daisy7.h"

Daisy7 daisy7;

void setup() {

  daisy7.begin();
  Serial.begin(115200);
  Serial1.begin(115200);

  while (!Serial) ; //Needed for native USB
  Serial.println("Start!");  
}

void loop() {
  if (daisy7.accelerator.available()) {
    Serial.print("acc: x=");
    Serial.print(daisy7.accelerator.X());
    Serial.print(" y=");
    Serial.print(daisy7.accelerator.Y());
    Serial.print(" z=");
    Serial.println(daisy7.accelerator.Z());
    }

  if (daisy7.gyroscope.available()) {
    Serial.print("gyro: x=");
    Serial.print(daisy7.gyroscope.X());
    Serial.print(" y=");
    Serial.print(daisy7.gyroscope.Y());
    Serial.print(" z=");
    Serial.println(daisy7.gyroscope.Z());
    }

  if (Serial1.available()) {
    Serial.write(Serial1.read());
    }
  if (Serial.available()) {
    Serial1.write(Serial.read());
    }
}

