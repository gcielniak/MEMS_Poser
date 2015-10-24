#include <Wire.h>
#include "daisy7.h"

#define acc_address 0x18

Daisy7 daisy;

void setup()

{
 Serial.begin(57600);
 Serial.println("Wire.begin");

 daisy.accelerator->NormalMode();
}
 

void loop()
{
  while (!daisy.accelerator->NewData())
    ;
 
 Serial.print("acc x=");
 Serial.print(daisy.accelerator->X());
 Serial.print(" y=");
 Serial.print(daisy.accelerator->Y());
 Serial.print(" z=");
 Serial.println(daisy.accelerator->Z());

 delay(100);
}

