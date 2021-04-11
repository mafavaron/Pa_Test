#include <mbed.h>

using namespace rtos;
using namespace mbed;

Thread t1;
Thread t2;

void func1() {
  while(1) {
    Serial.println("A");
    ThisThread::sleep_for(2000);
  }
}

void func2() {
  while(1) {
    Serial.println("a");
    ThisThread::sleep_for(3500);
  }
}

void setup() {
  Serial.begin(9600);
  t1.start(func1);
  t2.start(func2);
}

void loop() {}
