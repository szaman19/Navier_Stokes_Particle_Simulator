/*
* Lagrangian Module
*
*/

#ifndef _lagrangian_h
#define _lagrangian_h

#include "phys.h"
#include "met.h"
#include "sources.h"
#include "scalars.h"
#include "util.h"
#include "state.h"


void MotionEquation(REAL **A, REAL **B, gridT *grid, physT *phys, propT *prop, metT *met, int myproc, MPI_Comm comm);
#endif
