#include<stdlib.h>
#include<stdio.h>
#include <assert.h>

#include"decl.h"

#define INLINE_ALLOC

double ** alloc_matrix(int len, int height){
	//allocation dynamique de memoire pour une matrice len x height

	#ifndef INLINE_ALLOC
	double ** arr = (double**)malloc(len * sizeof(double*));
	assert(arr != NULL);
    for (int i = 0; i < len; i++){
		arr[i] = (double*)malloc(height * sizeof(double));
		assert(arr[i] != NULL);
	}
	#endif

	#ifdef INLINE_ALLOC
	double * varr = (double*)malloc(len * height * sizeof(double));
	double ** arr = (double**)malloc(len * sizeof(double*));
	assert(arr != NULL && varr != NULL);
	for(int i=0; i<len; i++){
		arr[i] = varr + i*height;
	}
	#endif
	return arr;
};

void free_matrix(double ** arr, int len, int height){
	//liberation de la memoire allouee pour une matrice prealablement definine

	#ifndef INLINE_ALLOC
	for (int i = 0; i < len; i++)
        free(arr[i]);
	free(arr);
	#endif

	#ifdef INLINE_ALLOC
	free(arr[0]); free(arr);
	#endif
}

void write_over(double ** arr, double ** arr_tmp, int len, int height){
	//copie du contenu de arr_tmp dans arr
	//fonction non utilisee pour OMP

	#ifdef USE_OMP_COPY
	#pragma omp for schedule(static) collapse(2)
	#endif
	for (int i=1; i<len-1; i++){
		for (int j=1; j<height-1; j++){
			arr[i][j] = arr_tmp[i][j];
		}
	}
}