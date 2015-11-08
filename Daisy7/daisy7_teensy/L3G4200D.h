#ifndef L3G4200D_H
#define L3G4200D_H

#include "Arduino.h"

class Daisy7;

/**
 * L3G4200D three-axes gyroscope IC by ST.
 * 
 * http://www.st.com/web/en/resource/technical/document/datasheet/CD00265057.pdf
 * 
 */
class L3G4200D {

  public:

/**
 * Data rate in Hz.
 */
enum DataRate {
  ODR_100 = 0,
  ODR_200 = 1,
  ODR_400 = 2,
  ODR_800 = 3  
  };

/**
 * Lo-pass cut-off frequency which depends on DataRate setting
 * 
 * Bandwidth | DataRate | Cut-off 
 *      BW_0 |   100 Hz | 12.5 Hz
 *      BW_1 |   100 Hz |   25 Hz
 *      BW_2 |   100 Hz |   25 Hz
 *      BW_3 |   100 Hz |   25 Hz
 *      BW_0 |   200 Hz | 12.5 Hz
 *      BW_1 |   200 Hz |   25 Hz
 *      BW_2 |   200 Hz |   50 Hz
 *      BW_3 |   200 Hz |   70 Hz
 *      BW_0 |   400 Hz |   20 Hz
 *      BW_1 |   400 Hz |   25 Hz
 *      BW_2 |   400 Hz |   50 Hz
 *      BW_3 |   400 Hz |  110 Hz
 *      BW_0 |   800 Hz |   30 Hz
 *      BW_1 |   800 Hz |   35 Hz
 *      BW_2 |   800 Hz |   50 Hz
 *      BW_3 |   800 Hz |  110 Hz
 */
enum Bandwidth {
  BW_0 = 0,
  BW_1 = 1,
  BW_2 = 2,
  BW_3 = 3  
  };

/**
 * Hi-pass filter mode.
 */
enum HPF_Mode {
  HPF_NORMALRESET = 0,
  HPF_REFERENCE = 1,
  HPF_NORMAL = 2,
  HPF_AUTORESET = 3  
  };

/**
 * Hi-pass cut-off frequency which depends on DataRate setting
 * 
 *  HPF | DR=100Hz | DR=200Hz | DR=400Hz | DR=800Hz
 *    0 |        8 |       15 |       30 |       56
 *    1 |        4 |        8 |       15 |       30
 *    2 |        2 |        4 |        8 |       15
 *    3 |        1 |        2 |        4 |        8
 *    4 |      0.5 |        1 |        2 |        4
 *    5 |      0.2 |      0.5 |        1 |        2
 *    6 |      0.1 |      0.2 |      0.5 |        1
 *    7 |     0.05 |      0.1 |      0.2 |      0.5
 *    8 |     0.02 |     0.05 |      0.1 |      0.2
 *    9 |     0.01 |     0.02 |     0.05 |      0.1
 */
enum HPF_Cutoff {
  HPF_0 = 0,
  HPF_1 = 1,
  HPF_2 = 2,
  HPF_3 = 3,
  HPF_4 = 4,
  HPF_5 = 5,
  HPF_6 = 6,
  HPF_7 = 7,
  HPF_8 = 8,
  HPF_9 = 9  
  };

/**
 * Speed in degrees per second.
 */
enum DPS {
  DPS_250 = 0,
  DPS_500 = 1,
  DPS_2000 = 2
  };

  /**
   * Associate the main Daisy7 board.
   */
  void SetDaisy(Daisy7* daisy7) {
    this->daisy7 = daisy7;
    }
    
  /**
   * Write a single byte to device.
   */
  void write(byte reg, byte data);

 /**
  * Read a single byte from device.
  */
  byte read(byte reg);

 /**
  * Switch on all axes.
  */
  void AllAxesOn();

  /**
   * Set bandwidth. 
   */
  void SetBandwidth(Bandwidth);

  /**
   * Set data rate.
   */
  void SetDataRate(DataRate);

  /**
   * Set hi-pass filter mode.
   */
  void SetHMFMode(HPF_Mode);

  /**
   * Set hi-pass fitler cut-off frequency.
   */
  void SetHPFCutoff(HPF_Cutoff);

  /**
   * Set speed.
   */
  void SetDPS(DPS);
  
  /**
   * Check if new data is available.
   */
  bool available();

  /**
   * Get X axis reading.
   */
  short X();
  
  /**
   * Get Y axis reading.
   */
  short Y();

  /**
   * Get Z axis reading.
   */
  short Z();

protected:
  Daisy7* daisy7;
  const byte address = 0x68; //I2C address
  
  /**
   * Register addresses.
   */
  enum Register {
    WHO_AM_I = 0x0F,
    CTRL_REG1 = 0x20,
    CTRL_REG2 = 0x21,
    CTRL_REG3 = 0x22,
    CTRL_REG4 = 0x23,
    CTRL_REG5 = 0x24,
    OUT_TEMP = 0x26,
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
