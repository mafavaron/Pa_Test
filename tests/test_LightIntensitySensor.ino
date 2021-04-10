
#include "Wire.h"

int lightBegin(void)
{
  Wire.beginTransmission(0x4A);
  Wire.write(0x02);
  Wire.write(0x00); // changed from 0x40
  
  return Wire.endTransmission();
  
}


float lightGetLux(void)
{
  
  unsigned int data[2];
  
  Wire.beginTransmission(0x4A);
  Wire.write(0x03); //request high-byte register data
  Wire.endTransmission();

  // Request 1 byte of data
  Wire.requestFrom(0x4A, 1);

  // Wait some time, to allow the MAX 44009 microcontroller to process the answer
  // (this step may not be needed on 8-bit Arduinos, but it's indispensable on
  // my very fast Nano 33 BLE Sense).
  delay(10);

  // Read first byte of data
  if (Wire.available() == 1)
  {
    data[0] = Wire.read();
  }

  Wire.beginTransmission(0x4A);
  Wire.write(0x04); //request low-byte register data
  Wire.endTransmission();

  // Request 1 byte of data
  Wire.requestFrom(0x4A, 1);

  // Read second byte of data
  if (Wire.available() == 1)
  {
    data[1] = Wire.read();
  }
 
  // Convert the data to lux
  int exponent = (data[0] & 0xF0) >> 4;
  int mantissa = ((data[0] & 0x0F) << 4) | (data[1] & 0x0F);
  
  //float luminance = pow(2, exponent) * mantissa * 0.045;
  float luminance = (float)(((0x00000001 << exponent) * (float)mantissa) * 0.045);
  
  return luminance; 
  
}

void setup()
{
  Serial.begin(9600);

  Wire.begin();

  int iRetCode = lightBegin();

}

void loop()
{

  float lux = lightGetLux();

  Serial.println(lux);

  delay(1000);
  
}

// END OF FILE
