#include "BMP085.h"
#include "daisy7.h"

void BMP085::write(byte reg, byte data) {
  daisy7->write(address, reg, data);
  }

byte BMP085::read(byte reg) {
  return daisy7->read(address, reg);
}

void BMP085::Mode(OversamplingSetting mode) {
  this->mode = mode;
  if (!init) {
    byte high_byte, low_byte;
    
    for (int i = 0; i < 11; i++) {
      high_byte = daisy7->read(address, CALIB_REG+i*2);
      low_byte = daisy7->read(address, CALIB_REG+i*2+1);
      calib_registers[i] = (short)((high_byte<<8)|low_byte);
      } 
     init = true;
    }
  }
  
int32_t BMP085::B5(uint32_t ut) {
  int32_t x1 = (((int32_t)ut - (int32_t)((uint16_t)calib_registers[I_AC6])) * (int32_t)((uint32_t)calib_registers[I_AC5])) >> 15;
  int32_t x2 = ((int32_t)calib_registers[I_MC] << 11) / (x1 + (int32_t)calib_registers[I_MD]);
  return (x1 + x2);
}

uint16_t BMP085::TemperatureRaw() {
  daisy7->write(address, CONTROL, READTEMPCMD);
  delay(5);
  byte high_byte = daisy7->read(address, TEMPDATA);
  byte low_byte = daisy7->read(address, TEMPDATA+1);
  return (uint16_t)((high_byte<<8)|low_byte);    
  }

int32_t BMP085::Temperature() {
  return ((B5(TemperatureRaw()) + 8) >> 4);
  }

uint32_t BMP085::PressureRaw() {
  daisy7->write(address, CONTROL, READPRESSURECMD + (mode << 6));

  delay(2 + (3 << mode));

  byte high_byte = daisy7->read(address, PRESSUREDATA);
  byte low_byte = daisy7->read(address, PRESSUREDATA+1);
  byte xlow_byte = daisy7->read(address, PRESSUREDATA+2);
    
  return (((uint32_t)high_byte << 16) | ((uint32_t)low_byte << 8) | (uint32_t)xlow_byte) >> (8 - mode);
  }

int32_t BMP085::Pressure() {
  int32_t x1, x2, p, b6, b3;
  uint32_t b4, b7;

  // do pressure calcs
  b6 = B5(TemperatureRaw()) - 4000;

  x1 = ((int32_t)calib_registers[I_B2] * ( (b6 * b6) >> 12)) >> 11;
  x2 = ((int32_t)calib_registers[I_AC2] * b6) >> 11;
  b3 = ((((int32_t)calib_registers[I_AC1]*4 + (x1 + x2)) << mode) + 2) / 4;

  x1 = ((int32_t)calib_registers[I_AC3] * b6) >> 13;
  x2 = ((int32_t)calib_registers[I_B1] * ((b6 * b6) >> 12)) >> 16;
  b4 = ((uint32_t)((uint16_t)calib_registers[I_AC4]) * (uint32_t)((((x1 + x2) + 2) >> 2) + 32768)) >> 15;
  b7 = ((uint32_t)PressureRaw() - b3) * (uint32_t)( 50000UL >> mode);

  if (b7 < 0x80000000) {
    p = (b7 * 2) / b4;
  } else {
    p = (b7 / b4) * 2;
  }
  x1 = (p >> 8) * (p >> 8);
  x1 = (x1 * 3038) >> 16;
  x2 = (-7357 * p) >> 16;

  p = p + ((x1 +x2 + (int32_t)3791)>>4);

  return p;
}

float BMP085::Altitude() {
  return (44330.0 * (1.0 - pow((float)Pressure()/sealevel_pressure, 0.190284)));
    }
