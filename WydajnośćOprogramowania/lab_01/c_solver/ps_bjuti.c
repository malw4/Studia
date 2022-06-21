/*************************************************************
File contains procedures:
  findpat1 - to create a patch of elements with 1 internal node 
  assebj - to compute element stiffness matrices and assembling
           them into patch stifness matrices  

Required routines:
  numelno, celm - pf_cons.c
  put_list, chk_list, ludcmp, lusol - in po_util.c

Included files:
  ./typedef.d
  ./declar.d
  ./patches.d
*************************************************************/

#include<stdlib.h>
#include<stdio.h>

/* definitions and declarations of global types and variables */
#include "./typedef.d"
#include "./declar.d"
/*definition of type PATCHES*/
#include "./patches.d"

/*---------------------------------------------------------
findpat1 - constructing a patch for a given node,
patch consist of all elements sharing the node.
---------------------------------------------------------*/
void findpat1(Nod0, patch)
int Nod0;   /* a corner node for which a patch is constructed */
PATCHES *patch;   /* pointer to the patch structure */
{
/*called functions */
extern int put_list();
extern int chk_list();
extern int nrnostel();
/* local  variables */
/* temporary storage for elements and nodes in the patch */
int Elloc[MAXELPA], Nolocac[MAXNOPA], Nolocin[MAXNOPA];
/* local auxiliary  variables */
int inol, inoll, iell, nrell, nrnoacl, nrnoinl, ibc[3];
int i, j, ipr, iprint, iel, nel, nelf, nels, ino, nno, iaux;
int ihono1,ihono2,in1,in2,i1,i2,k,nrnost;
int ifath,inf1,inf2,ihonof1,ihonof2;

iprint=1;

/* initiate Elloc */
for(i=0;i<MAXELPA;i++) Elloc[i]=0;
/* initiate Noloc's */
for(i=0;i<MAXNOPA;i++) Nolocac[i]=0;
for(i=0;i<MAXNOPA;i++) Nolocin[i]=0;
/*kbw
printf("Node %d\n",Nod0);
/*kbw*/
/* in a loop over all elements sharing the node Nod0*/
nrell=0;
for(iell=0;iell<MAXELNO&&(iel=pnode[Nod0]->elems[iell])!=0;iell++){
/*put element on a list of patch elements*/
  i=put_list(iel,Elloc,MAXELPA);
  if(i==0) nrell++;
  if(i<0){
    printf("Too much elements in a patch for node %d\n",Nod0);
    exit(1);
    }
/*for each element vertex node*/
  for(inol=0;inol<3;inol++){
    if(pelem[iel]->nodes[inol]<0){
/* if node is constrained then find element's father and add 
to the patch those of its sons which are not refined and .... */
      nelf=pelem[iel]->fath;
      for(i=0;i<=3;i++){
        nels=pelem[nelf]->sons[i];
        if(pelem[nels]->type==1 && nels != iel){
          for(j=0;j<3;j++){
/* ... have at least one constrained node */
	    if(pelem[nels]->nodes[j]<0){  
	      ipr=put_list(nels,Elloc,MAXELPA);
	      if(ipr==0) nrell++;
	      if(ipr<0){
	        printf("Too much elements in a patch for node %d\n",Nod0);
                exit(1);
              }
	      break;
              }
	    }
	  }
        }
      }
    }
  }
patch->Nreles=nrell;
/* allocate space for elements in a patch */
patch->Eles = (int *)malloc(nrell*sizeof(int));
if(patch->Eles==NULL){
  printf("Not enough space for elements in the patch for node %d\nExiting !!!\n",Nod0);
  exit(1);
  }
for(iell=0;iell<nrell;iell++){patch->Eles[iell]=Elloc[iell];}
/* having found all elements in the patch - the list of
nodes of the patch is created with indication whether
the node is an inner or boundary node */
Nolocac[0]=Nod0;
nrnoacl=1;
nrnoinl=0;
for(iell=0;iell<nrell;iell++){
  iel=Elloc[iell];
/*kbw
  if(iprint==1){
    printf("Before updating : element %d\n",iel);
    printf("Its nodes: ");
    nrnost=nrnostel(iel);
    for(ipr=0;ipr<nrnost;ipr++){printf("%d ",pelem[iel]->nodes[ipr]);}
    printf("\n");
    printf("%d patch active nodes:",nrnoacl);
    for(i=0;i<nrnoacl;printf(" %d",Nolocac[i++])){}
    printf("\n");
    printf("%d patch inactive nodes:",nrnoinl);
    for(i=0;i<nrnoinl;printf(" %d",Nolocin[i++])){}
    printf("\n");
  }
/*kbw*/
/*in a loop over element vertex nodes*/
  for(inol=0;inol<3;inol++){
/*take an active vertex node different from the central node*/
    if((ino=pelem[iel]->nodes[inol])>0){
      if(ino!=Nod0){
/* check whether on the boundary or inside a patch */
        for(i=0;i<MAXELNO&&(iaux=pnode[ino]->elems[i])!=0;i++){
          if(chk_list(iaux,Elloc,nrell)==0) {
            ino *= -1;
            break;
          }
/*kb! - we take all boundary corner nodes as internal nodes!*/
        }
        if(ino<0) {
          i=put_list(-ino,Nolocin,MAXNOPA);
          if(i==0) {
            nrnoinl++;
          }
        }
        else if(ino>0) {
          i=put_list(ino,Nolocac,MAXNOPA);
          if(i==0) {
            nrnoacl++;
          }
        }
        if(i<0) {
          printf("Too much nodes in a patch for node %d!!!\n",Nod0);
          exit(1);
        }
      }
    }
    else{
      printf("Not an active vertex node. Exiting from findpat !\n");
      exit(1);
    }
  }
/*take into account higher order nodes*/
  if(pelem[iel]->order[0]>1){
/*location of the first higher order node in nodes array*/
    ihono1=3;
/*in a loop over element edges*/
    for(inol=0;inol<3;inol++){
     if((j=pelem[iel]->order[inol+1])>1){
/*location of the last higher order node on the edge in nodes array*/
      ihono2 = ihono1+j-1;
/*take two nodes at the ends of the edge */
      in1=pelem[iel]->nodes[inol];
      in2=pelem[iel]->nodes[(inol+1)%3];
/*when both nodes are real or both are constrained*/
      if(in1*in2>0){
/*check whether they are on the patch boundary*/
        i1=chk_list(in1,Nolocin,MAXNOPA);
        i2=chk_list(in2,Nolocin,MAXNOPA);

/*kbw
if(iprint==1){
  printf("on edge %d - nodes %d %d\n",inol,in1,in2);
}
/*kbw*/

/*when both nodes are on the outer edge of the patch*/
        if(i1>0&&i2>0){
/*rewrite edge nodes to inactive nodes array*/
          for(inoll=ihono1;inoll<ihono2;inoll++){
            if((nno=pelem[iel]->nodes[inoll])>0){
              i=put_list(nno,Nolocin,MAXNOPA);
              if(i==0) {
                nrnoinl++;
              }
              if(i<0) {
                printf("Too much nodes in a patch for node %d!!!\n",Nod0);
                exit(1);
              }
            }
          }
/*kbw
if(iprint==1){
  printf("adding inactive nodes from %d to %d\n",ihono1,ihono2);
    printf("%d patch active nodes:\n",nrnoacl);
    for(i=0;i<nrnoacl;printf(" %d",Nolocac[i++])){}
    printf("\n");
    printf("%d patch inactive nodes:\n",nrnoinl);
    for(i=0;i<nrnoinl;printf(" %d",Nolocin[i++])){}
    printf("\n");
}
/*kbw*/
        }
/*when the edge is internal*/
        else{
/*rewrite edge nodes to active nodes array*/
          for(inoll=ihono1;inoll<ihono2;inoll++){
            if((nno=pelem[iel]->nodes[inoll])>0){
              i=put_list(nno,Nolocac,MAXNOPA);
              if(i==0) {
                nrnoacl++;
              }
              if(i<0) {
                printf("Too much nodes in a patch for node %d!!!\n",Nod0);
                 exit(1);
              }
            }
          }
/*kbw
if(iprint==1){
  printf("adding active nodes from %d to %d\n",ihono1,ihono2);
    printf("%d patch active nodes:\n",nrnoacl);
    for(i=0;i<nrnoacl;printf(" %d",Nolocac[i++])){}
    printf("\n");
    printf("%d patch inactive nodes:\n",nrnoinl);
    for(i=0;i<nrnoinl;printf(" %d",Nolocin[i++])){}
    printf("\n");
}
/*kbw*/
        }
      }
      else{
/*one of the vertices is constrained*/
/*looking for the father*/
        ifath=pelem[iel]->fath;
/*it is enough to check only fourth son*/
        if(iel==pelem[ifath]->sons[3]){
/*father nodes are: inol and (inol+1)%3*/
          inf1=pelem[ifath]->nodes[inol];
          inf2=pelem[ifath]->nodes[(inol+1)%3];
/*if both father's nodes are on the patch boundary*/
          i1=chk_list(inf1,Nolocin,MAXNOPA);
          i2=chk_list(inf2,Nolocin,MAXNOPA);
          if(i1>0&&i2>0){
/*find suitable father's midside nodes and add to the patch*/
            ihonof1=3;
            for(iaux=0;iaux<inol;iaux++){
              ihonof1+=pelem[ifath]->order[inol]-1;
            }
            ihonof2=ihonof1+pelem[ifath]->order[inol]-1;
/*rewrite father edge nodes to active nodes array*/
            for(inoll=ihonof1;inoll<ihonof2;inoll++){
              if((nno=pelem[ifath]->nodes[inoll])>0){
                i=put_list(nno,Nolocin,MAXNOPA);
                if(i==0) {
                  nrnoinl++;
                }
                if(i<0) {
                  printf("Too much nodes in a patch for node %d!!!\n",Nod0);
                   exit(1);
                }
              }
            }
          }
        }
      }
      ihono1 = ihono2;
     }
    }
/*now the middle nodes*/
    if((k=pelem[iel]->order[4])>2){
      ihono2 = ihono1+(k-1)*(k-2)/2;
/*rewrite middle nodes to active nodes array*/
      for(inoll=ihono1;inoll<ihono2;inoll++){
        if((nno=pelem[iel]->nodes[inoll])>0){
          i=put_list(nno,Nolocac,MAXNOPA);
          if(i==0) {
            nrnoacl++;
          }
          if(i<0) {
            printf("Too much nodes in a patch for node %d!!!\n",Nod0);
            exit(1);
          }
        }
      }
    }
  }
/*kbw
  if(iprint==1){
    printf("\nAfter updating\n");
    printf("%d patch active nodes:",nrnoacl);
    for(i=0;i<nrnoacl;printf(" %d",Nolocac[i++])){}
    getchar();
    printf("%d patch inactive nodes:",nrnoinl);
    for(i=0;i<nrnoinl;printf(" %d",Nolocin[i++])){}
    getchar();
    }
/*kbw*/
}
patch->Nrnoac=nrnoacl;
patch->Nrnoin=nrnoinl;
/* allocate space for nodes in a patch */
patch->Noac = (int *)malloc(nrnoacl*sizeof(int));
if(patch->Noac==NULL){
  printf("Not enough space for active nodes in the patch\nExiting !!!\n");
  exit(1);
  }
patch->Noin = (int *)malloc(nrnoinl*sizeof(int));
if(patch->Noin==NULL){
  printf("Not enough space for inactive nodes in the patch\nExiting !!!\n");
  exit(1);
  }
/* rewrite node numbers to PATCH structure */
for(inol=0;inol<nrnoacl;inol++){
  patch->Noac[inol]=Nolocac[inol];
}
for(inol=0;inol<nrnoinl;inol++){
  patch->Noin[inol]=Nolocin[inol];
}
/*kbw
if(iprint==1){
  printf("Constructed patch for a node %d\n",Nod0);
  printf("Elements: ");
  for(iell=0;iell<nrell;printf(" %d",Elloc[iell++])){}
  printf("\nInternal nodes: ");
  for(inol=0;inol<nrnoacl;printf(" %d",Nolocac[inol++])){}
  printf("\nBoundary nodes: ");
  for(inol=0;inol<nrnoinl;printf(" %d",Nolocin[inol++])){}
  getchar();
  }
/*kbw*/
}

