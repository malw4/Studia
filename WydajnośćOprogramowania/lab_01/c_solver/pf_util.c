/*************************************************************
File contains procedures:
  findgen - to find generation level for an element 
  chck_el - to check whether the element is wlle defined 
  neighb - to find nieghbours of an element
  renumber - to renumber nodes in non-optimal way
  setint - to initiate intagration constants
  comhgrad - to compute a gradient for linear elements

Required procedures:
  solco - in pf_cons.c
  put_list, del_list - in po_util.c

Included files:
  ./typedef.d
  ./declar.d
*************************************************************/

#include<stdlib.h>
#include<stdio.h>
#include<math.h>

/* definitions and declarations of global types and variables */
#include "./typedef.d"
#include "./declar.d"

/*---------------------------------------------------------
nrnostel - to find the number of standard nodes for an element
---------------------------------------------------------*/
int nrnostel(Nel)
int Nel;
{
int i, nrnost;

nrnost=pelem[Nel]->order[1]+pelem[Nel]->order[2];
i=pelem[Nel]->order[4];
nrnost+=(i-1)*(i-2)/2+pelem[Nel]->order[3];

return(nrnost);
}


/*---------------------------------------------------------
findgen - to find generation level for an element 
---------------------------------------------------------*/
int findgen(El)
int El;
{
int findgen();
int gen;

if(pelem[El]->fath == 0){
  return(0);
  }
else
  {
  gen = 1 + findgen(abs(pelem[El]->fath));
  }
return(gen);
}


/*--------------------------------------------------------
neighb - to find nieghbours of an element
--------------------------------------------------------*/
#define MXCND 50

void neighb(Nel, Neig, Neigsid)
int Nel, *Neig, *Neigsid;
{
extern int put_list();

int elcand[MXCND];
int ino,iel,nno,ncom,ifath;
int isid1,ino1,nno1,isid2,ino2,nno2;
int io1,no1,io2,no2;
int i,j,iprint,ipr;

iprint=1;


for(i=0;i<6;i++) Neig[i]=0;
for(i=0;i<6;i++) Neigsid[i]=0;
for(i=0;i<MXCND;i++) elcand[i]=0;

for(nno=0;nno<3;nno++){
  ino=pelem[Nel]->nodes[nno];
  if(ino<0){
    printf("Constrained node - exiting !!!!\n");
    exit(1);
  }
  else{
    for(iel=0;iel<MAXELNO;iel++){
      if((j=pnode[ino]->elems[iel])!=0) {
        if(j!=Nel) put_list(j,elcand,MXCND);
      }
    }
  }
}
/*add also the 4th brother of the family*/
if((ifath=pelem[Nel]->fath)!=0){
  j=pelem[ifath]->sons[3];
  if(pelem[j]->type>0&&j!=Nel) put_list(j,elcand,MXCND);
}


/*kbw
 if(Nel==219||Nel==83){
if(iprint==1){

  printf("For element %d, candidates for neighbours are:\n",Nel);
  for(ipr=0;ipr<MXCND;ipr++){
    printf("%d  ",elcand[ipr]);
  }
  printf("\n");
  getchar();
}
}
/*kbw*/

for(isid1=0;isid1<3;isid1++){
  ino1=io1=pelem[Nel]->nodes[isid1];
  ino2=io2=pelem[Nel]->nodes[(isid1+1)%3];
  for(iel=0;iel<MXCND;iel++){
    if(elcand[iel]==0) break;
    for(isid2=0;isid2<3;isid2++){
      nno1=no1=pelem[elcand[iel]]->nodes[isid2];
      nno2=no2=pelem[elcand[iel]]->nodes[(isid2+1)%3];
      ncom=0;

      if(ino1*ino2>0){
        if(nno1*nno2>0){
          if(ino1==nno2&&ino2==nno1){
            Neig[2*isid1]=elcand[iel];
            Neig[2*isid1+1]=elcand[iel];
            Neigsid[2*isid1]=isid2;
            Neigsid[2*isid1+1]=isid2;
          }
        }
        else{
          printf("Constrained node - exiting !!!!\n");
          exit(1);
        }
      }
      else{
        printf("Constrained node - exiting !!!!\n");
        exit(1);
      }
/*^end of considering different cases*/
    }
/*^end of loop over sides2*/
  }
/*^end of loop over candidates*/
} 
/*^end of loop over sides1*/


/*kbw
 if(Nel==219||Nel==83){
if(iprint==1){

  printf("For element %d, neighbours are:\n",Nel);
  for(ipr=0;ipr<6;ipr++){
    printf("neighbour %d   side %d\n",Neig[ipr],Neigsid[ipr]);
  }
  printf("\n");
printf("Nodes %d %d %d\n",pelem[Nel]->nodes[0],pelem[Nel]->nodes[1],pelem[Nel]->nodes[2]);
  getchar();
}
}
/*kbw*/



}

                       
/*---------------------------------------------------------
renumbering scheme
---------------------------------------------------------*/
#define FRO 0.3

