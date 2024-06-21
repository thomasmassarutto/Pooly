/*
This example code sets up a pool monitoring system using Arduino. 
It defines a Pool object with 2 WaterSensors to measure chlorine and pH levels (sensors can be potentiometers). 
The sensors are initialized (mapPh is a dummy function to calculate pH from a resistive value). 
In the setup function, the sensors are attached to the Pool object. 
In the loop function, the pool status is updated, and the current chlorine and pH levels are printed to the Serial Monitor.
*/

#include <Arduino.h>

#include <Pooly.h>

float mapPh(float x);

Pool piscina(50);

WaterSensor sensoreCloro(A0);
WaterSensor sensorePh(A1, mapPh);

void setup() {
  Serial.begin(9600);
  Serial.println("Hello there");

  piscina.setChlorineSensor(&sensoreCloro);
  piscina.setPhSensor(&sensorePh);
  

  delay(3000);
}

void loop() {
  Serial.println("----");

  piscina.updateStatus();

  Serial.println("test:\t\t ");

  float cl = piscina.getWaterChlorine();
  Serial.print("cloro:\t\t ");
  Serial.println(cl);
  delay(20);
  
  float ph = piscina.getWaterPh();
  Serial.print("ph:\t\t ");
  Serial.println(ph);
  delay(20);
  

  delay(1000);
}

//--------------------------------------//

float mapPh(float x){

  return map(x, 0, 1023, 0, 14);
}