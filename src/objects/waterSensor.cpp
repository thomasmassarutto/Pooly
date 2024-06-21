#include <Arduino.h>

#include "WaterSensor.h"

WaterSensor::WaterSensor(int pin){
    this->_pin= pin;
    this->_correctiveFunction = nullptr;
    pinMode(pin, INPUT);

}

WaterSensor::WaterSensor(int pin, float (*correctiveFunction)(float)){
    this->_pin= pin;
    pinMode(pin, INPUT);
    this->_correctiveFunction= correctiveFunction; 
}

int WaterSensor::getPin(){
    return this->_pin;
}

float WaterSensor::getMeasurement(){
    float mes= analogRead(this->_pin);

    if (this->_correctiveFunction != nullptr) {
        mes = this->_correctiveFunction(mes);
    }

    return mes;
}

float WaterSensor::getAverageMeasurement(int times){
    float res=0;

    for (int i;i<=times;i++){
        res= res + analogRead(this->_pin);
    }

    res= res / times;

    if (this->_correctiveFunction != nullptr) {
        res = this->_correctiveFunction(res);
    }

    return res;
}