#ifndef PUMP_H
#define PUMP_H

#include "Pooly.h"

class Pump{
private:
    int _pin;
    bool _pump_status;
    float _flow;

public:
    /*
    * @param pin: pin del rele per attivare la pompa
    * @param flow: flow della pompa in m^3/h
    */
    Pump(int pin, float flow);
        
    int getPin();
    float getPumpFlow();

    void pumpStart();
    void pumpStop();      
    /*
    * attiva la pompa per tot secondi
    * @param milliseconds: secondi 
    * @attention bloccante
    */
    void activatePump(int milliSeconds);
};

#endif