#ifndef BMP085_H
#define BMP085_H

#include "Arduino.h"

class Daisy7;
  
class BMP085 {
  enum Mode {
      ULTRALOWPOWER = 0,
      STANDARD = 1,
      HIGHRES = 2,
      ULTRAHIGHRES = 3
      };
  
  enum Register {
    CALIB_DATA = 0xAA,
    READTEMPCMD = 0x2E,
    READPRESSURECMD = 0x34,
    TEMPDATA = 0xF6,
    PRESSUREDATA = 0xF6,
    CONTROL = 0xF4  
  };

  enum RegIndex {
    I_AC1 = 0,
    I_AC2 = 1,
    I_AC3 = 2,
    I_AC4 = 3,
    I_AC5 = 4,
    I_AC6 = 5,
    I_B1 = 6,
    I_B2 = 7,
    I_MB = 8,
    I_MC = 9,
    I_MD = 10    
    };

  Daisy7* daisy7;
  const byte address = 0x77;
  Mode mode;
  unsigned short calib_registers[11];

  public:
  void SetDaisy(Daisy7* daisy7) {
    this->daisy7 = daisy7;
    }
    
  void write(byte reg, byte data);

  byte read(byte reg);

  void NormalMode();

  uint16_t TemperatureRaw();

  float Temperature();

  uint32_t PressureRaw();
  
  int32_t Pressure();

  protected:
  int32_t B5(uint32_t UT);  
};

#endif
