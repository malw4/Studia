/* maximum number of elements and nodes in a patch */
#define MAXELPA 20
#define MAXNOPA 1000
/* definition of type PATCHES for standard block solvers */
typedef struct {
/* Numbers of and pointers to arrays of subsequent: elements, 
active nodes, inactive (on the boundary of a patch) nodes */
  int Nreles;
  int *Eles;
  int Nrnoac;
  int *Noac; 
  int Nrnoin;
  int *Noin;
/* stiffness matrix for patch internal dofs*/
  double **Ain;
/* matrix of coefficients between patch internal and boundary dofs*/
  double **Aib;
/* RHS vector for Ain*/
  double *Rin;
/* Ain^-1 * Aib */
  double **Aio;
/* Ain^-1 * Rin */
  double *Rir;
  } PATCHES;
