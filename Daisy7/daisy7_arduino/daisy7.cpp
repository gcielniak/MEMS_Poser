#include <Arduino.h>
#include "daisy7.h"
#include <Wire.h>

Daisy7::Daisy7() {
   Wire.begin();
   accelerator = new Accelerator(this);
}

void Daisy7::write(byte device, byte reg, byte data) {
 Wire.beginTransmission(device);
 Wire.write(reg);
 Wire.write(data);
 Wire.endTransmission();
}

byte Daisy7::read(byte device, byte reg) {
 Wire.beginTransmission(device);
 Wire.write(reg);
 Wire.endTransmission();
 Wire.requestFrom(device, (byte)1);
 return Wire.read();
}  