/*---------------------------------------------------------
assebj - to compute element stiffness matrices
and assembling them into patch stifness matrices:
one for dofs inside a patch (Ain) and the second for dofs
inside and on the boundary of a patch (Aib), which in turn
are used to compute LU factorization of Ain, its inverse -
Aii and the product of the inverse and Aib - Aio
---------------------------------------------------------*/

/*maximal number od dofs in a patch is equal to the number
of equations (here used maximal as parameter)
times the maximal number of nodes in a patch*/

void assebj(Indyk,ppatch,nrpa)
/*patch is a pointer to the array of length nrpa of patch structures*/
  PATCHES **ppatch; /*PATCHES structure described at the top of a file*/
  int Indyk,nrpa; /*Indicator who is calling and the total number of patches*/
{
  
  /* structures for element stiffness matrices and load vectors */
  typedef struct{
    /* number of element nodes */
    int nrnoel;
    /* list of element nodes */
    int *lnoel;
    /* element stiffness matrix and load vector*/
    double **Ael;
    double *Rel;
  } ELMATS;
  
  
  /*called functions*/
  extern int numelno();
  extern int celm();
  extern int chk_list();
  extern void ludcmp();
  extern void lusol();
  
  /* number of patches having an element */
  int *nrpael;
  /*maximal numbers of internal DOF's and boundary DOF's for patches*/
  int maxdofpa, maxbdfpa;
  /*pointers to structures with element matrices*/
  ELMATS **Elmat;
  /*pointer to a given patch*/
  PATCHES *patch;
  /* array for pivoting information*/
  int *ips;
  /*numbers of: active/inactive dofs in a patch, dofs in an element*/
  int nrdofpa, nrbdfpa, numdofel;
  /*auxiliary integers*/
  int ino, nno, iel, nel, iell, inol, nnol, ipos1, ipos2, ivar1, ivar2;
  int i, j, kp, ke, lp, le, m, n, ipr, iprint, iaux, ipr1, ipa, icelm;
  /*storage*/
  double stor,storp;
  
  iprint=1;
  
  /* allocate space for pointers to structures with element matrices */
  Elmat = (ELMATS **)malloc((Nmel+1)*sizeof(ELMATS *)); 
  if(Elmat==NULL){
    printf("Not enough space for element matrices\nExiting !!!\n");
    exit(1);
  }  
  /*initialize pointers to stiffness matrices indicating whether
    an element has been considered or not */
  for(iel=1;iel<=Nmel;iel++){
    Elmat[iel] = NULL;
  }
  
  /*vector for storing the number of patches having a given element and not yet condidered*/
  nrpael = (int *)malloc((Nmel+1)*sizeof(int));
  for(iel=1;iel<=Nmel;iel++){nrpael[iel]=0;}
  stor=0;
  
  /* allocate space for pointers to structures with patches' matrices */
  maxdofpa=0;
  maxbdfpa=0;
  for(ipa=1;ipa<=nrpa;ipa++){
    nno=ipa;
    
    /*update information on patches to which elements belong*/
    for(iel=0;iel<ppatch[nno]->Nreles;iel++){
      nel=ppatch[nno]->Eles[iel];
      nrpael[nel]++;
    }
    
    nrdofpa=Nreq*ppatch[nno]->Nrnoac;
    if(nrdofpa>maxdofpa) maxdofpa=nrdofpa;
    nrbdfpa=Nreq*ppatch[nno]->Nrnoin;
    if(nrbdfpa>maxbdfpa) maxbdfpa=nrbdfpa;
    /*allocate space for patch vectors and arrays */
    ppatch[nno]->Ain=(double **)malloc((nrdofpa)*sizeof(double *));
    if(ppatch[nno]->Ain==NULL){
      printf("Not enough space for patch %d\nExiting !!!\n",nno);
      exit(1);
    }  
    for(i=0;i<nrdofpa;i++){
      ppatch[nno]->Ain[i]=(double *)malloc((nrdofpa)*sizeof(double));
      if(ppatch[nno]->Ain[i]==NULL){
	printf("Not enough space for patch %d\nExiting !!!\n",nno);
	exit(1);
      }  
    }
    ppatch[nno]->Aib=(double **)malloc((nrbdfpa)*sizeof(double *));
    if(ppatch[nno]->Aib==NULL){
      printf("Not enough space for patch %d\nExiting !!!\n",nno);
      exit(1);
    }  
    for(i=0;i<nrbdfpa;i++){
      ppatch[nno]->Aib[i]=(double *)malloc((nrdofpa)*sizeof(double));
      if(ppatch[nno]->Aib[i]==NULL){
	printf("Not enough space for patch %d\nExiting !!!\n",nno);
	exit(1);
      }  
    }
    ppatch[nno]->Rin=(double *)malloc((nrdofpa)*sizeof(double));
    if(ppatch[nno]->Rin==NULL){
      printf("Not enough space for patch %d\nExiting !!!\n",nno);
      exit(1);
    }
    /*kbw
      if(iprint==1){
      printf("Allocated space for patch %d\n",ipa);
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
  
  
#pragma omp parallel private (ips, nrdofpa, nrbdfpa, numdofel, ino, nno, iel, nel, iell, inol, nnol, ipos1, ipos2, ivar1, ivar2, i, j, kp, ke, lp, le, m, n, ipr, iprint, iaux, ipr1, ipa, icelm, stor,storp, patch) 
  {
#pragma omp for
    for(ipa=1;ipa<=nrpa;ipa++){
      patch=ppatch[ipa];
      
      /*kbw
	if(iprint==1){
	printf("in patch %d \n",ipa);
	}
	/*kbw*/
      
      
      
      nrdofpa=Nreq*patch->Nrnoac;
      nrbdfpa=Nreq*patch->Nrnoin;
      /* initiate Rin, Ain, Aib */
      for(i=0;i<nrdofpa;i++){
	patch->Rin[i]=0;
	for(j=0;j<nrdofpa;j++){
	  patch->Ain[i][j]=0;
	}
	for(j=0;j<nrbdfpa;j++){
	  patch->Aib[j][i]=0;
	}
      }
      
      /* for each element from the patch */
      for(iell=0;iell<patch->Nreles;iell++){

#pragma omp critical
{
	iel=patch->Eles[iell];
	/* if the element not yet considered*/
	if(Elmat[iel]==NULL){
	  Elmat[iel] = (ELMATS *)malloc(sizeof(ELMATS));
	  if(Elmat[iel]==NULL){
	    printf("Not enough space for element %d matrices\nExiting !!!\n",iel);
	    exit(1);
	  }  
	  /* get the number and list of its real nodes */
	  Elmat[iel]->lnoel = (int *)malloc(MAXRNOEL*sizeof(int));
	  Elmat[iel]->nrnoel=numelno(iel,Elmat[iel]->lnoel,&icelm);
	  numdofel=Nreq*Elmat[iel]->nrnoel;
	  
	}

}

	/* assemble computed or stored Ael and Rel into patch->Ain or patch->Aib and patch->Rin*/
	/* in a loop over all element nodes*/
	for(inol=0;inol<Elmat[iel]->nrnoel;inol++){
	  ino=Elmat[iel]->lnoel[inol];
	  ipos1=chk_list(ino,patch->Noac,patch->Nrnoac);
	  if(ipos1>0){
	    /* the node is an inside node - assemble into patch->Rin */
	    for(ivar1=0;ivar1<Nreq;ivar1++){
	      /*kp,lp-positions in patch matrices, ke,le-positions in element matrices*/
	      kp=(ipos1-1)*Nreq+ivar1;
	      ke=inol*Nreq+ivar1;
	      patch->Rin[kp] += 1.e0;
	    }
	    /*the second loop over element nodes*/
	    for(nnol=0;nnol<Elmat[iel]->nrnoel;nnol++){
	      nno=Elmat[iel]->lnoel[nnol];
	      ipos2=chk_list(nno,patch->Noac,patch->Nrnoac);
	      if(ipos2>0){
		/* the second node is also an inside node - assemble into patch->Ain */
		for(ivar1=0;ivar1<Nreq;ivar1++){
		  /*kp,lp-positions in patch matrices, ke,le-positions in element matrices*/
		  kp=(ipos1-1)*Nreq+ivar1;
		  ke=inol*Nreq+ivar1;
		  for(ivar2=0;ivar2<Nreq;ivar2++){
		    lp=(ipos2-1)*Nreq+ivar2;
		    le=nnol*Nreq+ivar2;
		    patch->Ain[kp][lp] += 1.e-2;
		  }
		}
	      }
	      else{
		ipos2=chk_list(nno,patch->Noin,patch->Nrnoin);
		if(ipos2>0){
		  /* the second node is a boundary node - assemble into patch->Aib */
		  for(ivar1=0;ivar1<Nreq;ivar1++){
		    /*kp,lp-positions in patch matrices, ke,le-positions in element matrices*/
		    kp=(ipos1-1)*Nreq+ivar1;
		    ke=inol*Nreq+ivar1;
		    for(ivar2=0;ivar2<Nreq;ivar2++){
		      lp=(ipos2-1)*Nreq+ivar2;
		      le=nnol*Nreq+ivar2;
		      patch->Aib[lp][kp] += 1.e-2;
		    }
		  }
		}
		else{
		  printf("Element %d node %d - not on the list of patch nodes !\n",iel,ino);
		  exit(1);
		}
	      }
	      /*the end of second loop through nodes*/
	    }
	  }
	  /*the node is not an internal node*/
	  else{
	    ipos2=chk_list(ino,patch->Noin,patch->Nrnoin);
	    if(ipos2>0){
	    }
	    else{
	      printf("Element %d node %d - not on the list of patch nodes !\n",iel,ino);
	      exit(1);
	    }
	  }
	  /*the end of first loop through nodes*/
	}
	
	/*update information on element patches*/
	nrpael[iel]--;
	
	/*if element will not appear in any further patch - deallocate memory*/
	if(nrpael[iel]==0){
	  free((char *)Elmat[iel]->lnoel);
	  free((char *)Elmat[iel]);
	}
	
	/*the end of loop over patch elements*/
      }
      /*the end of loop over all patches*/
    }
    
  }  /* end of parallel region */

  /*after computing all patch matrices free the space for element matrices*/
  free((char *)Elmat);
  free((char *)nrpael);
  
  /*kbw*/
  if(iprint==1)printf("Freed the space for all %d element matrices\n",nel);
  /*kbw*/
  
  
}
  
  
  
  