void renumber(Indyk)
/*Indyk=1 - renumber all nodes, else - vertices only*/
int Indyk;
{
extern int put_list();
extern int del_list();
int ino,inol,iel,iell,ngno,ngel,nmnof,pnof,nrnof,nrnost,Nmax;
int i,j,k,l,m,iaux;
int iprint,ipr;
/*arrays for considered elements and nodes in the front*/
int *loel,*front;

iprint=0;

printf("\nRenumbering nodes !!!\n\n");

/*allocate the space for renumbering array*/
nmnof = FRO*Nrno ;
front = (int *)malloc((nmnof)*sizeof(int));
loel = (int *)malloc((Nmel+1)*sizeof(int));
if(front==NULL||loel==NULL){
  printf("Not enough space in renumbering scheme\nExiting !!!\n");
  exit(1);
  }
/*initializing arrays*/
for(iaux=0;iaux<=Nmno;iaux++){renum[iaux]=0;}
for(ino=0;ino<nmnof;ino++){front[ino]=0;}
for(ino=1;ino<=Nmel;ino++){loel[ino]=0;}

/*default front*/
nrnof=1;front[0]=1;
/* global number of considered nodes */
ngno=0; 
/*number of nodes to be considered: nrno - for all nodes renumbering,
somo smaller number for renumbering of vertices only*/
Nmax=Nrno;
pnof=0; /* the pointer to the next node in the front */
/*until all nodes are considered...*/
while(ngno<Nmax){
/* pick the next node from the front and advance the pointer*/
    ino=front[pnof++];
    if(ino==0){
      printf("The end of front before all nodes have been distributed !\n");
      exit(1);
      }
/* check whether the node should be deleted from the front */
    m=0;
    for(l=0;l<MAXELNO&&(ngel=pnode[ino]->elems[l])!=0;l++){
      if(loel[ngel]==0){
/* if there is at least one element sharing the node
and not yet considered then break*/
	m=1;
	break;
        }
      }
/* if all elements belong already to the subdomain delete the node
from the front */
    if(m==0){
      k=del_list(ino,front,nmnof);
      if(k>0){
        nrnof--;
/* deletion succesfull - we check whether the pointer should be moved */
        if(k<=pnof) pnof--;
        }
      }
    if(renum[ino]==0){
      ngno++;
      renum[ino]=ngno;
      }
/*kbw
if(iprint==1){
  printf("The front after updating 1:\n");
  for(ipr=0;ipr<nrnof;ipr++){printf("%d ",front[ipr]);}
  printf("\n");
  printf("Now pointer %d points to node %d\n",pnof,front[pnof]);
  getchar();
  }
/*kbw*/
/* for each element sharing the node */
    for(iell=0;iell<MAXELNO&&(iel=pnode[ino]->elems[iell])!=0;iell++){
      if(loel[iel]==0) {
        loel[iel]=1;
/* if the element was not on the list yet */
/*compute the number of standard lement nodes*/
        nrnost=nrnostel(iel);
/*kbw
if(iprint==1){
  printf("In element %d (for node %d)\n",iel,ino);
  printf("Element nodes :");
  for(ipr=0;ipr<nrnost;ipr++) printf("%d  ",pelem[iel]->nodes[ipr]);
  printf("\n");
  getchar();
  }
/*kbw*/
/* for each of its vertex nodes */
	for(inol=0;inol<3;inol++){
	  iaux=pelem[iel]->nodes[inol];
/* if node is not constrained */
	  if(iaux>0){
/* we check whether it should be added or deleted from the front */
            m=0;
	    for(l=0;l<MAXELNO&&(ngel=pnode[iaux]->elems[l])!=0;l++){
              if(loel[ngel]==0){
/* if there is at least one element sharing the node
and not yet considered add the node to the front and break*/
                if(renum[iaux]==0){
	       	  k=put_list(iaux,front,nmnof);
		  if(k==0) {
		    nrnof++;
		  }
                }
                m=1;
	        break;
              }
            }
/* if all elements belong already to the subdomain delete the node
from the front */
	    if(m==0){
	      k=del_list(iaux,front,nmnof);
	      if(k>0){
		nrnof--;
/* deletion succesfull - we check whether the pointer should be moved */
		if(k<=pnof) pnof--;
	      }
	    }
            if(renum[iaux]==0){
              ngno++;
              renum[iaux]=ngno;
            }
          }
        }
/*for higher order nodes*/
        for(inol=3;inol<nrnost;inol++){
          iaux=pelem[iel]->nodes[inol];
/* if node is not constrained */
          if(iaux>0){
/* and not considered yet */
            if(renum[iaux]==0){
/*either renumber it (for Gauss elimination solver*/
              if(Indyk==1){
                ngno++;
                renum[iaux]=ngno;
	      }
/* or decrease the number of nodes to cinsider*/
              else{
                Nmax--;
                renum[iaux]= -1;
              }
            }
          }
        }
/* finished with all nodes of a given element sharing a front node */
/*kbw
if(iprint==1){
  printf("The front after updating (ngno %d, Nmax %d):\n",ngno,Nmax);
  for(ipr=0;ipr<nrnof;ipr++){printf("%d ",front[ipr]);}
  printf("\n");
  printf("Now pointer %d points to node %d\n",pnof,front[pnof]);
  getchar();
  }
/*kbw*/
	}
      }
/* finished with all elements sharing a front node */
    } /* the end of while loop */

/*checking*/
  ino=0;
  for(ipr=1;ipr<=Nmno;ipr++){
    if((Indyk==1&&pnode[ipr]->type>0)||(Indyk!=1&&pnode[ipr]->type==1)){
      if(renum[ipr]<=0){
        printf("Node %d not considered during renumbering !!!\n",ipr);
      }
      else if(renum[ipr]>Nmax) printf("Too much patches !!!\n");
      else ino++;
    }
  }
  if(ino!=Nmax) printf("Error in renumbering !!!\n"); 

/*kbw*/
if(iprint==1){
  printf("Nodes numbers: old        new");
  for(ipr=0;ipr<=Nmno;ipr++){
    printf("               %d         %d\n",ipr,renum[ipr]);
    }
  }
/*kbw*/
if(ngno!=Nmax) {
  printf("Not all nodes considered!!! (%d < %d)\n",ngno,Nmax);
  getchar();
  }

free((char *)front);
free((char *)loel);

}

