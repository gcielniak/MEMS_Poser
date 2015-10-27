#ifndef ACCELERATOR_H
#define ACCELERATOR_H

#include "Arduino.h"

enum AccRegisters {
  CTRL_REG1 = 0x20,
  STATUS_REG = 0x27,
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

class Daisy7;
  
class Accelerator {
  Daisy7* daisy7;
  const byte address = 0x18;
  
  public:
  void SetDaisy(Daisy7* daisy7) {
    this->daisy7 = daisy7;
    }
    
  void write(byte reg, byte data);

  byte read(byte reg);

  void NormalMode();

  bool available();

  short X();
  
  short Y();

  short Z();
};

#endif
