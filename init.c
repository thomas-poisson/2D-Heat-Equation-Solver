#include<stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include"decl.h"

int max(int a, int b){
	int res;
	if (a>b){res = a;}
	else {res = b;}
	return res;
}

void init_matrix(double ** u, int len, int height, double dx, double dy){
	//initialisation de l'ensemble de la matrice au temps initial
	init_boundary(u, len, height, dx, dy, 0);
	init_time(u, len, height, dx, dy);
}

void init_boundary(double ** u, int len, int height, double dx, double dy, double t){
	//initialisation des bords
	#ifdef USE_OMP_BOUNDARY
	#pragma omp for
	#endif
	for (int i=0; i<len; i++){
		u[i][0] = temp_lower(i, len, height, dx, dy, t);
		u[i][height-1] = temp_upper(i, len, height, dx, dy, t);
	}
	#ifdef USE_OMP_BOUNDARY
	#pragma omp for
	#endif
	for (int i=0; i<height; i++){
		u[0][i] = temp_left(i, len, height, dx, dy, t);
		u[len-1][i] = temp_right(i, len, height, dx, dy, t);
	}
}

void init_time(double ** u, int len, int height, double dx, double dy){
	//initialisation au temps t=0 du centre de la matrice
	#ifdef USE_OMP_BOUNDARY
	#pragma omp for schedule(static) collapse(2)
	#endif
	for (int i=1; i<len-1; i++){
		for(int j=1; j<height-1; j++){
			u[i][j] = temp_init(i, j, len, height, dx, dy);
		}
	}
}

//fonctions definissant les conditions initiales et aux limites du probleme

double temp_upper(int i, int len, int height, double dx, double dy, double t){
	double Dy = (len-1)*dy;
	return sin(2*M_PI*(i*dy)/Dy);
}
double temp_lower(int i, int len, int height, double dx, double dy, double t){
	return 0;
}

double temp_left(int i, int len, int height, double dx, double dy, double t){
	return 0;
}

double temp_right(int i, int len, int height, double dx, double dy, double t){
	return 0;
}

double temp_init(int i, int j, int len, int height, double dx, double dy){
	return 0;
}
