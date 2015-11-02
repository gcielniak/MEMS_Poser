#ifndef BMP085_H
#define BMP085_H

#include "Arduino.h"

class Daisy7;

/**
 * A BMP085 barometer IC by Bosch Sensortec. 
 * Datasheet available at https://www.sparkfun.com/datasheets/Components/General/BST-BMP085-DS000-05.pdf.
 * 
 * References:
 *  - Daisy 7 adlib library: https://github.com/tanzilli/ablib
 *  - Adafruit's board: https://github.com/adafruit/Adafruit-BMP085-Library
 *  - Bosch's source code: https://code.google.com/p/halcyon/source/browse/trunk/firmware/bmp085.h?r=6
 */
class BMP085 {
  public:
  /**
   * Operational mode.
   */
  enum OversamplingSetting {
      ULTRALOWPOWER = 0,
      STANDARD = 1,
      HIGHRES = 2,
      ULTRAHIGHRES = 3
      };

  /**
   * Register address.
   */
  enum Register {
    CALIB_REG = 0xAA,
    READTEMPCMD = 0x2E,
    READPRESSURECMD = 0x34,
    TEMPDATA = 0xF6,
    PRESSUREDATA = 0xF6,
    CONTROL = 0xF4  
  };

  /**
   * Indicies for different calibration registers.
   */
  enum RegisterIndex {
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

  /**
   * Associate the main Daisy7 board.
   */
  void SetDaisy(Daisy7* daisy7) {
    this->daisy7 = daisy7;
    }

  /**
   * Set operational mode and initialise the calibration registers.
   */
  void Mode(OversamplingSetting mode);

  /**
   * Write a single byte to device.
   */
  void write(byte reg, byte data);

 /**
  * Read a single byte from device.
  */
  byte read(byte reg);

  /**
   * Get raw temperature reading.
   */
  uint16_t TemperatureRaw();

  /**
   * Get actual temperature reading in steps of 0.1 deg Celsius.
   */
  int32_t Temperature();

  /**
   * Get raw pressure reading.
   */
  uint32_t PressureRaw();
  
  /**
   * Get actual pressure reading in steps of 1.0 Pa.
   */
  int32_t Pressure();

  /**
   * Get altitude in meters.
   */
  float Altitude();
  
  protected:
  Daisy7* daisy7;
  const byte address = 0x77; //I2C address
  OversamplingSetting mode;
  short calib_registers[11]; //values of all calibration registers
  bool init = false;
  const float sealevel_pressure = 101325.0;

  /**
   * Helper function to calculate B5 parameter.
   */
  int32_t B5(uint32_t UT);  
};

#endif
