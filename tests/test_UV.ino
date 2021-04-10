/*

  UV index sensor test

*/

int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = LED_BUILTIN;      // select the pin for the LED
double sensorValue = 0.0;  // variable to store the value coming from the sensor

void setup() {
  Serial.begin(9600);
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  analogReadResolution(12);
}

void loop() {

  // read the value from the UV sensor, and convert it to UV index
  sensorValue = (double)analogRead(sensorPin)/4095.0*3300.0;
  int iUVindex = 0;
  if(sensorValue >= 1170.0) {
    iUVindex = 11;
  }
  else if(sensorValue >= 1079.0) {
    iUVindex = 10;
  }
  else if(sensorValue >= 976.0) {
    iUVindex = 9;
  }
  else if(sensorValue >= 881.0) {
    iUVindex = 8;
  }
  else if(sensorValue >= 795.0) {
    iUVindex = 7;
  }
  else if(sensorValue >= 696.0) {
    iUVindex = 6;
  }
  else if(sensorValue >= 606.0) {
    iUVindex = 5;
  }
  else if(sensorValue >= 503.0) {
    iUVindex = 4;
  }
  else if(sensorValue >= 408.0) {
    iUVindex = 3;
  }
  else if(sensorValue >= 318.0) {
    iUVindex = 2;
  }
  else if(sensorValue >= 227.0) {
    iUVindex = 1;
  }

  // print reults
  Serial.println(iUVindex);
  delay(1000);

}
