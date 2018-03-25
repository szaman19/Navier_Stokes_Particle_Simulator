#include "phys.h"
#include "met.h"
#include "sources.h"
#include "scalars.h"
#include "util.h"
#include "state.h"
#include "physio.h"
#include "merge.h"
#include "sendrecv.h"
#include "mynetcdf.h"
#include "lagrangian.h"
#include <stdio.h>
/*
 * Function: Write2DData
 * Usage: Write2DData(phys->h,prop->mergeArrays,fid,"Error outputting h data!",grid,numprocs,myproc,comm);
 * -------------------------------------------------------------------------------------------------------
 * Write a 2D array in the pointer *array to the file pointer fid, usually for free-surface data.
 *
 */
void WriteData(REAL *array, int merge, FILE *fid, char *error_message,
		 gridT *grid, int numprocs, int myproc, MPI_Comm comm) {
  int arraySize, writeProc, nwritten;
  REAL *array2DPointer;

  if(merge) {
    MergeCellCentered2DArray(array,grid,numprocs,myproc,comm);

    if(myproc==0) {
      arraySize=mergedGrid->Nc;
      array2DPointer=merged2DArray;
    }
    writeProc=0;
  } else {
    arraySize=grid->Nc;
    array2DPointer=array;
    writeProc=myproc;
  }

  if(myproc==writeProc) {
    nwritten=fwrite(array2DPointer,sizeof(REAL),arraySize,fid);
    if(nwritten!=arraySize) {
      printf("%s",error_message);
      exit(EXIT_WRITING);
    }
  }
  fflush(fid);
}

void TrialOutput(gridT *grid, physT *phys, propT *prop,int myproc, int numprocs, int blowup, MPI_Comm comm){
  printf("%s\n", "Going to look through phys and prop and grid");
	int grid_size = grid->Nc;
	printf("%s : %d\n", "Grid size is", grid_size);
	int grid_layers = grid->Nkmax;
	printf("%s : %d layers \n", "Grid depth is", grid_layers);
	// printf("%s: \n", "Printing depths at each cell" );
	// for(int i = 0; i < grid_size; i++){
	// 	printf("%.1f\n", grid->Nk[i]);
	// }

	printf("%s: \n", "Printing xy coordinates of voronoi points in each cell" );
	FILE * storeData;
	storeData = fopen("TrialData.txt", "a");
	for(int i = 0; i < grid_size; i++){
		// printf("(%.4f,%.4f) \n", grid->xv[i],grid->yv[i]);
		fprintf(storeData, "%.4f,%.4f\n",grid->xv[i],grid->yv[i] );
	}
	fclose(storeData);

	FILE * boundaryNodes;
	boundaryNodes = fopen("BoundaryNodes.txt","a");
	int i;
	for(int iptr = grid->celldist[1]; iptr < grid->celldist[2]; iptr++){
		i = grid->cellp[iptr];
		// printf("(%.4f,%.4f) \n", grid->xv[i],grid->yv[i]);
		fprintf(boundaryNodes, "%.4f,%.4f\n",grid->xv[i],grid->yv[i] );
	}
	fclose(boundaryNodes);
	// printf("%s : \n", "Printing the Surface temperature" );
	// for(int i = 0; i < grid_size;i++){
	// 	printf("%f ", phys->Tsurf[i]);
	// }
	// int  i = 0;
	// int top = 0;
	// printf("%s\n", "Printing surface horizontal velocities");
	// for(int iptr= grid->edgedist[0]; iptr < grid->edgedist[1]; iptr++){
	// 	i = grid->edgep[iptr];
	//  top = grid->ctop[i];
	// 	printf("%.2f ", phys->u[i][top]);
	// }


}

void OutputParticleVariables(particle *p, int n){
	FILE * particleData;
	particleData = fopen("particleData.txt","a");
	fprintf(particleData, "%d\n", n);
	fprintf(particleData, "%.4f,%.4f\n",p->x,p->y);
	fclose(particleData);

}

void updateParticlePosition(gridT * grid, physT* phys, particle *part, int n){
	// printf("Moving Particle: %.4f, %.4f -> \n", part->x, part->y);
	// printf("%s\n","Particle has edges at :");
	// for (int i = 0; );
	part->x = grid->xv[n];
	part->y = grid->yv[n];
	// part->nearest_cell = grid->celldist[n];
	int pointer = grid->cellp[n];
	printf("Double checking pointer correctness: (%.4f, %.4f) == (%.4f,%.4f) \n",
	grid->xv[pointer], grid->yv[pointer], part->x, part->y);

}
