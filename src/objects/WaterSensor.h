#ifndef WATERSENSOR_H
#define WATERSENSOR_H

#include "Pooly.h"
class WaterSensor{
    private:
        int _pin;
        float (*_correctiveFunction)(float);

    public:
        WaterSensor(int pin);
        WaterSensor(int pin, float (*correctiveFunction)(float));

        int getPin();

        float getMeasurement();
        float getAverageMeasurement(int times);
};

#endif