#ifndef DAISY7_H
#define DAISY7_H

#include "Arduino.h"
#include "i2c_t3.h"
#include "Accelerator.h"

class Daisy7 {
public:
  Accelerator accelerator;

  Daisy7() {
    accelerator.SetDaisy(this);
    }

 void begin() {
    Wire.begin(I2C_MASTER, 0x00, I2C_PINS_16_17, I2C_PULLUP_EXT, I2C_RATE_400);
    accelerator.NormalMode();
  }

  void write(byte address, byte reg, byte data) {
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.write(data);
    Wire.endTransmission();
    }

  byte read(byte address, byte reg) {
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.endTransmission(I2C_NOSTOP);
    Wire.requestFrom(address, (size_t) 1);
    return Wire.read();
    }

  void read(byte address, byte reg, byte *dest, int count) {
    Wire.beginTransmission(address);
    Wire.write(reg);
    Wire.endTransmission(I2C_NOSTOP);
    Wire.requestFrom(address, (size_t) count);
    for (int i = 0; i < count; i++)
      dest[i++] = Wire.read();
    }
};

#endif
