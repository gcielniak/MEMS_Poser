#include "LIS331DLH.h"
#include "daisy7.h"

void LIS331DLH::write(byte reg, byte data) {
  daisy7->write(address, reg, data);
  }

byte LIS331DLH::read(byte reg) {
  return daisy7->read(address, reg);
}

void LIS331DLH::AllAxesOn() {
  byte data = daisy7->read(address, CTRL_REG1);
  daisy7->write(address, CTRL_REG1, data|0b111);
  }
  
void LIS331DLH::SetDataRate(DataRate value) {
  byte data = daisy7->read(address, CTRL_REG1);
  daisy7->write(address, CTRL_REG1, (data&0b11100111)|(value<<3));
  }

void LIS331DLH::SetPowerMode(PowerMode value) {
  byte data = daisy7->read(address, CTRL_REG1);
  daisy7->write(address, CTRL_REG1, (data&0b00011111)|(value<<5));
  }

bool LIS331DLH::available() {
   byte data = daisy7->read(address, STATUS_REG);
   return ((data&0x08) != 0);
  }

short LIS331DLH::X() {
  byte low_byte = daisy7->read(address, OUT_X_L);
  byte high_byte = daisy7->read(address, OUT_X_H);
  return (short)((high_byte<<8)|low_byte);    
  }

short LIS331DLH::Y() {
  byte low_byte = daisy7->read(address, OUT_Y_L);
  byte high_byte = daisy7->read(address, OUT_Y_H);
  return (short)((high_byte<<8)|low_byte);    
  }

short LIS331DLH::Z() {
  byte low_byte = daisy7->read(address, OUT_Z_L);
  byte high_byte = daisy7->read(address, OUT_Z_H);
  return (short)((high_byte<<8)|low_byte);    
  }


