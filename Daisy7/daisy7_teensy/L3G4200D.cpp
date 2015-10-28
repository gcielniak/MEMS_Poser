#include "L3G4200D.h"
#include "daisy7.h"

void L3G4200D::write(byte reg, byte data) {
  daisy7->write(address, reg, data);
  }

byte L3G4200D::read(byte reg) {
  return daisy7->read(address, reg);
}

void L3G4200D::NormalMode() {  
  //Chip in Normal mode. Turn on all axis
  daisy7->write(address, (byte)L3G4200DRegister::CTRL_REG1, 0x0F);
  //Full 2000dps to control REG4
  daisy7->write(address, (byte)L3G4200DRegister::CTRL_REG4, 0x20);
  }

bool L3G4200D::available() {
   byte data = daisy7->read(address, (byte)L3G4200DRegister::STATUS_REG);
   return ((data&0x08) != 0);
  }

short L3G4200D::X() {
  byte low_byte = daisy7->read(address, (byte)L3G4200DRegister::OUT_X_L);
  byte high_byte = daisy7->read(address, (byte)L3G4200DRegister::OUT_X_H);
  return (short)((high_byte<<8)|low_byte);    
  }

short L3G4200D::Y() {
  byte low_byte = daisy7->read(address, (byte)L3G4200DRegister::OUT_Y_L);
  byte high_byte = daisy7->read(address, (byte)L3G4200DRegister::OUT_Y_H);
  return (short)((high_byte<<8)|low_byte);    
  }

short L3G4200D::Z() {
  byte low_byte = daisy7->read(address, (byte)L3G4200DRegister::OUT_Z_L);
  byte high_byte = daisy7->read(address, (byte)L3G4200DRegister::OUT_Z_H);
  return (short)((high_byte<<8)|low_byte);    
  }


