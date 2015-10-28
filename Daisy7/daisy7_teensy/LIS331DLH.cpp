#include "LIS331DLH.h"
#include "daisy7.h"

void LIS331DLH::write(byte reg, byte data) {
  daisy7->write(address, reg, data);
  }

byte LIS331DLH::read(byte reg) {
  return daisy7->read(address, reg);
}

void LIS331DLH::NormalMode() {
  daisy7->write(address, (byte)LIS331DLHRegister::CTRL_REG1, ((byte)LIS331DLHPowerMode::POWER_NORMAL<<5)|((byte)LIS331DLHODR::ODR_50_HZ<<3)|7);
  }

bool LIS331DLH::available() {
   byte data = daisy7->read(address, (byte)LIS331DLHRegister::STATUS_REG);
   return ((data&0x08) != 0);
  }

short LIS331DLH::X() {
  byte low_byte = daisy7->read(address, (byte)LIS331DLHRegister::OUT_X_L);
  byte high_byte = daisy7->read(address, (byte)LIS331DLHRegister::OUT_X_H);
  return (short)((high_byte<<8)|low_byte);    
  }

short LIS331DLH::Y() {
  byte low_byte = daisy7->read(address, (byte)LIS331DLHRegister::OUT_Y_L);
  byte high_byte = daisy7->read(address, (byte)LIS331DLHRegister::OUT_Y_H);
  return (short)((high_byte<<8)|low_byte);    
  }

short LIS331DLH::Z() {
  byte low_byte = daisy7->read(address, (byte)LIS331DLHRegister::OUT_Z_L);
  byte high_byte = daisy7->read(address, (byte)LIS331DLHRegister::OUT_Z_H);
  return (short)((high_byte<<8)|low_byte);    
  }

