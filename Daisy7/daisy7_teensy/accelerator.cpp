#include "accelerator.h"
#include "daisy7.h"

void Accelerator::write(byte reg, byte data) {
  daisy7->write(address, reg, data);
  }

byte Accelerator::read(byte reg) {
  return daisy7->read(address, reg);
}

void Accelerator::NormalMode() {
  daisy7->write(address, CTRL_REG1, (POWER_NORMAL<<5)|(ODR_50_HZ<<3)|7);
  }

bool Accelerator::available() {
   byte data = daisy7->read(address, STATUS_REG);
   return ((data&0x08) != 0);
  }

short Accelerator::X() {
  byte low_byte = daisy7->read(address, OUT_X_L);
  byte high_byte = daisy7->read(address, OUT_X_H);
  return (short)((high_byte<<8)|low_byte);    
  }

short Accelerator::Y() {
  byte low_byte = daisy7->read(address, OUT_Y_L);
  byte high_byte = daisy7->read(address, OUT_Y_H);
  return (short)((high_byte<<8)|low_byte);    
  }

short Accelerator::Z() {
  byte low_byte = daisy7->read(address, OUT_Z_L);
  byte high_byte = daisy7->read(address, OUT_Z_H);
  return (short)((high_byte<<8)|low_byte);    
  }