/*---------------------------------------------------------
setint - to read matrices with data for 1D and 2D integration
---------------------------------------------------------*/
void setint()
{
int i,j,k,iprint;
FILE *fopen(), *fp;

iprint=1;

fp=fopen("./inputs/quadr.dat","r");

for(i=1;i<=10;i++){
  fscanf(fp,"%d",&k);
  for(j=1;j<=k;j++){
    fscanf(fp,"%lf",&xig1[j][i]);
    fscanf(fp,"%lf",&wag1[j][i]);
  }
}
for(i=0;i<9;i++){
  fscanf(fp,"%d",&sch2[i]);
}
for(i=0;i<19;i++){
  fscanf(fp,"%d",&npg2[i]);
  for(j=0;j<npg2[i];j++){
    fscanf(fp,"%lf",&xig2[0][j][i]);
    fscanf(fp,"%lf",&xig2[1][j][i]);
    fscanf(fp,"%lf",&xig2[2][j][i]);
    fscanf(fp,"%lf",&wag2[j][i]);
  }
}

fclose(fp);

/*kbw
if(iprint==1){
  printf("\n\nIntegration data 1D\n\n");
for(i=1;i<=10;i++){
  printf("%d",i);
    printf("\n");
  for(k=1;k<=i;k++){
    printf("%20.15lf",xig1[k][i]);
    printf("%20.15lf",wag1[k][i]);
    printf("\n");
  }
}
  printf("\n\nIntegration data 2D\n\n");
for(i=0;i<9;i++){
  printf("%d",sch2[i]);
    printf("\n");
}
for(i=0;i<19;i++){
  printf("%d    %d",i,npg2[i]);
    printf("\n");
  for(k=0;k<npg2[i];k++){
    printf("%20.15lf",xig2[0][k][i]);
    printf("%20.15lf",xig2[1][k][i]);
    printf("%20.15lf",xig2[2][k][i]);
    printf("%20.15lf",wag2[k][i]);
    printf("\n");
  }
getchar();
}
}
/*kbw*/
  
}

