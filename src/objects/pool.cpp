#include <Arduino.h>
void arrayShift(float array[], int length);

# include "Pool.h"
# include "Pump.h"
# include "WaterSensor.h"

Pool::Pool(float waterVolume){
    this->_waterVolume= waterVolume;
    this->_chlorinePump= nullptr;
    this->_phPump= nullptr; 
    this->_masterPump= nullptr; 
    this->_waterPump= nullptr; 
    this->_chlorineSensor= nullptr; 
    this->_phSensor= nullptr; 
    this->_waterLevelSensor= nullptr; 
    this->_waterTemperatureSensor= nullptr; 

    for (int i=0; i<MAX; i++){
        this->_waterChlorine[i]= 0.0;
        this->_waterLevel[i]= 0.0;
        this->_waterPh[i]= 0.0;
        this->_waterTemperature[i]= 0.0;
    }
}

// privati
void Pool::replaceSensor(WaterSensor*& oldSensor, WaterSensor* newSensor){
    delete oldSensor;
    oldSensor= newSensor;
}

void Pool::replacePump(Pump*& oldPump, Pump* newPump){
    delete oldPump;
    oldPump= newPump;
}

// set pompe
void Pool::setChlorinePump(Pump* pump){
    this->replacePump(this->_chlorinePump, pump);
}

void Pool::setPhPump(Pump* pump){
    this->replacePump(this->_phPump, pump);        
}

void Pool::setMasterPump(Pump* pump){
    this->replacePump(this->_masterPump, pump);
}

void Pool::setWaterPump(Pump* pump){
    this->replacePump(this->_waterPump, pump);
}

// set sensori
void Pool::setChlorineSensor(WaterSensor* sensor) {
    this->replaceSensor(this->_chlorineSensor, sensor);
}

void Pool::setPhSensor(WaterSensor* sensor) {
    this->replaceSensor(this->_phSensor, sensor);
}

void Pool::setWaterLevelSensor(WaterSensor* sensor) {
    this->replaceSensor(this->_waterLevelSensor, sensor);
}

void Pool::setWaterTemperatureSensor(WaterSensor* sensor) {
    this->replaceSensor(this->_waterTemperatureSensor, sensor);
}

//
float Pool::getWaterChlorine(){
    return this->_waterChlorine[0];
}

float Pool::getWaterLevel(){
    return this->_waterLevel[0];
}

float Pool::getWaterPh(){
    return this->_waterPh[0];
}

float Pool::getWaterTemperature(){
    return this->_waterTemperature[0];
}

void Pool::updateStatus() {

    arrayShift(_waterChlorine, MAX);
    arrayShift(_waterLevel, MAX);
    arrayShift(_waterPh, MAX);
    arrayShift(_waterTemperature, MAX);

    int maxIterations = 5;

    float sumChlorine = 0.0;
    float sumPh = 0.0;
    float sumLevel = 0.0;
    float sumTemperature = 0.0;

    for (int i = 0; i < maxIterations; i++) {
        if (_chlorineSensor != nullptr) {
            sumChlorine= sumChlorine +  _chlorineSensor->getMeasurement();
        }

        if (true) {
            sumPh= sumPh +  _phSensor->getMeasurement();
        }

        if (_waterLevelSensor != nullptr) {
            sumLevel= sumLevel + _waterLevelSensor->getMeasurement();
        }

        if (_waterTemperatureSensor != nullptr) {
            sumTemperature= sumTemperature + _waterTemperatureSensor->getMeasurement();
        }

        delay(100); 
    }

 
    if (_chlorineSensor != nullptr ) {
        _waterChlorine[0] = sumChlorine / maxIterations;
    }

    if (true) {
        _waterPh[0] = sumPh / maxIterations;
    }

    if (_waterLevelSensor != nullptr) {
        _waterLevel[0] = sumLevel / maxIterations;
    }

    if (_waterTemperatureSensor != nullptr) {
        _waterTemperature[0] = sumTemperature / maxIterations;
    }
}


// utils
void arrayShift(float array[], int length){
    
    for (int i = length-1; i> 0;i--){
        array[i]= array[i-1];
    }

    array[0]=0;
}

void Pool::test() {

    Serial.println("test:\t\t ");
    if (_chlorineSensor == nullptr) {
        Serial.println("*_chlorineSensor nullptr");
    } else {
        int mes = _chlorineSensor->getMeasurement();
        Serial.print("cloro:\t\t ");
        Serial.println(mes);
        delay(20);
    }

    if (_phSensor == nullptr) {
        Serial.println("*_chlorineSensor nullptr");
    } else {
        int mes = _phSensor->getMeasurement();
        Serial.print("ph:\t\t ");
        Serial.println(mes);
        delay(20);
    }
}
