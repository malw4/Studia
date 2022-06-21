/* Explanation of NODE and ELEMENTS variables
pnode - pointer to array of pointers to structures NODES
        ( pnode[i] - pointer to i-th node)
pelem - pointer to array of pointers to structures ELEMS
        ( pelem[i] - pointer to i-th element)
*/
extern NODES **pnode;
extern ELEMS **pelem;

/*Global array for storing node numbers used for renumbering*/
extern int *renum;

/*
Explanation of numbers:
Nrno - number of nodes
Nrel - number of elements
Nreq - number of equations
*/
extern int Nrno;
extern int Nrel;
extern int Nreq;
/*
Explanation of pointers:
pf.. - pointer to first free entry
Nm.. - maximal initialized index for arrays of pointers 
*/
extern int pfno;
extern int pfel;
extern int Nmno;
extern int Nmel;

/*
Explanation of integration parameters:
xig1[k], wag1[k] - coordinates and weights for k-th 
1D Gaussian integration (exact for polynomials of order 2*k+1)
npg2[k] - number of gaussian points for k-th integration scheme
[k = (order of polynomials integrated exactly - 1)]
xig2, wag2 - coordinates and weights for 2D Gaussian integration
*/

extern double xig1[11][11];
extern double wag1[11][11];
extern int sch2[9];
extern int npg2[19];
extern double xig2[3][73][19];
extern double wag2[73][19];


/*
Explanation of control variables:

Nnopt   - type of the problem, each problem can have an individual 
          number and all problems are grouped into:
               stationary flows - Nnopt<100, 
               nonstationary flows - Nnopt<200,
          plus possibly: shalow water flows, Laplace's equation, etc.)
Ntype   - type of the algorithm in groups:
               linear implicit: TG, SUPG, etc. - Ntype < 100
               nonlinear implicit - Ntype < 200
               explicit - Ntype < 300
Indsol  - type of the solver (PCG, GMRES)

Nadapt  - time steps interval between adaptation
Indgen  - maximum generation level (initial mesh - generation 0 )
Nnopt   - optimal number of nodes to control adaptations
Epsu    - error level to control adaptations

Eta     - first coefficient of the method
Eta2    - second coefficient of the method

Nstop   - number of time steps to stop
istop   - current time step number
Dtt     - initial time step (if > 0.0999 it denotes CFL constant)
Dtime   - current time step
Dtold   - previous time step
Time    - current time
Errconv  - error level indicating convergence

Bndata  - array of vectors for boundary conditions
*/

extern int       Nnopt, Ntype, Indsol, Nadapt, Indgen, Nstop, istop;
extern double    Epsu, Eta, Eta2, Dtt, Dtime, Dtold, Time, Errconv;
extern double    Bndata[9][4];


