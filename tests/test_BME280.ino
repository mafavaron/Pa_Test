/*
  Get environmental readings as a burst from the BME280
  By: Claudio Donaté
  Date: December 30th, 2020
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14348 - Qwiic Combo Board
  https://www.sparkfun.com/products/13676 - BME280 Breakout Board
  
  This example shows how to read humidity, pressure, and current temperature from the BME280 over I2C reading all registers at once.
  Please check BME280 Datasheet, section 4, Data readout for detail explanations on why.

  Hardware connections:
  BME280 -> Arduino
  GND -> GND
  3.3 -> 3.3
  SDA -> A4
  SCL -> A5
*/

#include <Wire.h>

#include "SparkFunBME280.h"

#define CELSIUS_SCALE 0 //Default
#define FAHRENHEIT_SCALE 1

BME280 mySensor;
BME280_SensorMeasurements measurements;

void setup()
{
  Serial.begin(115200);
  while(!Serial);

  Serial.println("Reading basic values from BME280 as a Burst");

  pinMode(LED_BUILTIN, OUTPUT);

  Wire.begin();
  mySensor.setI2CAddress(0x76);

  if (mySensor.beginI2C() == false) //Begin communication over I2C
  {
    Serial.println("The sensor did not respond. Please check wiring.");
    while(1) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(200);
      digitalWrite(LED_BUILTIN, LOW);
      delay(200);
    }; //Freeze
  }
}

void loop()
{
  while (mySensor.isMeasuring()); // Wait for sensor to finish measuring
    
  mySensor.readAllMeasurements(&measurements); // Return temperature in Celsius
  // mySensor.readAllMeasurements(&measurements, FAHRENHEIT_SCALE);
  
  Serial.print("Humidity: ");
  Serial.print(measurements.humidity, 0);

  Serial.print(" Pressure: ");
  Serial.print(measurements.pressure / 100.0, 2);

  Serial.print(" Temp: ");
  Serial.println(measurements.temperature, 2);

  delay(50);
}
