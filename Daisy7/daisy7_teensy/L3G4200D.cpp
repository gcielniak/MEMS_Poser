#include "L3G4200D.h"
#include "daisy7.h"

void L3G4200D::write(byte reg, byte data) {
  daisy7->write(address, reg, data);
  }

byte L3G4200D::read(byte reg) {
  return daisy7->read(address, reg);
}

void L3G4200D::AllAxesOn() {
  byte data = daisy7->read(address, CTRL_REG1);
  daisy7->write(address, CTRL_REG1, data|0xF);
  }

void L3G4200D::SetBandwidth(Bandwidth value) {
  byte data = daisy7->read(address, CTRL_REG1);
  daisy7->write(address, CTRL_REG1, (data&0b11001111)|(value<<4));
  }

void L3G4200D::SetDataRate(DataRate value) {
  byte data = daisy7->read(address, CTRL_REG1);
  daisy7->write(address, CTRL_REG1, (data&0b00111111)|(value<<6));
  }

void L3G4200D::SetHMFMode(HPF_Mode value) {
  byte data = daisy7->read(address, CTRL_REG2);
  daisy7->write(address, CTRL_REG2, (data&0b11001111)|(value<<4));
  }

void L3G4200D::SetHPFCutoff(HPF_Cutoff value) {
  byte data = daisy7->read(address, CTRL_REG2);
  daisy7->write(address, CTRL_REG2, (data&0b11110000)|value);
  }

void L3G4200D::SetDPS(DPS value) {
  byte data = daisy7->read(address, CTRL_REG4);
  daisy7->write(address, CTRL_REG4, (data&0b11001111)|(value<<4));
  }
  
bool L3G4200D::available() {
   byte data = daisy7->read(address, STATUS_REG);
   return ((data&0x08) != 0);
  }

short L3G4200D::X() {
  byte low_byte = daisy7->read(address, OUT_X_L);
  byte high_byte = daisy7->read(address, OUT_X_H);
  return (short)((high_byte<<8)|low_byte);    
  }

short L3G4200D::Y() {
  byte low_byte = daisy7->read(address, OUT_Y_L);
  byte high_byte = daisy7->read(address, OUT_Y_H);
  return (short)((high_byte<<8)|low_byte);    
  }

short L3G4200D::Z() {
  byte low_byte = daisy7->read(address, OUT_Z_L);
  byte high_byte = daisy7->read(address, OUT_Z_H);
  return (short)((high_byte<<8)|low_byte);    
  }


