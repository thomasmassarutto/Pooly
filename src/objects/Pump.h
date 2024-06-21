#ifndef PUMP_H
#define PUMP_H

class Pump{
    private:
        int _pin;
        bool _pump_status;
        float _flow;

    public:
        Pump(int pin, float flow);
        
        int getPin();

        void pumpStart();
        void pumpStop();
        void activatePump(int seconds);
};

#endif