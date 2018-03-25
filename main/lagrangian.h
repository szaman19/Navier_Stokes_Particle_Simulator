/*
* Lagrangian Module
*
*/

#ifndef _lagrangian_h
#define _lagrangian_h

#include "phys.h"
#include "particle.h"
// #include "met.h"
// #include "sources.h"
// #include "scalars.h"
// #include "util.h"
// // #include "state.h"
// // #include "physio.h"
// #include "merge.h"
// #include "sendrecv.h"
// #include "mynetcdf.h"
#include "suntans.h"






void NearestVoronoiPoint(particle *part, gridT *grid);
void OutputParticleVariables(particle *p, int n);
/*03/24/18 -- end */

// void MotionEquation(REAL **A, REAL **B, gridT *grid, physT *phys, propT *prop, metT *met, int myproc, MPI_Comm comm);
// void TrialOutput(gridT *grid, physT *phys, propT *prop,int myproc, int numprocs, int blowup, MPI_Comm comm);
void WriteData(REAL *array, int merge, FILE *fid, char *error_message,
		 gridT *grid, int numprocs, int myproc, MPI_Comm comm);
void updateParticlePosition(gridT * grid, physT* phys, particle *part, int n);
#endif
