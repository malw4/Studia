/*************************************************************
File contains procedures:
  numelno - to count the number of element real (unconstrained) nodes 
  celm - to compute constrained element stiffness matrix and load vector 
  solco - to compute solution components and nodes coordinates

Required routines:
  put_list, chk_list - in po_util.c
  elem - in pf_elem.c

Included files:
  ./typedef.d
  ./declar.d
*************************************************************/
#include<stdlib.h>
#include<stdio.h>

/* definitions and declarations of global types and variables */
#include "./typedef.d"
#include "./declar.d"

#define ELDOF MAXNODEL*MAXEQ

/*---------------------------------------------------------
numelno - to count the number of element nodes
---------------------------------------------------------*/
int numelno(Nel,Lnoel,picelm)
int Nel,*Lnoel,*picelm;
{
/*called functions*/
extern int put_list();
int i,j,k,ino,nno1,nno2,Nrnoel,incelm,nrvert;

/*set flag for constrained nodes to zero*/
incelm=0;
/*initialize Lnoel */
for(i=0;i<MAXRNOEL;i++) Lnoel[i]=0;

Nrnoel=0;
if(pelem[Nel]->type == 1) nrvert=3;
/*for each element vertex node */
for(i=0;i<nrvert;i++){
  ino=pelem[Nel]->nodes[i];
  if(ino>0){
    j=put_list(ino,Lnoel,MAXRNOEL);
    if(j==0){
/*if the element was just added to the list - increase Nrnoel*/
      Nrnoel++;
      }
    }
  else {
    /*flag up - there are constrained nodes*/
    incelm=1;
    printf("Constrained node - exiting !!!!\n");
    exit(1);
  }
}

/* if element is linear - return */
if(pelem[Nel]->order[0]==1) return(Nrnoel);

/*for each element midside node */
nno1=nrvert-1;
for(i=1;i<=nrvert;i++){
  for(k=0;k<pelem[Nel]->order[i]-1;k++){
    nno1++;
    ino=pelem[Nel]->nodes[nno1];
    if(ino>0){
      j=put_list(ino,Lnoel,MAXRNOEL);
      if(j==0){
/*if the element was just added to the list - increase Nrnoel*/
        Nrnoel++;
        }
      }
    else {
      /*flag up - there are constrained nodes*/
      incelm=1;
      printf("Constrained node - exiting !!!!\n");
      exit(1);
      }
    }
  } 
/*finally middle node */
k=pelem[Nel]->order[nrvert+1];
for(i=0;i<(k-2)*(k-1)/2;i++){
  nno1++;
  ino=pelem[Nel]->nodes[nno1];
  if(ino>0){
    j=put_list(ino,Lnoel,MAXRNOEL);
    if(j==0){
/*if the element was just added to the list - increase Nrnoel*/
      Nrnoel++;
      }
    }
  else {
    /*flag up - there are constrained nodes*/
    incelm=1;
    printf("Constrained node - exiting !!!!\n");
    exit(1);
  }
}


*picelm = incelm;
return(Nrnoel);
}

