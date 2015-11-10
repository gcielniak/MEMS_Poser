#ifndef GPS_H
#define GPS_H

#include "Arduino.h"

/**
 * A GPS receiver Venus638LPx by Skytraq.
 */
class GPS {
  public:

  /**
   * Update the internal GPS string.
   */
  void update(byte data) {
    if (available())
      gps_slength = 0;          
    gps_line[gps_slength++] = data;
    }

  /**
   * New string available.
   */
  bool available() {
    return ((gps_slength > 2) && (gps_line[gps_slength-1] == 0x0A) && (gps_line[gps_slength-2] == 0x0D));
    }

  char* GetLine() {
    return gps_line;
    }

  byte GetLength() {
    return gps_slength;
    }

private:
  char gps_line[82];
  byte gps_slength = 0;  
};

#endif
