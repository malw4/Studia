#include<stdlib.h>
#include<stdio.h>
#include<math.h>

/*definitions of structures: NODES i ELEMS */
#include "./typedef.d"

#define LINE 80

/*maximal number of iterations in the nonlinear algorithm*/
#define MAXITER 100

/* default accuracy for solvers (in time dependent problems)*/
#define DELTA 1.e-12

/* Global variables - explanation in declar.d */
NODES **pnode;
ELEMS **pelem;

int *renum;

int Nrno, Nrel;
int pfno, pfel;
int Nmno, Nmel;
int Nreq;

double xig1[11][11], wag1[11][11];
int sch2[9],npg2[19];
double xig2[3][73][19], wag2[73][19];

int Ntype, Indsol, Nstop, Nadapt, Indgen, Nnopt, istop;
double Epsu, Eta, Eta2, Dtt, Dtime, Dtold, Time, Errconv;
double  Bndata[9][4];

/*the end of variables stored in declar.d*/


/*---------------------------------------------------------
 main - to drive the solution procedure
---------------------------------------------------------*/
main()
{
/* called functions */
/* PROBLEM INDEPENDENT */
extern void dumpin_j();
/*to read and write data structure from and to files*/
extern void renumber();
extern void bljacsol();  
extern void czas(); 
extern void uczas();

/* local auxiliary variables */
char *pans, c;
int i,j,k,iaux,ino,iel,iit;
int iprint,Inadapt,Indyk,Inden,Indit,Ialloc,Irenum;
double daux,cfl,errtime,errmax,erresmax,dif,difx,dify;

/*initialize time measurement*/
czas();

iprint=1;

/*set renumbering indicator to show that nodes should be renumbered*/
renum=NULL;
Irenum=1;

dumpin_j();

      Nstop=1;
      istop=0;

      do{
/*renumber nodes*/
        if(renum==NULL) {
          renum = (int *)malloc((Nmno+1)*sizeof(int));
          if(renum==NULL){
            printf("Not enough space for renumbering nodes\nExiting !!!\n");
            exit(1);
          }
          if(Irenum==1){
            i=0; if(Indsol==1) i=1;
            renumber(i);
            Irenum=0;
          }
          else{
            i=0;
            for(ino=1;ino<=Nmno;ino++){
              if(pnode[ino]->type>0){
                i++;
                renum[ino]=i;
              }
            }
          }           
        }
        else if(Irenum==1) {
          free((char *)renum);
          renum = (int *)malloc((Nmno+1)*sizeof(int));
          if(renum==NULL){
            printf("Not enough space for renumbering nodes\nExiting !!!\n");
            exit(1);
          }
          i=0; if(Indsol==1) i=1;
          renumber(i);
          Irenum=0;
        }

        istop++;
/*using bare  Gauss-Seidel*/
        iaux=2;
        bljacsol(iaux);   



        } while(istop<Nstop);

        printf("Time for solving %d time steps \n",istop);
        uczas();
        czas();
        printf("\n");

if(renum!=NULL) free((char *)renum);

for(i=1;i<=Nmno;i++){
  free((char *)pnode[i]);
  }
free((char *)pnode);
for(i=1;i<=Nmel;i++){
  free((char *)pelem[i]);
  }
free((char *)pelem);

return(0);
}