/*---------------------------------------------------------
setint_old - to initiate matrices for 1D and 2D integration
(1D - four schemes n=1-4, n order of integration,
order of polynomials integrated exactly 2*n-1;
2D - five schemes n=0-4, order of integration n+1 !!!
npg2[n] - number of gaussian points for n-th scheme 
---------------------------------------------------------*/
void setint_old()
{
int i,j,k,iprint;

iprint=1;

xig1[1][1] =  0.000000000000000;

xig1[1][2] = -0.577350269189626;
xig1[2][2] =  0.577350269189626;

xig1[1][3] = -0.774596669241483;
xig1[2][3] =  0.000000000000000;
xig1[3][3] =  0.774596669241483;

xig1[1][4] = -0.861136311594053;
xig1[2][4] = -0.339981043584856;
xig1[3][4] =  0.339981043584856;
xig1[4][4] =  0.861136311594053;

wag1[1][1] =  2.000000000000000;

wag1[1][2] =  1.000000000000000;
wag1[2][2] =  1.000000000000000;

wag1[1][3] =  0.555555555555556;
wag1[2][3] =  0.888888888888889;
wag1[3][3] =  0.555555555555556;

wag1[1][4] =  0.347854845137454;
wag1[2][4] =  0.652145154862546;
wag1[3][4] =  0.652145154862546;
wag1[4][4] =  0.347854845137454;

for(i=1;i<5;i++){
  for(j=1;j<5;j++){
    xig1[i][j]  = 0.5*(1.0+xig1[i][j]);
    wag1[i][j] *= 0.5;
    }
  }

npg2[0]=1;
npg2[1]=3;
npg2[2]=4;
npg2[3]=6;
npg2[4]=7;

wag2[0][0] = 1.000000000000000;   
xig2[0][0][0] = 0.333333333333333;   
xig2[1][0][0] = 0.333333333333333;   
xig2[2][0][0] = 0.333333333333333;

    
wag2[0][1] = 0.333333333333333;   
xig2[0][0][1] = 0.666666666666667;   
xig2[1][0][1] = 0.166666666666667;   
xig2[2][0][1] = 0.166666666666667;
    
wag2[1][1] = 0.333333333333333;   
xig2[0][1][1] = 0.166666666666667;   
xig2[1][1][1] = 0.166666666666667;   
xig2[2][1][1] = 0.666666666666667;
    
wag2[2][1] = 0.333333333333333;   
xig2[0][2][1] = 0.166666666666667;   
xig2[1][2][1] = 0.666666666666667;   
xig2[2][2][1] = 0.166666666666667;

   
wag2[0][2] = -0.562500000000000;   
xig2[0][0][2] = 0.333333333333333;   
xig2[1][0][2] = 0.333333333333333;   
xig2[2][0][2] = 0.333333333333333;
    
wag2[1][2] = 0.520833333333333;   
xig2[0][1][2] = 0.600000000000000;   
xig2[1][1][2] = 0.200000000000000;   
xig2[2][1][2] = 0.200000000000000;
    
wag2[2][2] = 0.520833333333333;   
xig2[0][2][2] = 0.200000000000000;   
xig2[1][2][2] = 0.200000000000000;   
xig2[2][2][2] = 0.600000000000000;
    
wag2[3][2] = 0.520833333333333;  
xig2[0][3][2] = 0.200000000000000;   
xig2[1][3][2] = 0.600000000000000;   
xig2[2][3][2] = 0.200000000000000;

    
wag2[0][3] = 0.223381589678011;   
xig2[0][0][3] = 0.108103018168070;   
xig2[1][0][3] = 0.445948490915965;   
xig2[2][0][3] = 0.445948490915965;
    
wag2[1][3] = 0.223381589678011;   
xig2[0][1][3] = 0.445948490915965;   
xig2[1][1][3] = 0.445948490915965;   
xig2[2][1][3] = 0.108103018168070;
    
wag2[2][3] = 0.223381589678011;   
xig2[0][2][3] = 0.445948490915965;   
xig2[1][2][3] = 0.108103018168070;   
xig2[2][2][3] = 0.445948490915965;
    
wag2[3][3] = 0.109951743655322;   
xig2[0][3][3] = 0.816847572980459;   
xig2[1][3][3] = 0.091576213509771;   
xig2[2][3][3] = 0.091576213509771;
    
wag2[4][3] = 0.109951743655322;   
xig2[0][4][3] = 0.091576213509771;   
xig2[1][4][3] = 0.091576213509771;   
xig2[2][4][3] = 0.816847572980459;
    
wag2[5][3] = 0.109951743655322;   
xig2[0][5][3] = 0.091576213509771;   
xig2[1][5][3] = 0.816847572980459;   
xig2[2][5][3] = 0.091576213509771;

    
wag2[0][4] = 0.225000000000000;   
xig2[0][0][4] = 0.333333333333333;   
xig2[1][0][4] = 0.333333333333333;   
xig2[2][0][4] = 0.333333333333333;
    
wag2[1][4] = 0.132394152788506;   
xig2[0][1][4] = 0.059715871789770;   
xig2[1][1][4] = 0.470142064105115;   
xig2[2][1][4] = 0.470142064105115;
    
wag2[2][4] = 0.132394152788506;   
xig2[0][2][4] = 0.470142064105115;   
xig2[1][2][4] = 0.470142064105115;   
xig2[2][2][4] = 0.059715871789770;
    
wag2[3][4] = 0.132394152788506;   
xig2[0][3][4] = 0.470142064105115;   
xig2[1][3][4] = 0.059715871789770;   
xig2[2][3][4] = 0.470142064105115;
    
wag2[4][4] = 0.125939180544827;   
xig2[0][4][4] = 0.797426985353087;   
xig2[1][4][4] = 0.101286507323456;   
xig2[2][4][4] = 0.101286507323456;
    
wag2[5][4] = 0.125939180544827;   
xig2[0][5][4] = 0.101286507323456;   
xig2[1][5][4] = 0.101286507323456;   
xig2[2][5][4] = 0.797426985353087;
    
wag2[6][4] = 0.125939180544827;   
xig2[0][6][4] = 0.101286507323456;   
xig2[1][6][4] = 0.797426985353087;   
xig2[2][6][4] = 0.101286507323456;

/*kbw*/
if(iprint==1){
  printf("\n\nIntegration data 1D\n\n");
for(i=1;i<=10;i++){
  printf("%d",i);
    printf("\n");
  for(k=1;k<=i;k++){
    printf("%20.15lf",xig1[k][i]);
    printf("%20.15lf",wag1[k][i]);
    printf("\n");
  }
}
  printf("Integration data 2D\n\n");
for(i=0;i<4;i++){
  printf("%d     %d",i,npg2[i]);
    printf("\n");
  for(k=0;k<npg2[i];k++){
    printf("%20.15lf",xig2[0][k][i]);
    printf("%20.15lf",xig2[1][k][i]);
    printf("%20.15lf",xig2[2][k][i]);
    printf("%20.15lf",wag2[k][i]);
    printf("\n");
  }
getchar();
}
}
/*kbw*/
}


