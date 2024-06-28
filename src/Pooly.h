#ifndef POOLY_H
#define POOLY_H
/**
 * Numero di segmenti in cui è diviso il giorno.
 *
 * Questa costante definisce il numero di segmenti in cui viene suddiviso il giorno,
 * utile per la pianificazione e gestione delle attività della piscina.
 */

// Lunghezza storico delle misurazioni della piscina da tenere in memoria
const int POOLMEMORY= 4;

// Il giorno è diviso in 96 parti, una ogni 15 min
const int DAYSEGMENTS= 96;

#include "objects/Pool.h"
#include "objects/PoolGuardian.h"
#include "objects/WaterSensor.h"
#include "objects/Pump.h"

#endif