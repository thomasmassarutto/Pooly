#include <Arduino.h>

#include "Pooly.h"

Pump::Pump(int pin, float flow){
    pinMode(pin, OUTPUT);
    this->_pin= pin;
    this->_flow= flow;
}

// get
int Pump::getPin(){
    return this->_pin;
}
float Pump::getPumpFlow(){
    return this->_flow;
}

// azioni
void Pump::pumpStart(){
    this->_pump_status= true;
    digitalWrite(_pin, HIGH);
}

void Pump::pumpStop(){
    digitalWrite(_pin, LOW);
    this->_pump_status= false;
}

void Pump::activatePump(int milliSeconds){
    this->_pump_status= true;
    digitalWrite(_pin, HIGH);
    
    delay(milliSeconds);
    
    digitalWrite(_pin, LOW);
    this->_pump_status= true;
}