double comhgrad(xnod,sold)
double xnod[MAXNODEL][2],sold[MAXNODEL][MAXEQ];
{
double w0,w1,w2,gradx,grady;
double vnx1,vnx2,vny1,vny2,vnx3,vny3,dvl1,dvl2,dvl3;
double vlx1,vlx2,vly1,vly2,vm,dwdl1,dwdl2;
double daux,vp1,vp2,vp3,vp;
int i;

/*first unknown at nodal points */
      w0=sold[0][0];
      w1=sold[1][0];
      w2=sold[2][0];
/*kb*/

/*three vectors parallel to element sides*/
      vnx1=xnod[2][0]-xnod[1][0];
      vny1=xnod[2][1]-xnod[1][1];
      dvl1=sqrt(vnx1*vnx1+vny1*vny1);

      vnx2=xnod[0][0]-xnod[1][0];
      vny2=xnod[0][1]-xnod[1][1];
      dvl2=sqrt(vnx2*vnx2+vny2*vny2);

      vnx3=xnod[0][0]-xnod[2][0];
      vny3=xnod[0][1]-xnod[2][1];
      dvl3=sqrt(vnx3*vnx3+vny3*vny3);

/*normalized vectors*/
      vlx1=vnx1/dvl1;
      vly1=vny1/dvl1;
      vlx2=vnx2/dvl2;
      vly2=vny2/dvl2;

/*directional derivatives of w along sides*/
      dwdl1=(w2-w1)/dvl1;
      dwdl2=(w0-w1)/dvl2;

/*solution of a system for x and y derivatives of w*/
      vm=vlx1*vly2-vlx2*vly1;
      gradx=( dwdl1*vly2-dwdl2*vly1)/vm;
      grady=(-dwdl1*vlx2+dwdl2*vlx1)/vm;

/*normalize gradient*/
    daux=sqrt(gradx*gradx+grady*grady);
    if(daux>1e-12){
      gradx = gradx/daux;
      grady = grady/daux;

/*projections of side vectors onto the direction of the gradient*/
      vp1=fabs(gradx*vnx1+grady*vny1);
      vp2=fabs(gradx*vnx2+grady*vny2);
      vp3=fabs(gradx*vnx3+grady*vny3);

    }
    else{

/*just length of sides*/
       vp1=sqrt(vnx1*vnx1+vny1*vny1);
       vp2=sqrt(vnx2*vnx2+vny2*vny2);
       vp3=sqrt(vnx3*vnx3+vny3*vny3);

    }

/*max*/
    vp=vp1;
    if(vp2>vp) vp=vp2;
    if(vp3>vp) vp=vp3;

return(vp);
}
