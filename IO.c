#include<stdio.h>
#include<stdlib.h>
#include <assert.h>

void read_file(char * filename, double * palpha, double * pDx, double * pDy,
 int *pnx, int * pny, double * ptmax, int * pnt){
	int maxlength = 50;
	char tmp[maxlength];	
	
	FILE *fp;
	fp = fopen(filename, "r");
	assert(fp!=NULL);
	fscanf(fp, "%lf", palpha);
	fscanf(fp, "%lf", pDx);
	fscanf(fp, "%lf", pDy);
	fscanf(fp, "%d", pnx);
	fscanf(fp, "%d", pny);
	fscanf(fp, "%lf", ptmax);
	fscanf(fp, "%d", pnt);
	fclose(fp);
}

void print_to_file(double **u, int nx, int ny, double dx, double dy,
					int nt, double dt, double alpha)
{	
	FILE * fout = fopen("./output.txt", "w");
	assert(fout != NULL);
	double tf = (nt-2) * dt;
	fprintf(fout, "%d %d %e %e %e %e", nx, ny, dx, dy, tf, alpha);
	for(int i = 5; i<ny; i++){
		fprintf(fout, "0 ");
	}
	fprintf(fout, "\n");
	for (int i=0; i<nx; i++){
		for (int j=0; j<ny; j++){
			fprintf(fout, "%f ", u[i][j]);
		}
		fprintf(fout, "\n");
	}
	fclose(fout);
}

void print_matrix(double ** arr, int len, int height){
	for (int i=0; i<len; i++){
		for (int j=0; j<height; j++){
			printf("%.2e ",arr[i][j]);
		}
		printf("\n");
	}
}