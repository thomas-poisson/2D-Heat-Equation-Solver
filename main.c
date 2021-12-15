#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<omp.h>

#include"decl.h"

int main(int argc, char *argv[]){
	/*
	resolution de l'equation de la chaleur pour une plaque rectangulaire
	ordre de convergence de 1 en temps et de 2 en espace
	parallélisé avec OpenMP (OMP)

	argument 1 : nom du fichier contenant les paramètres physiques de l'étude
	argument 2 : nombre de threads a utiliser
	*/
	
	if (argc !=3) {fprintf(stderr, "Arguments manquants : nom_fichier num_threads");}
	
	char *tmp;
	int numthreads;
	numthreads = atoi(argv[2]);
	omp_set_num_threads(numthreads);
	
	
	//definition des parametres physiques de l'etude
	double alpha; //coefficient de diffusion thermique du milieu
	double Dx, Dy; //dimensions physiques de la plaque
	int nx, ny; //pas de discretisation en espace
	double tmax; //intervalle de temps de l'etude
	int nt2;

	read_file(argv[1], &alpha, &Dx, &Dy, &nx, &ny, &tmax, &nt2);

	double dx = Dx/(nx-1), dy = Dy/(ny-1); //pas de discretisation en espace
	int ntopt = 2*alpha*tmax*(1/(dx*dx) + 1/(dy*dy)) + 10; //calcul du pas de temps en fonction du critere de stabilite CFL
	int nt = max(nt2, ntopt);
	double dt = tmax / (nt-2);
	
	double CFL = alpha*dt*(1/(dx*dx)+1/(dy*dy)); //constante de stabilite CFL
	if (CFL > 0.5) {fprintf(stderr, "CFL=%f, stabilite non assuree\n", CFL);}

	//resolution du probleme
	double ** u = alloc_matrix(nx, ny);
	double time_spent, start;
	start = omp_get_wtime();
	u = solve_heat_eq(u, nx, ny, dx, dy, nt, dt, alpha);
	time_spent = omp_get_wtime() - start;
	
	//ecriture de la solution au temps final
	print_to_file(u, nx, ny, dx, dy, nt, dt, alpha);
	printf("%d %lf\n", numthreads, time_spent);

	free_matrix(u, nx, ny);
}
