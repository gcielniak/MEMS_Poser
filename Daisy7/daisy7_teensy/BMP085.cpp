#include "BMP085.h"
#include "daisy7.h"

void BMP085::write(byte reg, byte data) {
  daisy7->write(address, reg, data);
  }

byte BMP085::read(byte reg) {
  return daisy7->read(address, reg);
}

void BMP085::NormalMode() {
  mode = STANDARD;
  byte high_byte, low_byte;
  
  for (int i = 0; i < 11; i++) {
    high_byte = daisy7->read(address, CALIB_DATA+i*2);
    low_byte = daisy7->read(address, CALIB_DATA+i*2+1);
    calib_registers[i] = (unsigned short)((high_byte<<8)|low_byte);
    } 
  }

int32_t BMP085::B5(uint32_t UT) {
  int32_t X1 = ((int32_t)UT - (int32_t)calib_registers[I_AC6]) * ((int32_t)calib_registers[I_AC5]) >> 15;
  int32_t X2 = ((int32_t)calib_registers[I_MC] << 11) / (X1+(int32_t)calib_registers[I_MD]);
  return X1 + X2;
}

uint16_t BMP085::TemperatureRaw() {
  daisy7->write(address, CONTROL, READTEMPCMD);
  delay(5);
  byte high_byte = daisy7->read(address, TEMPDATA);
  byte low_byte = daisy7->read(address, TEMPDATA+1);
  return (uint16_t)((high_byte<<8)|low_byte);    
  }


float BMP085::Temperature() {
  float temp = (B5(TemperatureRaw())+8) >> 4;
  temp /= 10;
  return temp;
  }

uint32_t BMP085::PressureRaw() {
  daisy7->write(address, CONTROL, READPRESSURECMD + (mode << 6));

  if (mode == ULTRALOWPOWER)
    delay(5);
  else if (mode == HIGHRES)
    delay(14);
  else if (mode == ULTRAHIGHRES)
    delay(26);
  else
    delay(8);

  byte high_byte = daisy7->read(address, PRESSUREDATA);
  byte low_byte = daisy7->read(address, PRESSUREDATA+1);
  byte xlow_byte = daisy7->read(address, PRESSUREDATA+2);
    
  return (uint32_t )((high_byte << 16) + (low_byte << 8) + xlow_byte) >> (8 - mode);
  }

int32_t BMP085::Pressure() {
  int32_t B3, B6, X1, X2, X3, p;
  uint32_t B4, B7;

  // do pressure calcs
  B6 = B5(TemperatureRaw()) - 4000;
  X1 = ((int32_t)calib_registers[I_B2] * ( (B6 * B6)>>12 )) >> 11;
  X2 = ((int32_t)calib_registers[I_AC2] * B6) >> 11;
  X3 = X1 + X2;
  B3 = ((((int32_t)calib_registers[I_AC1]*4 + X3) << mode) + 2) / 4;

  X1 = ((int32_t)calib_registers[I_AC3] * B6) >> 13;
  X2 = ((int32_t)calib_registers[I_B1] * ((B6 * B6) >> 12)) >> 16;
  X3 = ((X1 + X2) + 2) >> 2;
  B4 = ((uint32_t)calib_registers[I_AC4] * (uint32_t)(X3 + 32768)) >> 15;
  B7 = ((uint32_t)PressureRaw() - B3) * (uint32_t)( 50000UL >> mode);

  if (B7 < 0x80000000) {
    p = (B7 * 2) / B4;
  } else {
    p = (B7 / B4) * 2;
  }
  X1 = (p >> 8) * (p >> 8);
  X1 = (X1 * 3038) >> 16;
  X2 = (-7357 * p) >> 16;

  p = p + ((X1 + X2 + (int32_t)3791)>>4);

  return p;
}

