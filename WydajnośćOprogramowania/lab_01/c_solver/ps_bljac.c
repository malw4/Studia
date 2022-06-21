/*************************************************************
File contains procedures:
  bljacsol - to solve the problem by means of Block Jacobi solver
  bljacit - to perform one iteration of Block Jacobi or Gauss-Seidel 

Required routines:
  findpat, assebj - in ps_bjuti.c 
  vecnorm - in po_util.c

Included files:
  ./typedef.d
  ./declar.d
  ./patches.d
*************************************************************/

#include<stdlib.h>
#include<stdio.h>
#include<math.h>

/* definitions and declarations of global types and variables */
#include "./typedef.d"
#include "./declar.d"
/*definition of type PATCHES*/
#include "./patches.d"

/* default accutacy of the solver*/
#define EPS 1.0e-12
#define MAXITER 10

/**************************************************************
bljacsol - to solve the problem by means of Block Jacobi solver
***************************************************************/
void bljacsol(Indit)
int Indit;
{
/* called functions */
extern void findpat1();
extern void assebj();
void bljacit();
void bljacit_new();
extern double vecnorm();
/* local  variables */
PATCHES **ppatch;
int nrdofpa, nrbdfpa, maxdofpa, maxbdfpa;
/* local auxiliary  variables */
int iel, nel, ino, nno, ipa, nrpa, nmdofg;
int i, ipr, ipr1, iprint, inol, j;
int ino1,ipos1,ivar1,kg,iter;
/*storage*/
double stor,storp,daux;
/*convergence indicators*/
double error;
/* vectors of unknown for Block Jacobi solver*/
double *uin, *uout;
/*indicator for assembling*/
int Indykas;

iprint=1;

/* allocate space for pointers to patches */
ppatch = (PATCHES **)malloc((Nrno+2)*sizeof(PATCHES *));
if(ppatch==NULL){
  printf("Not enough space for pointers to patches in gmres\nExiting !!!\n");
  exit(1);
  }

/*kbw
if(iprint==1){
  printf("Size of a pointer to patch %d\n",sizeof(PATCHES *));
  printf("Allocated space for %d pointers\n",Nrno+1);
  printf("Size of a structure patch %d\n",sizeof(PATCHES));
  }
/*kbw*/

maxdofpa=0;
maxbdfpa=0;

/* findpat1 - option in which patch consist of all elements
sharing a given active node, number of patches coincides with
the number of active nodes */
nrpa=0;
/* loop over all nodes */
for(ino=1;ino<=Nmno;ino++){
  if(pnode[ino]->type==1){
    nrpa++;
/* old version    nno++; */
    nno=renum[ino];
    /* allocate space for a new patch */
    ppatch[nno] = (PATCHES *)malloc(sizeof(PATCHES));
    if(ppatch[nno]==NULL){
      printf("Not enough space for patch %d\nExiting !!!\n",nno);
      exit(1);
      }
    /* find the patch corresponding to the node ino */
    findpat1(ino, ppatch[nno]);
/*kbw
if(iprint==1){
 printf("Received patch %d for a node %d\n",nno,ino);
 printf("Elements: ");
 for(ipr=0;ipr<ppatch[nno]->Nreles;ipr++){printf(" %d (%d)",ppatch[nno]->Eles[ipr],ppatch[nno]->Eles[ipr]-34);}
 printf("\nActive nodes: ");
 for(ipr=0;ipr<ppatch[nno]->Nrnoac;printf(" %d",ppatch[nno]->Noac[ipr++])){}
 printf("\nInactive nodes: ");
 for(ipr=0;ipr<ppatch[nno]->Nrnoin;printf(" %d",ppatch[nno]->Noin[ipr++])){}
 printf("\n");
 getchar();
 }
/*kbw*/
    }
  }
/*kbw
if(iprint==1){
  printf("Created %d patches, storage %18.9lf MBytes.\n",nrpa,stor);
  }
/*kbw*/

/**************************************************************
assebj - computing of element stiffness matrices
and assembling them into patch stifness matrices:
one for dofs inside a patch (Ain) and the second for dofs
inside and on the boundary of a patch (Aib), which in turn
are used to compute LU factorization of Ain, its inverse -
Aii and the product of the inverse Aii with: Aib giving ppatch[ipa]->Aio
and the vector of RHS Rin giving ppatch[ipa]->Rir;
on output ppatch[ipa]->Aio and ppatch[ipa]->Rir are filled in
**************************************************************/

Indykas=1;
assebj(Indykas,ppatch,nrpa);

/*kbw
if(iprint==1){
for(ipa=nrpa;ipa<=nrpa;ipa++){
 printf("Patch %d\n",ipa);
 printf("Elements: ");
 for(ipr=0;ipr<ppatch[ipa]->Nreles;ipr++){printf(" %d (%d)",ppatch[ipa]->Eles[ipr],ppatch[ipa]->Eles[ipr]-136);}
 printf("\nActive nodes: ");
 for(ipr=0;ipr<ppatch[ipa]->Nrnoac;printf(" %d",ppatch[ipa]->Noac[ipr++])){}
 printf("\nInactive nodes: ");
 for(ipr=0;ipr<ppatch[ipa]->Nrnoin;printf(" %d",ppatch[ipa]->Noin[ipr++])){}
 printf("\nSolution vector for internal nodes and RHS load vector\n");
 for(ipr=0;ipr<Nreq*ppatch[ipa]->Nrnoac;printf(" %18.9lf",ppatch[ipa]->Rir[ipr++])){}
 getchar();
 printf("\nResolved extended stiffnes matrix between active and inactive nodes\n");
 for(ipr=0;ipr<Nreq*ppatch[ipa]->Nrnoin;ipr++){
   for(ipr1=0;ipr1<Nreq*ppatch[ipa]->Nrnoac;ipr1++){
     printf(" %18.9lf",ppatch[ipa]->Aio[ipr][ipr1]);
     }
   printf("\n");
   }
 getchar();
 }
 }
/*kbw*/

nmdofg=Nreq*Nmno;
uin = (double *)malloc((nmdofg)*sizeof(double));
uout = (double *)malloc((nmdofg)*sizeof(double));
for(ino=0;ino<nmdofg;ino++) uin[ino]=uout[ino]=1.0;

/*loop until convergence*/
iter=0;
do{
  /* perform one iteration of Block Jacobi or Gauss-Seidel */
  iter++;
  /* see explanation of variables below in definition of bljacit */
  bljacit(Indit,uin,uout,ppatch,nrpa);
/*  bljacit_new(Indit,uin,uout,ppatch,nrpa,maxdofpa,maxbdfpa); */
  /* compute the error */
  error=0.0;
  for(ino=0;ino<nmdofg;ino++){
    if(fabs(uin[ino]-uout[ino])>error) error=fabs(uin[ino]-uout[ino]);
    }
  if(error>EPS){
    for(ino=0;ino<nmdofg;ino++) uin[ino]=uout[ino];
    }
    printf("Gauss Seidel iteration %d, error %18.9lf\n",iter,error);
}while(error>EPS && iter<MAXITER);



/* do not forget to free any allocated space */
free((char *)uin);
free((char *)uout);
for(i=1;i<=nrpa;i++){
  for(j=0;j<(Nreq*ppatch[i]->Nrnoac);j++){
    free((char *)ppatch[i]->Ain[j]);
    }
  for(j=0;j<(Nreq*ppatch[i]->Nrnoin);j++){
    free((char *)ppatch[i]->Aib[j]);
    }
  free((char *)ppatch[i]->Ain);
  free((char *)ppatch[i]->Aib);
  free((char *)ppatch[i]->Rin);
  free((char *)ppatch[i]->Eles);
  free((char *)ppatch[i]->Noac);
  free((char *)ppatch[i]->Noin);
  free((char *)ppatch[i]);
  }
free((char *)ppatch);
/*kbw*/
if(iprint==1){
  printf("Freed the space for patches\n");
  }
/*kbw*/
}

