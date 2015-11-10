#ifndef LIS331DLH_H
#define LIS331DLH_H

#include "Arduino.h"

class Daisy7;

/**
 * LIS331DLH 3-axis accelerometer by ST.
 */
class LIS331DLH {
  
public:
  /**
   * Power mode which affects the output data rate.
   * POWER_NORMAL uses data rate settings specified by DataRate.
   * POWER_X settings define data rate in Hz. Then DataRate specifies
   * low-pass filter cut-off frequency.
   */
  enum PowerMode {
    POWER_DOWN = 0,
    POWER_NORMAL = 1,
    POWER_LOW_05 = 2,
    POWER_LOW_1 = 3,
    POWER_LOW_2 = 4,
    POWER_LOW_5 = 5,
    POWER_LOW_10 = 6
    };

  /**
   * Output data rate in Hz for POWER_NORMAL settings of DataRate.
   * 
   * If DataRate is different then setting corresponds to low-pass filter
   * cut-off frequency:
   * - ODR_50_Hz = 37 Hz
   * - ODR_100_Hz = 74 Hz
   * - ODR_400_Hz = 292 Hz
   * - ODR_1000_Hz = 780 Hz
   */
  enum DataRate {
    ODR_50_HZ = 0,
    ODR_100_HZ = 1,
    ODR_400_HZ = 2,
    ODR_1000_HZ = 3  
    };

  /**
   * Hi-pass filter cut-off frequency:
   * HPF_X | ODR_50_HZ |  ODR_100_HZ |  ODR_400_HZ |  ODR_1000_HZ
   *     0 |         1 |           2 |           8 |           20
   *     1 |       0.5 |           1 |           4 |           10
   *     2 |      0.25 |         0.5 |           2 |            5
   *     3 |     0.125 |        0.25 |           1 |          2.5   
   */
  enum HPFCutOff {
    HPF_0 = 0,
    HPF_1 = 1,
    HPF_2 = 2,
    HPF_3 = 3
    };

  void SetDaisy(Daisy7* daisy7) {
    this->daisy7 = daisy7;
    }
    
  void write(byte reg, byte data);

  byte read(byte reg);

  void AllAxesOn();
  
  void SetDataRate(DataRate);

  void SetPowerMode(PowerMode);

  bool available();

  short X();
  
  short Y();

  short Z();

private:
  Daisy7* daisy7;
  const byte address = 0x18;
  
  enum Register {
    WHO_AM_I = 0x0F,
    CTRL_REG1 = 0x20,
    CTRL_REG2 = 0x21,
    CTRL_REG3 = 0x22,
    CTRL_REG4 = 0x23,
    CTRL_REG5 = 0x24,
    HP_FILTER_RESET = 0x25,
    REFERENCE = 0x26,
    STATUS_REG = 0x27,
    OUT_X_L = 0x28,
    OUT_X_H = 0x29,
    OUT_Y_L = 0x2A,
    OUT_Y_H = 0x2B,
    OUT_Z_L = 0x2C,
    OUT_Z_H = 0x2D
    };
};

#endif
