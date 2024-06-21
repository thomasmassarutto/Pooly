#ifndef POOL_H
#define POOL_H

#include "Pump.h"
#include "WaterSensor.h"

#define MAX 100

class Pool {
private:
    float _waterVolume;

    float _waterChlorine[MAX];
    float _waterLevel[MAX];
    float _waterPh[MAX];
    float _waterTemperature[MAX];

    Pump* _chlorinePump;
    Pump* _phPump;
    Pump* _masterPump;
    Pump* _waterPump;

    WaterSensor* _chlorineSensor;
    WaterSensor* _phSensor;
    WaterSensor* _waterLevelSensor;
    WaterSensor* _waterTemperatureSensor;

    void replaceSensor(WaterSensor*& oldSensor, WaterSensor* newSensor);
    void replacePump(Pump*& oldPump, Pump* newPump);

public:
    Pool(float waterVolume);

    void setChlorineSensor(WaterSensor* sensor);
    void setPhSensor(WaterSensor* sensor);
    void setWaterLevelSensor(WaterSensor* sensor);
    void setWaterTemperatureSensor(WaterSensor* sensor);

    void setChlorinePump(Pump* pump);
    void setPhPump(Pump* pump);
    void setMasterPump(Pump* pump);
    void setWaterPump(Pump* pump);

    float getWaterChlorine();
    float getWaterLevel();
    float getWaterPh();
    float getWaterTemperature();

    void updateStatus();

    void test();
};

#endif
