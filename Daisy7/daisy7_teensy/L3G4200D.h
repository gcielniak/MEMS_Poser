#ifndef L3G4200D_H
#define L3G4200D_H

#include "Arduino.h"

enum class L3G4200DRegister {
  WHO_AM_I = 0x0F,
  CTRL_REG1 = 0x20,
  CTRL_REG2 = 0x21,
  CTRL_REG3 = 0x22,
  CTRL_REG4 = 0x23,
  CTRL_REG5 = 0x24,
  REFERENCE = 0x25,
  OUT_TEMP = 0x26,
  STATUS_REG = 0x27,
  OUT_X_L = 0x28,
  OUT_X_H = 0x29,
  OUT_Y_L = 0x2A,
  OUT_Y_H = 0x2B,
  OUT_Z_L = 0x2C,
  OUT_Z_H = 0x2D
  };

class Daisy7;
  
class L3G4200D {
  Daisy7* daisy7;
  const byte address = 0x68;
  
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
