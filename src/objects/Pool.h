#ifndef POOL_H
#define POOL_H

#include "Pooly.h"

#include "Pump.h"
#include "WaterSensor.h"

class Pool {
private:
    float _waterVolume; // volume di acqua nella piscina
    int _remainingFilteringTime; // minuti rimanenti di filtraggio acqua

    float _waterChlorine[POOLMEMORY]; // storico valori cloro misurati
    float _waterLevel[POOLMEMORY]; // storico livello acqua misurati
    float _waterPh[POOLMEMORY]; // storico valori ph misurati
    float _waterTemperature[POOLMEMORY]; // storico temperatura acqua misurata

    WaterSensor* _chlorineSensor; // sensore cloro
    WaterSensor* _phSensor; // sensore ph
    WaterSensor* _waterLevelSensor; // sensore livello acqua
    WaterSensor* _waterTemperatureSensor; // sensore temperatura acqua

    Pump* _chlorinePump; // pompa per aggiungere cloro
    Pump* _phPlusPump; // pompa per ph+
    Pump* _phMinusPump; // pompa per ph-
    Pump* _masterPump; // pompa della piscina
    Pump* _waterPump; // pompa per aggiungere acqua
    
    // metodi generici privati

    bool hasPump(Pump* pump);
    bool hasSensor(WaterSensor* sensor);

    void replaceSensor(WaterSensor*& oldSensor, WaterSensor* newSensor);
    void replacePump(Pump*& oldPump, Pump* newPump);

public:

    /*
    * Crea una piscina
    * @param waterVolume m^3 di acqua
    */
    Pool(float waterVolume);

// set variabili 

    void setRemainingFilteringTime(int remainingMinutes);

// set sensori

    void setChlorineSensor(WaterSensor* sensor);
    void setPhSensor(WaterSensor* sensor);
    void setWaterLevelSensor(WaterSensor* sensor);
    void setWaterTemperatureSensor(WaterSensor* sensor);

// set pompe

    void setChlorinePump(Pump* pump);
    void setPhPlusPump(Pump* pump);
    void setPhMinusPump(Pump* pump);
    void setMasterPump(Pump* pump);
    void setWaterPump(Pump* pump);

// check se sono presenti sensori

    bool hasChlorineSensor();
    bool hasPhSensor();
    bool hasWaterLevelSensor();
    bool hasWaterTemperatureSensor();

// get variabili

    float getWaterVolume();
    float getRemainingFilteringTime();

// get valori misurati da sensori

    float getWaterChlorine();
    float getWaterLevel();
    float getWaterPh();
    float getWaterTemperature();

// get pompe

    Pump* getChlorinePump();
    Pump* getPhPlusPump();
    Pump* getPhMinusPump();
    Pump* getMasterPump();
    Pump* getWaterPump();

// logica

    /*
    * Aggiorna lo status dell'acqua della piscina utilizzando  
    * i sensori disponibili
    */
    void updateWaterStatus();

    /*
    * Calcola il tempo che impiega la pompa della piscina a 
    * filtrare tutta l'acqua 1 volta
    * @return minuti: int
    */
    int calculateRecirculationMinutes();


// ------- DEVZONE ------- // 

    /*
    * Modifica questa funzione in pool.cpp per eseguire un test personalizzato
    */
    void test();
};

#endif
