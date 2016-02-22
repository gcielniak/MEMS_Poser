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
  this->gain = gain;
  daisy7->write(address, CONF_REG_B, gain<<5);  
  }

bool HMC5883L::available() {
   reading_updated = false;
   byte data = daisy7->read(address, STATUS_REG);
   return ((data&0x03) == 1);
  }

short HMC5883L::XRaw() {
  byte low_byte = daisy7->read(address, OUT_X_L);
  byte high_byte = daisy7->read(address, OUT_X_H);
  return (short)((high_byte<<8)|low_byte);    
  }

short HMC5883L::YRaw() {
  byte low_byte = daisy7->read(address, OUT_Y_L);
  byte high_byte = daisy7->read(address, OUT_Y_H);
  return (short)((high_byte<<8)|low_byte);    
  }

short HMC5883L::ZRaw() {
  byte low_byte = daisy7->read(address, OUT_Z_L);
  byte high_byte = daisy7->read(address, OUT_Z_H);
  return (short)((high_byte<<8)|low_byte);    
  }

float HMC5883L::X() {
  short raw_value = XRaw();
  
  if (prev_reading[0] != raw_value)
    reading_updated = true;
  prev_reading[0] = raw_value;
  
  if (raw_value == -4096)
    return NAN;
  else
    return ((float)raw_value)*x_gain/gain_ratio[gain];
  }

float HMC5883L::Y() {
  short raw_value = YRaw();

  if (prev_reading[1] != raw_value)
    reading_updated = true;
  prev_reading[1] = raw_value;
  
  if (raw_value == -4096)
    return NAN;
  else
    return ((float)raw_value)*y_gain/gain_ratio[gain];
  }

float HMC5883L::Z() {
  short raw_value = ZRaw();

  if (prev_reading[2] != raw_value)
    reading_updated = true;
  prev_reading[2] = raw_value;

  if (raw_value == -4096)
    return NAN;
  else
    return ((float)raw_value)*z_gain/gain_ratio[gain];
  }

void HMC5883L::SelfTest() {
  //no bias
  SetOperatingMode(MEASUREMENT_IDLE);
  SetMeasurementMode(NO_BIAS);
  SetOperatingMode(MEASUREMENT_SINGLE);
  delay(10);
  
  //positive bias
  SetOperatingMode(MEASUREMENT_IDLE);
  SetMeasurementMode(POS_BIAS);
  SetOperatingMode(MEASUREMENT_SINGLE);
  delay(10);
  short x_pos = XRaw();
  short y_pos = YRaw();
  short z_pos = ZRaw();
  
  //negative bias
  SetOperatingMode(MEASUREMENT_IDLE);
  SetMeasurementMode(NEG_BIAS);
  SetOperatingMode(MEASUREMENT_SINGLE);
  delay(10);
  short x_neg = XRaw();
  short y_neg = YRaw();
  short z_neg = ZRaw();
  
  x_gain = 232./((float)(x_pos-x_neg)/gain_ratio[gain]);
  y_gain = 232./((float)(y_pos-y_neg)/gain_ratio[gain]);
  z_gain = 216./((float)(z_pos-z_neg)/gain_ratio[gain]);

  //resume operation
  SetMeasurementMode(NO_BIAS);
  SetOperatingMode(MEASUREMENT_CONT);
  delay(10);
  }

