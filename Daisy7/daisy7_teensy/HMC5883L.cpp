#include "HMC5883L.h"
#include "daisy7.h"

void HMC5883L::write(byte reg, byte data) {
  daisy7->write(address, reg, data);
  }

byte HMC5883L::read(byte reg) {
  return daisy7->read(address, reg);
}

void HMC5883L::NormalMode() {
//      self.compass_setScale(1.3)
//    self.compass_setContinuousMode()
//    self.compass_setDeclination(9,54)
    
  daisy7->write(address, (byte)LIS331DLHRegister::CTRL_REG1, ((byte)LIS331DLHPowerMode::POWER_NORMAL<<5)|((byte)LIS331DLHODR::ODR_50_HZ<<3)|7);
  }

bool HMC5883L::available() {
   byte data = daisy7->read(address, (byte)HMC5883LRegister::STATUS_REG);
   return ((data&0x08) != 0);
  }

short HMC5883L::X() {
  byte low_byte = daisy7->read(address, (byte)HMC5883LRegister::OUT_X_L);
  byte high_byte = daisy7->read(address, (byte)HMC5883LRegister::OUT_X_H);
  return (short)((high_byte<<8)|low_byte);    
  }

short HMC5883L::Y() {
  byte low_byte = daisy7->read(address, (byte)HMC5883LRegister::OUT_Y_L);
  byte high_byte = daisy7->read(address, (byte)HMC5883LRegister::OUT_Y_H);
  return (short)((high_byte<<8)|low_byte);    
  }

short HMC5883L::Z() {
  byte low_byte = daisy7->read(address, (byte)HMC5883LRegister::OUT_Z_L);
  byte high_byte = daisy7->read(address, (byte)HMC5883LRegister::OUT_Z_H);
  return (short)((high_byte<<8)|low_byte);    
  }


