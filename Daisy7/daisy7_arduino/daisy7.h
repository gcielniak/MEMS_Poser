#ifndef daisy7_h
#define daisy7_h

#include <Arduino.h>

class Accelerator;

class Daisy7 {
  public:
  Daisy7();
  void write(byte device, byte reg, byte data);
  byte read(byte device, byte reg);
  Accelerator* accelerator;
};

enum AccRegisters {
  CTRL_REG1 = 0x20,
  OUT_X_L = 0x28,
  OUT_X_H = 0x29,
  OUT_Y_L = 0x2A,
  OUT_Y_H = 0x2B,
  OUT_Z_L = 0x2C,
  OUT_Z_H = 0x2D,
  };

enum AccPower {
  POWER_DOWN = 0,
  POWER_NORMAL = 1,
  POWER_LOW_05 = 2,
  POWER_LOW_1 = 3,
  POWER_LOW_2 = 4,
  POWER_LOW_5 = 5,
  POWER_LOW_10 = 6
  };

enum AccODR {
  ODR_50_HZ = 0,
  ODR_100_HZ = 1,
  ODR_400_HZ = 2,
  ODR_1000_HZ = 3  
  };
  
class Accelerator {
  Daisy7* daisy7;
  const byte address = 0x18;
  
  public:
  Accelerator(Daisy7* daisy7) {
    this->daisy7 = daisy7;
    }

  void write(byte reg, byte data) {
    daisy7->write(address,reg,data);
    }

  byte read(byte reg) {
    return daisy7->read(address,reg);
  }

  void NormalMode() {
    daisy7->write(address, CTRL_REG1, (POWER_NORMAL<<5)|(ODR_50_HZ<<3)|7);
    }

  bool NewData() {
     byte data = daisy7->read(address, 0x27);
     return ((data&0x08) != 0);
    }

  short X() {
    byte low_byte = daisy7->read(address, OUT_X_L);
    byte high_byte = daisy7->read(address, OUT_X_H);
    return (short)((high_byte<<8)|low_byte);    
    }
  
  short Y() {
    byte low_byte = daisy7->read(address, OUT_Y_L);
    byte high_byte = daisy7->read(address, OUT_Y_H);
    return (short)((high_byte<<8)|low_byte);    
    }

  short Z() {
    byte low_byte = daisy7->read(address, OUT_Z_L);
    byte high_byte = daisy7->read(address, OUT_Z_H);
    return (short)((high_byte<<8)|low_byte);    
    }
  };

#endif
