/* parameters and types' definitions for 2dc_par */

/* maximum number of equations */
#define MAXEQ 4
/* maximum number of elements to which may belong a single vertex node */
#define MAXELNO 10
/* base for encoding boundary conditions numbers */
#define BCBASE 10
/* maximal values for allocating arrays of pointers */
/* this values cannot be exceeded during computations !!! */
#define MAXNO 1000000
#define MAXEL 1000000
/* maximal number of vertex nodes (vertices) of an element
3 - triangles only, 4 - triangles and quadrilaterals*/
#define MAXVNOEL  3
/* maximal order of elements */
#define MAXORDER  8
/* maximal number of nodes in an element*/
#define MAXNODEL 55 /* up to third order triangles */
/* maximal number of real unconstrained nodes in an element*/
#define MAXRNOEL 55 

/*parameter used as maximal number of processors in parallel
computations*/
#define PRBASE 33

/*
Explanation of NODES structure:
type: (for all types type = -type means constrained node)
      0 - free space
      1 - vertex node
      2 - midside node
      3 - middle node
glnr   - global number (for use in a parallel version of the code)
elems  - all elements to which belongs i-th node
	 (for free space elems[0]=0, elems[1] is a pointer
	 to the next free space)
x,y    - degrees of freedom for physical coordinates
u0, u1, u2 - dof's for components of solution vector, usually:
         u0 - at the end of the previous time step
         u1 - at the beginning of the current time step 
         ui - during iterations at the current time step
         u2 - at the end of the current time step (or after
              one iteration of iterative solver)
!!! particular components may be commented out for different versions
of the code !!!
*/
typedef struct {
  int type;
  int glnr;
  int *elems;
  double x;
  double y;
  double u0[MAXEQ];
  double u1[MAXEQ];
  double *ui;
  double u2[MAXEQ];
  } NODES;

/*
Explanation of ELEMS structure:
  type - element type (for active elements>0, for inactive <0)
         1 - isoparametric triangle	 
	 for free space: 0
  fath - for active elements: the father's number
	 for inactive elements: the father's number
	 for free space: the pointer to the next free space
  fson - first son number
  elbc - encoded BC types:
	elbc=0 - no BC,
	elbc>0 - ielbc= bc3 + bc2*BCBASE + bc1*BCBASE^2
	decoding pattern:
	  bc3=(pelem[nel]->elbc)%BCBASE;
          bc2=((pelem[nel]->elbc)/BCBASE)%BCBASE;
	  bc1=(((pelem[nel]->elbc)/BCBASE)/BCBASE)%BCBASE;
  where bc1, bc2, bc3 - boundary conditions for subsequent
  sides of the element
  order - array storing orders for sides and interior
  nodes - node numbers, nodes[i]<0 - constrained node
         it is assumed that nodes are specified in counter-
         clockwise order !!! (for free spaces nodes is NOT allocated)
*/
typedef struct {      
  int type;
  int fath;
  int sons[4];
  int elbc;
  int order[MAXVNOEL+2];
  int *nodes;
  } ELEMS;

