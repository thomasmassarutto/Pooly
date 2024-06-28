#ifndef POOLGUARDIAN_H
#define POOLGUARDIAN_H

#include <Arduino.h>

#include "Pooly.h"  

class PoolGuardian {
private:
/*
    rappresentano "quanto conviene" attivare le pompe in un momento della giornata
    la giornata è divisa in trance da 15 minuti
    deve essere aggiornato 1 sola volta al giorno 
*/
   float _electricEfficiencyPoints[DAYSEGMENTS];

   float _targetPh= 7.2; // ph ideale
   float _phDelta= 0.2; // variazione +- tollerata del ph
   float _targetChlorine= 0; // @todo capire come gestire cloro

    /*
    * Grammi ogni 100 m^3 di acqua per alzare il ph di 0,1   
    */
    float _standardDosePhPlus= 300;
    /*
    * Grammi ogni 100 m^3 di acqua per abbassare il ph di 0,1
    */
    float _standardDosePhMinus= 800;

    void emergencyLowWater(Pool& pool);
    /*
    * Dato un volume di liquido da spostare e la portata di una pompa
    * calcola quanto tempo in millisecondi questa pompa deve restare accesa 
    * @param chemicalVolume: volume da disperdere in acqua m^3
    * @param pumpFlow: portata della pompa m^3/h
    * @return millisecondi: float
    */
    float calculatePumpTime(float chemicalVolume, float pumpFlow);

    /*
    * 
    * calcola quanti m^3 di liquido dovranno essere aggiunti per fare in modo di
    * tornare alla situazione ottimale
    * @param waterVolume: soluzione da correggere
    * @param standardDose: **grammi** di correttore da aggiungere ogni 100 m^3 di acqua per correggere di 0,1 unità la soluzione
    * @param phMeasure: livello ph attuale 
    * @return m^3: float
    * 
    * @note Supponendo che la densità del correttore sia 1 kg = 1 L
    */
    float calculatePhVolumeCorrector(float waterVolume, float standardDose, float phMeasure);

public:

    /*
    * Controlla i valori di ph, cloro e livello acqua di una piscina
    * @attention Bloccante per ora
    */
    void checkPool(Pool& pool);

    /*
    * controlla il funzionamento del motore stepper che andrà a srotolare 
    * la cover della piscina in modo da coprirla 
    */
    void coverPool();
    
    /*
    * controlla il funzionamento del motore stepper che andrà ad arrotolare 
    * la cover della piscina in modo da scoprirla 
    */
    void unCoverPool();
    /*
    Da chiamare 1 volta ogni 24 ore.
    Calcola quanto convenga ad ogni segmento della giornata quanto 
    convenga tenere accesa la pompa della piscina.
    Utilizza chiamate API a servizi di meteo.
    */
    void updateDaySchedule();
    void updateFiltrationTime(Pool& pool, float minutes);
    void winterMode(Pool& pool);
};

#endif