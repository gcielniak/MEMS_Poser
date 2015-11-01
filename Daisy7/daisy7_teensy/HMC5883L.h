#ifndef HMC5883L_H
#define HMC5883L_H

#include "Arduino.h"

class Daisy7;
  
class HMC5883L {

enum Register {
  CONF_REG_A = 0x00,
  CONF_REG_B = 0x01,
  MODE_REG = 0x02,
  OUT_X_H = 0x03,
  OUT_X_L = 0x04,
  OUT_Y_H = 0x05,
  OUT_Y_L = 0x06,
  OUT_Z_H = 0x07,
  OUT_Z_L = 0x08,
  STATUS_REG = 0x09,
  ID_REG_A = 0x0A,
  ID_REG_B = 0x0B,
  ID_REG_C = 0x0C
  };

enum MeasurementMode {
  MEASUREMENT_CONT = 0x00,
  MEASUREMENT_SINGLE = 0x01,
  MEASUREMENT_IDLE = 0x02
  };

  Daisy7* daisy7;
  const byte address = 0x1E;
  
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
