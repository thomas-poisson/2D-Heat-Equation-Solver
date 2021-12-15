#include <stdio.h>
#include <omp.h>

#include "decl.h"

double ** solve_heat_eq(double **u, int nx, int ny, double dx, double dy, int nt, double dt, double alpha){
	//allocation d'une memoire u_prev de travail temporaire
	double ** tmp;
	double ** u_prev = alloc_matrix(nx, ny);
	init_matrix(u_prev, nx, ny, dx, dy);
	for (int k=1; k<nt+1; k++)
	{
		double t = k*dt;
		#pragma omp parallel
		{	
			init_boundary(u, nx, ny, dx, dy, t);
			solve_time_step(u, u_prev, nx, ny, dx, dy, dt, alpha);
		}
		tmp = u_prev; u_prev = u; u = tmp; //echange de pointeurs
	}
	free_matrix(u_prev, nx, ny);
	return u;
}

void solve_time_step(double **u, double ** u_prev, int nx, int ny, double dx, double dy, double dt, double alpha){
	#pragma omp for schedule(static) collapse(2)
	for (int i=1; i<nx-1; i++){
		for (int j=1; j<ny-1; j++){
			u[i][j] = u_prev[i][j] + alpha*dt * ((1/(dx*dx)) * (u_prev[i+1][j]-2*u_prev[i][j]+u_prev[i-1][j])
												+ (1/(dy*dy)) * (u_prev[i][j+1]-2*u_prev[i][j]+u_prev[i][j-1]));
		}
	}
}