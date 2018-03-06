#include "math.h"
#include "fileio.h"
#include "suntans.h"
#include "initialization.h"

REAL ReturnDepth(REAL x, REAL y){
  return 20;
}
REAL ReturnFreeSurface(REAL x, REAL y, REAL d){
  return 0;
}

REAL ReturnSalinity(REAL x, REAL y, REAL z){
  return 0;
}

REAL ReturnTemperature(REAL x, REAL y, REAL z, REAL depth){
  return 1;
}

REAL ReturnHorizontalVelocity(REAL x, REAL y REAL n1, REAL n2, REAL z){
  return 0;
}
REAL ReturnSediment(REAL x, REAL y, REAL z, int sizeno){
  return 0;
}

REAL ReturnBedSedimentRatio(REAL x, REAL y, int layer, int sizeno, int nsize){
  return 0;
}
