#include "HMC5883L.h"
#include "daisy7.h"

void HMC5883L::write(byte reg, byte data) {
  daisy7->write(address, reg, data);
  }

byte HMC5883L::read(byte reg) {
  return daisy7->read(address, reg);
}

void HMC5883L::SetSampleMode(SampleMode mode) {
  conf_reg_a = (conf_reg_a&0b10011111)|(mode<<5);
  daisy7->write(address, CONF_REG_A, conf_reg_a);
  }

void HMC5883L::SetDataRate(DataRate rate) {
  conf_reg_a = (conf_reg_a&0b11100011)|(rate<<2);
  daisy7->write(address, CONF_REG_A, conf_reg_a);
  }

void HMC5883L::SetMeasurementMode(MeasurementMode mode) {
  conf_reg_a = (conf_reg_a&0b11111100)|mode;
  daisy7->write(address, CONF_REG_A, conf_reg_a);
  }

void HMC5883L::SetOperatingMode(OperatingMode mode) {
  daisy7->write(address, MODE_REG, mode);
  }

void HMC5883L::SetGain(Gain gain) {
  daisy7->write(address, CONF_REG_B, gain<<5);  
  }

bool HMC5883L::available() {
   byte data = daisy7->read(address, STATUS_REG);
   return ((data&0x03) == 1);
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

