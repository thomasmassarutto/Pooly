#include <Arduino.h>
void arrayShift(float array[], int length);

#include "Pooly.h"

Pool::Pool(float waterVolume){
    this->_waterVolume= waterVolume;
    this->_chlorinePump= nullptr;
    this->_phPlusPump= nullptr; 
    this->_phMinusPump= nullptr; 
    this->_masterPump= nullptr; 
    this->_waterPump= nullptr; 
    this->_chlorineSensor= nullptr; 
    this->_phSensor= nullptr; 
    this->_waterLevelSensor= nullptr; 
    this->_waterTemperatureSensor= nullptr; 

    for (int i=0; i<POOLMEMORY; i++){
        this->_waterChlorine[i]= 0.0;
        this->_waterLevel[i]= 0.0;
        this->_waterPh[i]= 0.0;
        this->_waterTemperature[i]= 0.0;
    }
}

bool Pool::hasSensor(WaterSensor* sensor){
    bool res= false;

    if (sensor != nullptr){
        res= true;
    }else{
        res= false;
    }
    return res;
}

bool Pool::hasPump(Pump* pump){
    bool res= false;

    if (pump != nullptr){
        res= true;
    }else{
        res= false;
    }
    return res;
}

void Pool::replaceSensor(WaterSensor*& oldSensor, WaterSensor* newSensor){
    delete oldSensor;
    oldSensor= newSensor;
}

void Pool::replacePump(Pump*& oldPump, Pump* newPump){
    delete oldPump;
    oldPump= newPump;
}

// set variabili 

void Pool::setRemainingFilteringTime(int remainingMinutes){
    this->_remainingFilteringTime= remainingMinutes;
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

// set pompe

void Pool::setChlorinePump(Pump* pump){
    this->replacePump(this->_chlorinePump, pump);
}

void Pool::setPhPlusPump(Pump* pump){
    this->replacePump(this->_phPlusPump, pump);        
}

void Pool::setPhMinusPump(Pump* pump){
    this->replacePump(this->_phMinusPump, pump);        
}

void Pool::setMasterPump(Pump* pump){
    this->replacePump(this->_masterPump, pump);
}

void Pool::setWaterPump(Pump* pump){
    this->replacePump(this->_waterPump, pump);
}

// check se sono presenti sensori

bool Pool::hasChlorineSensor(){
    return hasSensor(this->_chlorineSensor);
}

bool Pool::hasPhSensor(){
    return hasSensor(this->_phSensor);
}

bool Pool::hasWaterLevelSensor(){
    return hasSensor(this->_waterLevelSensor);
}

bool Pool::hasWaterTemperatureSensor(){
    return hasSensor(this->_waterTemperatureSensor);
}

// get variabili

float Pool::getWaterVolume(){
    return this->_waterVolume;
}

float Pool::getRemainingFilteringTime(){
    return this->_remainingFilteringTime;
}

// get valori misurati dai sensori

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

// get pompe

Pump* Pool::getChlorinePump(){
    return this->_chlorinePump;
}

Pump* Pool::getPhPlusPump(){
    return this->_phPlusPump;
}

Pump* Pool::getPhMinusPump(){
    return this->_phMinusPump;
}

Pump* Pool::getMasterPump(){
    return this->_masterPump;
}

Pump* Pool::getWaterPump(){
    return this->_waterPump;
}

// logica
void Pool::updateWaterStatus() {

    arrayShift(_waterChlorine, POOLMEMORY);
    arrayShift(_waterLevel, POOLMEMORY);
    arrayShift(_waterPh, POOLMEMORY);
    arrayShift(_waterTemperature, POOLMEMORY);

    int maxIterations = 5;

    float sumChlorine = 0.0;
    float sumPh = 0.0;
    float sumLevel = 0.0;
    float sumTemperature = 0.0;

    for (int i = 0; i < maxIterations; i++) {
        
        if (this->hasChlorineSensor()) {
            sumChlorine= sumChlorine +  _chlorineSensor->getMeasurement();
        }

        if (this->hasPhSensor()) {
            sumPh= sumPh +  _phSensor->getMeasurement();
        }

        if (this->hasWaterLevelSensor()) {
            sumLevel= sumLevel + _waterLevelSensor->getMeasurement();
        }

        if (this->hasWaterTemperatureSensor()) {
            sumTemperature= sumTemperature + _waterTemperatureSensor->getMeasurement();
        }

        delay(100); 
    }

 
    if (this->hasChlorineSensor() ) {
        _waterChlorine[0] = sumChlorine / maxIterations;
    }

    if (this->hasPhSensor()) {
        _waterPh[0] = sumPh / maxIterations;
    }

    if (this->hasWaterLevelSensor()) {
        _waterLevel[0] = sumLevel / maxIterations;
    }

    if (this->hasWaterTemperatureSensor()) {
        _waterTemperature[0] = sumTemperature / maxIterations;
    }
}

int Pool::calculateRecirculationMinutes(){
    int res=0;

    float waterVolume= this->_waterVolume;
    float masterPumpFlow= this->_waterPump->getPumpFlow();

    res= (waterVolume/masterPumpFlow) * 60;

    return res; 
}

// utils
void arrayShift(float array[], int length){
    
    for (int i = length-1; i> 0; i--){
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
