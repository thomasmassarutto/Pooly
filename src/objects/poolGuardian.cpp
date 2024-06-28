#include <Arduino.h>

#include "Pooly.h"

// privati

void PoolGuardian::emergencyLowWater(Pool& pool){

}

float PoolGuardian::calculatePumpTime(float chemicalVolume, float pumpFlow){
    float milliseconds= (chemicalVolume * 3600000.0) / pumpFlow;

    return milliseconds;
}

float PoolGuardian::calculatePhVolumeCorrector(float waterVolume, float standardDose, float phMeasure){
    float volume=0.0; // valore da ritornar: m^3
    float gramsForOnePoint= (standardDose * waterVolume)/ 100.0; // modifica di 0,1 il ph nel volume corrente
    float targetPh= this->_targetPh;
    float delta=0.0; // differenza fra ph target e ph misurato
    float gramsNeeded=0.0;  // grammi necessari per modificare il ph dato il volume e il delta

    // il delta deve rimanere sempre positivo
    if (targetPh >= phMeasure){

        delta= targetPh - phMeasure;
    }
    else{

        delta= phMeasure - targetPh;
    } 

    gramsNeeded= delta * gramsForOnePoint;

    volume= gramsNeeded / 1000000.0;
    
    return volume;
}

// pubblici

void PoolGuardian::checkPool(Pool& pool){// @todo: gestire casi ha il sensore, non ha la pompa
    float poolWaterVolume= pool.getWaterVolume();
    
    // Prima controlla che ci sia abbastanza acqua
    if (pool.hasWaterLevelSensor()){

        if (pool.getWaterLevel() < 20){
            this->emergencyLowWater(pool);
        }
    }

    // routine gestione ph

    if (pool.hasPhSensor()){
        float phLevel= pool.getWaterPh();

        Pump* phPlusPump=  pool.getPhPlusPump();
        Pump* phMinusPump=  pool.getPhMinusPump();

        float volumeCorrector= 0.0; // grammi di correttore da aggiungere
        float milliSeconds= 0.0; // millisecondi per cui la pompa dovra rimanere attiva

        float minThresHold= this->_targetPh - this->_phDelta;
        float maxThresHold= this->_targetPh + this->_phDelta;

        if(phLevel > maxThresHold){

            volumeCorrector= calculatePhVolumeCorrector(poolWaterVolume, this->_standardDosePhMinus, phLevel);
            milliSeconds= this->calculatePumpTime(volumeCorrector, phMinusPump->getPumpFlow());

        }else if(phLevel < minThresHold){

            volumeCorrector= calculatePhVolumeCorrector(poolWaterVolume, this->_standardDosePhPlus, phLevel);
            milliSeconds= this->calculatePumpTime(volumeCorrector, phPlusPump->getPumpFlow());
        }
        //@todo finire implementazione accensione pompa
    }



    if (pool.hasChlorineSensor()){
        float chlorineLevel= pool.getWaterChlorine();
        //@todo
    }

}
/*
void PoolGuardian::coverPool(){
        while (this.endButton ==  LOW){
            stepper.cover();
        }
}

void PoolGuardian::unCoverPool(){
    while (this.startButton == HIGH){
        stepper.uncover();
    }
        
}
*/
  
void PoolGuardian::updateDaySchedule(){
        
}
    
void PoolGuardian::updateFiltrationTime(Pool& pool, float minutes){
        
}
    
void PoolGuardian::winterMode(Pool& pool){
        
}
    