#ifndef HMC5883L_H
#define HMC5883L_H

#include "Arduino.h"

class Daisy7;
  
class HMC5883L {
  public:
enum OperatingMode {
  MEASUREMENT_CONT = 0,
  MEASUREMENT_SINGLE = 1, //default
  MEASUREMENT_IDLE = 2
  };

enum MeasurementMode {
  NO_BIAS = 0,
  POS_BIAS = 1,
  NEG_BIAS = 2
  };

enum SampleMode {
  SAMPLE_1 = 0,
  SAMPLE_2 = 1,
  SAMPLE_4 = 2,
  SAMPLE_8 = 3 //default
  };

enum DataRate {
  DR_0_75 = 0,
  DR_1_5 = 1,
  DR_3 = 2,
  DR_7_5 = 3,
  DR_15 = 4,//default
  DR_30 = 5,
  DR_75 = 6  
  };

/**
 * Gain range in Ga. Output values vary between 0xF800-0x07FF (-2048-2047)
 */
enum Gain {
  GA_0_88 = 0,
  GA_1_3 = 1, //default
  GA_1_9 = 2,
  GA_2_5 = 3,
  GA_4_0 = 4,
  GA_4_7 = 5,
  GA_5_6 = 6,
  GA_8_1 = 7  
  };

  void SetDaisy(Daisy7* daisy7) {
    this->daisy7 = daisy7;
    }
    
  void write(byte reg, byte data);

  byte read(byte reg);

  void SetSampleMode(SampleMode);

  void SetDataRate(DataRate);

  void SetOperatingMode(OperatingMode);

  void SetGain(Gain);

  void SetMeasurementMode(MeasurementMode);

  bool available();

  short XRaw();
  
  short YRaw();

  short ZRaw();

  float X();
  
  float Y();

  float Z();

  void SelfTest();
  
protected:

  Daisy7* daisy7;
  const byte address = 0x1E;
  const int gain_ratio[8] = {1370, 1090, 820, 660, 440, 390, 330, 230};
  byte conf_reg_a = 0b01110000;
  byte gain = GA_1_3;
  
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

  
};

#endif