/**************************************************************
 bljacit - to perform one iteration of Block Jacobi or Gauss-Seidel 
**************************************************************/
/* Indyk = 0/2 - Bl-Jac/Ga-Sei, 0/1 - load/no-load */
/* lu - length of vectors uin and uout */
void bljacit(Indyk,uin,uout,ppatch,nrpa)
int Indyk, nrpa;
double *uin, *uout;
PATCHES **ppatch;
{
int ipa,inol1,inol2,ivar1,ivar2,ipos1,ipos2,ipol1,ipol2;
int ino1,ino2;
int ipr,ipr1,iprint,iaux;
/* local patch vectors of unknows*/
double daux;

iprint=1;

#pragma omp parallel private(ipa,inol1,ino1,ivar1,ipol1,ipos1,daux,inol2,ino2,ipol2,ivar2,ipos2)
//#pragma parallel local(ipa,inol1,ino1,ivar1,ipol1,ipos1,daux,inol2,ino2,ipol2,ivar2,ipos2)
 {
#pragma omp for
//#pragma pfor
   /* loop over all patches */
   for(ipa=1;ipa<=nrpa;ipa++){
     /* loop over all nodes of a patch */
     for(inol1=0;inol1<ppatch[ipa]->Nrnoac;inol1++){
       ino1=ppatch[ipa]->Noac[inol1];
       /* loop over variables */
       for(ivar1=0;ivar1<Nreq;ivar1++){
	 /* position in a patch */
	 ipol1=inol1*Nreq+ivar1;
	 ipos1=(ino1-1)*Nreq+ivar1;
	 daux=0.0;
	 /* in a double loop over all dofs of patch boundary nodes */
	 for(inol2=0;inol2<ppatch[ipa]->Nrnoin;inol2++){
	   ino2=ppatch[ipa]->Noin[inol2];
	   for(ivar2=0;ivar2<Nreq;ivar2++){
	     ipol2=inol2*Nreq+ivar2;
	     ipos2=(ino2-1)*Nreq+ivar2;
	     daux -= uout[ipos2]*ppatch[ipa]->Aib[ipol2][ipol1];
	   }
	 }
	 /* if necessary update uoutp by means of stored RHS */
	 if(Indyk%2<1){
	   daux += ppatch[ipa]->Rin[ipol1];
	 }
	 /* update uout */
	 uout[ipos1] = daux;
       }
     }
   }
 }


}

