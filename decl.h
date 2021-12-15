/*
	Global definitions for omp instruction use
*/
#define USE_OMP_BOUNDARY
#define USE_OMP_COPY

/*
	solve.c
	resolution du probleme 2D de l'equation de la chaleur
*/
double ** solve_heat_eq(double **u, int nx, int ny, double dx, double dy, int nt, double dt, double alpha);
void solve_time_step(double **u, double ** u_tmp, int nx, int ny, double dx, double dy, double dt, double alpha);

/*
	init.c
	initialisation de la matrice en fonctions des conditions limites et initiales
*/
//utilitaire
int max(int a, int b);

//initialisation du probleme
void init_matrix(double ** u, int len, int height, double dx, double dy);
void init_boundary(double ** u, int len, int height, double dx, double dy, double t);
void init_time(double ** u, int len, int height, double dx, double dy);

//conditions aux limites et initiales
double temp_upper(int i, int len, int height, double dx, double dy, double t);
double temp_lower(int i, int len, int height, double dx, double dy, double t);
double temp_left(int i, int len, int height, double dx, double dy, double t);
double temp_right(int i, int len, int height, double dx, double dy, double t);
double temp_init(int i, int j, int len, int height, double dx, double dy);



/*
	alloc.c
	allocation, liberation, affiche de matrice
*/

double ** alloc_matrix(int len, int height);
void free_matrix(double ** arr, int len, int height);
void write_over(double ** arr, double ** arr_tmp, int len, int height);

/*
	IO.c
	allocation, liberation, affiche de matrice
*/

void read_file(char filename[], double * palpha, double * pDx, double * pDy, int *pnx, int * pny, double * ptmax, int * pnt);
void print_to_file(double **u, int nx, int ny, double dx, double dy, int nt, double dt, double alpha);
void print_matrix(double ** arr, int len, int height);