#include <Arduino.h>

# include "Pump.h"

Pump::Pump(int pin, float flow){
    pinMode(pin, OUTPUT);
    this->_pin= pin;
    this->_flow= flow;
}

int Pump::getPin(){
    return this->_pin;
}

void Pump::pumpStart(){
    this->_pump_status= true;
    digitalWrite(_pin, HIGH);
}

void Pump::pumpStop(){
    digitalWrite(_pin, LOW);
    this->_pump_status= false;
}

void Pump::activatePump(int seconds){
    this->_pump_status= true;
    digitalWrite(_pin, HIGH);
    
    delay(seconds * 1000);
    
    digitalWrite(_pin, LOW);
    this->_pump_status= true;
}