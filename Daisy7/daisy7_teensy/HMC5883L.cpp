#include "HMC5883L.h"
#include "daisy7.h"

void HMC5883L::write(byte reg, byte data) {
  daisy7->write(address, reg, data);
  }

byte HMC5883L::read(byte reg) {
  return daisy7->read(address, reg);
}

void HMC5883L::NormalMode() { 
  daisy7->write(address, MODE_REG, 0x00);
  }

bool HMC5883L::available() {
   byte data = daisy7->read(address, STATUS_REG);
   return ((data&0x01) != 0);
  }

short HMC5883L::X() {
  byte low_byte = daisy7->read(address, OUT_X_L);
  byte high_byte = daisy7->read(address, OUT_X_H);
  return (short)((high_byte<<8)|low_byte);    
  }

short HMC5883L::Y() {
  byte low_byte = daisy7->read(address, OUT_Y_L);
  byte high_byte = daisy7->read(address, OUT_Y_H);
  return (short)((high_byte<<8)|low_byte);    
  }

short HMC5883L::Z() {
  byte low_byte = daisy7->read(address, OUT_Z_L);
  byte high_byte = daisy7->read(address, OUT_Z_H);
  return (short)((high_byte<<8)|low_byte);    
  }


