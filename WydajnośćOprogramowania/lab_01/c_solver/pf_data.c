/*************************************************************
File contains procedures:
  dumpin - to read data from dump.std stored there by dumpout
  dumpout - to write to a file dump.std all necessary data
  dumpin_j - to read data from input files

Required procedures:
  put_list - in po_util.c

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

#define PI 3.14159265358979
/*---------------------------------------------------------
dumpin - to read data from dump.std stored there by dumpout
---------------------------------------------------------*/
void dumpin(Indyk)
int Indyk;
{
extern int put_list();
int ino,iel,i,j,k,ipr,iprint,Indit,nrnoel,elorder;
double daux;
FILE *fopen(), *fp;


iprint=1;

/* open an initial or a standard dump file */
if(Indyk==0) fp=fopen("./inputs/dump.ini","r");
else fp=fopen("./inputs/dump.std","r");

/*reading proceeds in the same order as writing in dumpout
- see dumpout below for explanations */
/*short part with problem dependent data */
fscanf(fp,"%d",&Ntype);
fscanf(fp,"%d",&Indsol);
fscanf(fp,"%d",&Nstop);
fscanf(fp,"%d",&Nadapt);
fscanf(fp,"%d",&Indgen);
fscanf(fp,"%d",&Nnopt);
fscanf(fp,"%lf",&Epsu);
fscanf(fp,"%lf",&Eta);
fscanf(fp,"%lf",&Eta2);
fscanf(fp,"%lf",&Dtt);
fscanf(fp,"%lf",&Time);
fscanf(fp,"%lf",&Errconv);
/*problem independent data*/
fscanf(fp,"%d",&Nrno);
fscanf(fp,"%d",&Nrel);
fscanf(fp,"%d",&Nreq);
fscanf(fp,"%d",&pfno);
fscanf(fp,"%d",&pfel);
fscanf(fp,"%d",&Nmno);
fscanf(fp,"%d",&Nmel);

Indit=0;
if(Ntype/100==1) Indit=100;

/* allocate space for nodes and elements */
if(Nmno<=MAXNO){
  pnode = (NODES **)malloc((MAXNO+1)*sizeof(NODES *));
  for(ino=1;ino<=Nmno;ino++){
    pnode[ino] = (NODES *)malloc(sizeof(NODES));
    if(pnode[ino]==NULL){
      printf("Not enough space for node %d\nExiting !!!\n",ino);
      exit(1);
      }
    }
  }
else{
  printf("Too much nodes in dumpin !!!\n Increase MAXNO !\n");
  exit(1);
  }
if(Nmel<=MAXEL){
  pelem = (ELEMS **)malloc((MAXEL+1)*sizeof(ELEMS *));
  for(iel=0;iel<=Nmel;iel++){
    pelem[iel] = (ELEMS *)malloc(sizeof(ELEMS));
    if(pelem[iel]==NULL){
      printf("Not enough space for element %d\nExiting !!!\n",iel);
      exit(1);
      }
    }
  }
else{
  printf("Too much elements in dumpin !!!\n Increase MAXEL !\n");
  exit(1);
  }
if(iprint==1){
  printf("Number of elements %d\n",Nrel);
  printf("Number of nodes %d\n",Nrno);
  printf("Allocated space for %d elements\n",Nmel);
  printf("Allocated space for %d nodes\n",Nmno);
  }

/*read data concerning nodes*/
for(ino=1;ino<=Nmno;ino++){
  fscanf(fp,"%d",&pnode[ino]->type);

  if(pnode[ino]->type==0){
    fscanf(fp,"%d",&pnode[ino]->glnr);
  }
  else {
    if(pnode[ino]->type<-10){
      pnode[ino]->type += 10;
      pnode[ino]->x=0.0;
      pnode[ino]->y=0.0;
    }
    else if(pnode[ino]->type>10){
      pnode[ino]->type -= 10;
      pnode[ino]->x=0.0;
      pnode[ino]->y=0.0;
    }
    else{
      fscanf(fp,"%lf",&pnode[ino]->x);
      fscanf(fp,"%lf",&pnode[ino]->y);
    }
    pnode[ino]->glnr=0;
    if(Indit>0) pnode[ino]->ui=(double *)malloc(Nreq*sizeof(double));
    for(j=0;j<Nreq;j++){
      fscanf(fp,"%lf",&pnode[ino]->u2[j]);
      pnode[ino]->u0[j]=pnode[ino]->u2[j];
      pnode[ino]->u1[j]=pnode[ino]->u2[j];
    }

/* since fields elems[] from NODES structures are not stored
they are here initiated to zero (for vertex nodes only)*/
    if(abs(pnode[ino]->type)==1){
      pnode[ino]->elems=(int *)malloc(MAXELNO*sizeof(int));
      for(j=0;j<MAXELNO;j++){
        pnode[ino]->elems[j]=0;
      }
    }

  }
}
/*read data concerning elements*/
for(iel=1;iel<=Nmel;iel++){
  fscanf(fp,"%d",&pelem[iel]->type);
  fscanf(fp,"%d",&pelem[iel]->fath);
  if(pelem[iel]->type != 0){
    nrnoel=3;elorder=1;
    for(j=1;j<MAXVNOEL+2;j++){
      fscanf(fp,"%d",&pelem[iel]->order[j]);
      if(j<MAXVNOEL+1) nrnoel += pelem[iel]->order[j] -1;
      else{ k=pelem[iel]->order[j]; nrnoel += (k-1)*(k-2)/2;}
      if(pelem[iel]->order[j]>elorder) elorder=pelem[iel]->order[j];
    }
    pelem[iel]->order[0]=elorder;
    pelem[iel]->nodes = (int *)malloc(nrnoel*sizeof(int));
    for(j=0;j<nrnoel;j++){
      fscanf(fp,"%d",&pelem[iel]->nodes[j]);
/*while reading ELEMS structures the fields elems[]
in NODES structures are filled in (for vertex nodes only)*/
      if(j<3&&pelem[iel]->type>0){
        ino=pelem[iel]->nodes[j];
        if(ino>0){
    	  i=put_list(iel,pnode[ino]->elems,MAXELNO);
	  if(i<0){
	    printf("Something wrong with filling NODES->elems for %d\n",ino);
            for(ipr=0;ipr<MAXELNO;ipr++) 
              printf("%d\n",pnode[ino]->elems[ipr]);
	    printf("\n");
            getchar();
 	  }
        }
      }
    }
    fscanf(fp,"%d",&pelem[iel]->elbc);
  }
}

for(j=0;j<9;j++){
  fscanf(fp,"%lf",&Bndata[j][0]);
  fscanf(fp,"%lf",&Bndata[j][1]);
  fscanf(fp,"%lf",&Bndata[j][2]);
  fscanf(fp,"%lf",&Bndata[j][3]);
  }
fclose(fp);
}

/*---------------------------------------------------------
dumpout - to write to a file dump.std all necessary data
in the most compact form
---------------------------------------------------------*/
void dumpout(Indyk)
int Indyk;
{
extern void neighb(); /*in pf_util.c*/

int ino,iel,j,k,nrnoel,elorder;
double daux;
FILE *fopen(), *fp;
int neig[6], neigsid[6];

/* open an initial or a standard dump file */
if(Indyk==0) fp=fopen("./inputs/dump.ini","w");
else if(Indyk==2) fp=fopen("./inputs/dump.ent","w");
else if(Indyk==3) fp=fopen("./inputs/dump.ftn","w");
else fp=fopen("./inputs/dump.std","w");
/*write control data*/
fprintf(fp,"%6d\n",Ntype);
fprintf(fp,"%6d\n",Indsol);
fprintf(fp,"%6d\n",Nstop);
fprintf(fp,"%6d\n",Nadapt);
fprintf(fp,"%6d\n",Indgen);
fprintf(fp,"%6d\n",Nnopt);
fprintf(fp,"%16.12lf\n",Epsu);
fprintf(fp,"%16.12lf\n",Eta);
fprintf(fp,"%16.12lf\n",Eta2);
fprintf(fp,"%16.12lf\n",Dtt);
fprintf(fp,"%16.12lf\n",Time);
fprintf(fp,"%16.12lf\n",Errconv);
/*write numbers, pointers and maximal initiated indices*/
fprintf(fp,"%6d\n",Nrno);
fprintf(fp,"%6d\n",Nrel);
fprintf(fp,"%6d\n",Nreq);
fprintf(fp,"%6d\n",pfno);
fprintf(fp,"%6d\n",pfel);
fprintf(fp,"%6d\n",Nmno);
fprintf(fp,"%6d\n",Nmel);
/*write NODES structures (for free spaces only type and
the pointer to the next free space */
for(ino=1;ino<=Nmno;ino++){
  if(pnode[ino]->type==0){
    fprintf(fp,"%6d\n",pnode[ino]->type);
    fprintf(fp,"%6d\n",pnode[ino]->glnr);
    }
  else{
    if(pnode[ino]->x==0.0&&pnode[ino]->y==0.0){
      if(pnode[ino]->type>0){
        fprintf(fp,"%6d\n",pnode[ino]->type+10);
      }
      else{
        fprintf(fp,"%6d\n",pnode[ino]->type-10);
      }
    }
    else{
      fprintf(fp,"%6d\n",pnode[ino]->type);
      fprintf(fp,"%16.12lf\n",pnode[ino]->x);
      fprintf(fp,"%16.12lf\n",pnode[ino]->y);
    }
    for(j=0;j<Nreq;j++){
      fprintf(fp,"%16.12lf\n",pnode[ino]->u2[j]);
    }
  }
}
/*write ELEMS structures (for free
spaces only two fields: indi and fath */
for(iel=1;iel<=Nmel;iel++){
  fprintf(fp,"%6d\n",pelem[iel]->type);
  fprintf(fp,"%6d\n",pelem[iel]->fath);
  if(pelem[iel]->type != 0){
    nrnoel=3;elorder=1;
    for(j=1;j<MAXVNOEL+2;j++){
      fprintf(fp,"%6d\n",pelem[iel]->order[j]);
      if(j<MAXVNOEL+1) nrnoel += pelem[iel]->order[j] -1;
      else{ k=pelem[iel]->order[j]; nrnoel += (k-1)*(k-2)/2;}
      if(pelem[iel]->order[j]>elorder) elorder=pelem[iel]->order[j];
    }
    if(pelem[iel]->order[0]!=elorder){printf("wrong order\n");exit(1);}
    for(j=0;j<nrnoel;j++){
      fprintf(fp,"%6d\n",pelem[iel]->nodes[j]);
      }
    fprintf(fp,"%6d\n",pelem[iel]->elbc);
    if(Indyk==3){
      neighb(iel, neig, neigsid);
      for(j=0;j<3;j++){
        fprintf(fp,"%6d\n",neig[2*j]);
      }
    }
  }
}
/*write boundary data*/
for(j=0;j<9;j++){
  fprintf(fp,"%16.12lf\n",Bndata[j][0]);
  fprintf(fp,"%16.12lf\n",Bndata[j][1]);
  fprintf(fp,"%16.12lf\n",Bndata[j][2]);
  fprintf(fp,"%16.12lf\n",Bndata[j][3]);
  }
fclose(fp);
}

/*---------------------------------------------------------
dumpin_j - to read data from input files in directory inputs_j
---------------------------------------------------------*/
void dumpin_j()
{
extern int put_list();
extern void neighb(); /*in pf_util.c*/
int ino,iel,i,j,ieq,ipr,iprint,iaux,Indit,order,isid,inol,nrnost,pno;
double daux;
FILE *fopen(), *fp;
int bc[3],ino1,ino2,ino3,specflag,nrnoel,ipsid;
double inidata[4][4],tnx,tny,tnl;
double yp,ye,xp,xp1,yp1,x1,x2,y1,y2,xc,yc,rad,dist,gamma;
int neig[6], neigsid[6];

iprint=1;
specflag=1;

if(specflag==1){
  //  printf("\n\nSpecial treatment of boundary data !!!\n\n\n");
  }

/*  POSSIBLE SPLITTING INTO TWO FILES WITH DATA */

/* open the file with control data */
fp=fopen("./control.dat","r");


/* open the file with input data
fp=fopen("./input_j.dat","r");
 */

/*reading control data */
fscanf(fp,"%d",&Ntype);
fscanf(fp,"%d",&Indsol);
fscanf(fp,"%d",&Nstop);
fscanf(fp,"%d",&Nadapt);
fscanf(fp,"%d",&Indgen);
fscanf(fp,"%d",&Nnopt);
fscanf(fp,"%d",&Nreq);
fscanf(fp,"%lf",&Epsu);
fscanf(fp,"%lf",&Eta);
fscanf(fp,"%lf",&Eta2);
fscanf(fp,"%lf",&Dtt);
fscanf(fp,"%lf",&Time);
fscanf(fp,"%lf",&Errconv);

Indit=0;
if(Ntype/100==1) Indit=100;

/*read boundary data*/
fscanf(fp,"%d",&i);
if(i>9){
  printf("Too much boundary data !");
  exit(1);
  }
for(j=0;j<i;j++){
  for(ieq=0;ieq<Nreq;ieq++){
    fscanf(fp,"%lf",&Bndata[j][ieq]);
  }
}
for(j=i;j<9;j++){
  for(ieq=0;ieq<Nreq;ieq++){
    Bndata[j][ieq]=0.0;
  }
}

/*read initial data*/
fscanf(fp,"%d",&i);
if(i>4){
  printf("Too much initial data !");
  exit(1);
  }
for(j=0;j<i;j++){
  for(ieq=0;ieq<Nreq;ieq++){
    fscanf(fp,"%lf",&inidata[j][ieq]);
  }
}

/* POSSIBLE SPLITTING INTO TWO FILES WITH DATA */

/*  close the file with control data */
fclose(fp);

/*  open the file with mesh data */
fp=fopen("./input_j.dat","r");

/*for the time beeing it is assumed that the initial mesh is
homogeneous wrt element orders p and that p is specified as first 
parameter in input file
*/
fscanf(fp,"%d",&order);
if(order>MAXORDER){
  Nrno=order;
  order=1;
  nrnoel=3;
}
else{
  nrnoel=3*order+(order-1)*(order-2)/2;
  fscanf(fp,"%d",&Nrno);
}

/*reading data concerning vertex nodes*/
Nmno=Nrno;
pfno=Nmno+1;
/* allocate space for nodes and constrained nodes */
if(Nmno<MAXNO){
  pnode = (NODES **)malloc((MAXNO+1)*sizeof(NODES *));
  for(ino=1;ino<=Nmno;ino++){
    pnode[ino] = (NODES *)malloc(sizeof(NODES));
    if(pnode[ino]==NULL){
      printf("Not enough space for node %d\nExiting !!!\n",ino);
      exit(1);
      }
    }
  }
else{
  printf("Too much nodes in dumpin !!!\n Increase MAXNO !\n");
  exit(1);
  }
if(iprint==1){
  printf("Number of nodes %d\n",Nrno);
  printf("Allocated space for %d nodes\n",Nmno);
  }
/* NODES structures are here read or initiated to zero*/
for(ino=1;ino<=Nmno;ino++){
  pnode[ino]->type=1;
  pnode[ino]->glnr=0;
  pnode[ino]->elems=(int *)malloc(MAXELNO*sizeof(int));
  for(j=0;j<MAXELNO;j++){
    pnode[ino]->elems[j]=0;
  }
  fscanf(fp,"%lf",&pnode[ino]->x);
  fscanf(fp,"%lf",&pnode[ino]->y);

/*kbw
if(iprint==1){
  printf("Node %d, x = %12.6lf, y = %12.6lf",ino,pnode[ino]->x,pnode[ino]->y);
  getchar();
}
/*kbw*/
  if(Indit>0) pnode[ino]->ui=(double *)malloc(Nreq*sizeof(double));

  for(j=0;j<Nreq;j++){
    pnode[ino]->u1[j] = inidata[0][j];
  }
/*kb!!!
  if(Nnopt>=0&&pnode[ino]->x<0.5){
    pnode[ino]->u1[0] = -sin(pnode[ino]->x*PI/0.5);
    pnode[ino]->u1[1] = -sin(pnode[ino]->x*PI/0.5);
  }
/*kb!!!*/
}

/*reading data concerning elements*/
fscanf(fp,"%d",&Nrel);
Nmel=Nrel;
pfel=Nmel+1;

/* allocate space for elements */
if(Nmel<MAXEL){
  pelem = (ELEMS **)malloc((MAXEL+1)*sizeof(ELEMS *));
  for(iel=0;iel<=Nmel;iel++){
    pelem[iel] = (ELEMS *)malloc(sizeof(ELEMS));
    if(pelem[iel]==NULL){
      printf("Not enough space for element %d\nExiting !!!\n",iel);
      exit(1);
      }
    }
  }

if(iprint==1){
  printf("Number of elements %d\n",Nrel);
  printf("Allocated space for %d elements\n",Nmel);
  }

for(iel=1;iel<=Nmel;iel++){

  pelem[iel]->type = 1;
  pelem[iel]->fath = 0;

  fscanf(fp,"%d",&iaux);

/*for each element order arrays are filled in*/
  for(i=0;i<MAXVNOEL+2;i++){
    pelem[iel]->order[i]=order;
  }
  pelem[iel]->nodes = (int *)malloc(nrnoel*sizeof(int));

/*vertex nodes are read from the file*/
  for(j=0;j<3;j++){
    fscanf(fp,"%d",&pelem[iel]->nodes[j]);

/*while reading ELEMS structures the fields elems[]
in NODES structures are filled in*/
    ino=pelem[iel]->nodes[j];
    if(ino>0){
      i=put_list(iel,pnode[ino]->elems,MAXELNO);
      if(i<0){
        printf("Something wrong with filling NODES->elems for %d\n",ino);
        for(ipr=0;ipr<MAXELNO;ipr++)
          printf("%d\n",pnode[ino]->elems[ipr]);
        printf("\n");
        getchar();
      }
    }
  }
  for(j=3;j<nrnoel;j++) pelem[iel]->nodes[j]=0;


/*boundary data and neighbours are read from the input file*/
  fscanf(fp,"%d",&bc[0]);
  fscanf(fp,"%d",&bc[1]);
  fscanf(fp,"%d",&bc[2]);
  for(i=0;i<3;i++){
    if(bc[i]>0) bc[i]=0;
    else bc[i] *= -1;
  }

/*kb*/
  if(specflag==1){
/*nodes on the circle*/
    if(bc[0]==13){
      ino1=pelem[iel]->nodes[0];
      ino2=pelem[iel]->nodes[1];
      tnx=pnode[ino2]->x - pnode[ino1]->x;
      tny=pnode[ino2]->y - pnode[ino1]->y;
      tnl=sqrt(tnx*tnx+tny*tny);
      pnode[ino1]->u1[1]=fabs(tnx/tnl)*pnode[ino1]->u1[1];
      if(fabs(tnx)>0.000001*fabs(tny)){
        pnode[ino1]->u1[2]=tny/tnx*pnode[ino1]->u1[1];
      }
/*nodes on the NACA0012 airfoil*/
if(Nnopt>10&&Nnopt<30){
  xp=pnode[ino1]->x;yp=pnode[ino1]->y;
  ye=0.6*(0.2969*sqrt(xp)-0.126*xp-0.3516*xp*xp+0.2843*xp*xp*xp-0.1015*xp*xp*xp*xp);
  if(yp<0) ye *= -1;
  if(fabs(ye-yp)>1e-9) {
/*kbw
   printf("at old point: x - %9.6lf, y - %15.12lf\n",xp,yp);
   printf("exact airfoil data for x   - %15.12lf (diff=%15.12lf)\n",ye,ye-yp);
/*kbw*/
   xp=pnode[ino1]->x;
   ye=0.6*(0.2969*sqrt(xp)-0.126*xp-0.3516*xp*xp+0.2843*xp*xp*xp-0.1015*xp*xp*xp*xp);
   if(yp<0) ye *= -1;
   pnode[ino1]->y = ye;
/*kbw
   printf("new point: x - %9.6lf, y - %15.12lf\n",pnode[ino1]->x,pnode[ino1]->y);
   getchar();
/*kbw*/
  }
}



    }
  }
/*kb*/

  pelem[iel]->elbc =  bc[2] + bc[1]*BCBASE + bc[0]*BCBASE*BCBASE;

/*kbw
if(iprint==1){
  if(pelem[iel]->elbc>0){
    ino1=pelem[iel]->nodes[0];
    ino2=pelem[iel]->nodes[1];
    ino3=pelem[iel]->nodes[2];
    printf("Element %d, elbc - %d\n",iel,pelem[iel]->elbc);
    printf("Nodes %d, %d, %d\n",ino1,ino2,ino3);
    printf("Nodes coordinates:\n");
    printf("node 1 - %12.6lf %12.6lf\n",pnode[ino1]->x,pnode[ino1]->y);
    printf("node 2 - %12.6lf %12.6lf\n",pnode[ino2]->x,pnode[ino2]->y);
    printf("node 3 - %12.6lf %12.6lf\n",pnode[ino3]->x,pnode[ino3]->y);
    printf("Velocities at nodes:\n");
    printf("node 1 - %12.6lf %12.6lf\n",pnode[ino1]->u1[1],pnode[ino1]->u1[2]);
    printf("node 2 - %12.6lf %12.6lf\n",pnode[ino2]->u1[1],pnode[ino2]->u1[2]);
    printf("node 3 - %12.6lf %12.6lf\n",pnode[ino3]->u1[1],pnode[ino3]->u1[2]);
    printf("side 1 - %d, side 2 - %d, side 3 - %d\n", bc[0], bc[1], bc[2]);
    getchar();
  }
}
/*kbw*/


}

/* close the file with mesh data */
fclose(fp); 



if(order>1){

  /*adding higher order nodes information*/
  for(iel=1;iel<=Nmel;iel++){

    nrnost=2;

/*boundary conditions are necessary for some tricks*/
    bc[2]=(pelem[iel]->elbc)%BCBASE;
    bc[1]=((pelem[iel]->elbc)/BCBASE)%BCBASE;
    bc[0]=(((pelem[iel]->elbc)/BCBASE)/BCBASE)%BCBASE;

/*higher order nodes are created*/

/*first find neighbours and compare data structures*/
    neighb(iel, neig, neigsid);

/*in a loop over sides*/
    for(isid=0;isid<3;isid++){



/*kbw
printf("In element %d, on side %d\n",iel,isid);
printf("neighbour %d (its side %d)\n",neig[2*isid],neigsid[2*isid]);
/*kbw*/


/*if neighbour has already created necessary nodes*/
        if(neig[2*isid]>0&&pelem[neig[2*isid]]->nodes[MAXVNOEL]>0){

/*just rewrite his nodes to corresponding entries*/
/*last node on the side*/
        inol=2+neigsid[2*isid]*(order-1)+order-1;


/*kbw
printf("neighbour nodes \n");
for(ipr=0;ipr<nrnoel;ipr++){
  printf("%d  ",pelem[neig[2*isid]]->nodes[ipr]);
}
printf("\nWe chose %d %d\n",pelem[neig[2*isid]]->nodes[inol],pelem[neig[2*isid]]->nodes[inol-1]);
getchar();
/*kbw*/


        for(i=0;i<order-1;i++){
          nrnost++;
          pno=pelem[neig[2*isid]]->nodes[inol-i];
          pelem[iel]->nodes[nrnost]=pno;
        }
      }
      else{
/*we have to create new nodes between side endpoints (x1,y1) and (x2,y2)*/
        i=pelem[iel]->nodes[isid];
        x1=pnode[i]->x;
        y1=pnode[i]->y;
        j=pelem[iel]->nodes[(isid+1)%3];
        x2=pnode[j]->x;
        y2=pnode[j]->y;

/*checking for circle boundary*/
        if(bc[isid]==7){
          xc=2.0;yc=0.0;rad=0.5;
          yp=sqrt(rad*rad-(x1-xc)*(x1-xc));
	  if(fabs(yp-y1)>1e-9){
            if(fabs(yp-y1)<1e-3) {
              pnode[i]->y=yp;
              y1=yp;
              printf("Corrected value on the circle boundary!\n");
            } else {
              printf("Wrong value on the circle boundary!\n");
              exit(1);
            }
          }
          yp=sqrt(rad*rad-(x2-xc)*(x2-xc));
	  if(fabs(yp-y2)>1e-9){
            if(fabs(yp-y2)<1e-3) {
              pnode[j]->y=yp;
              y2=yp;
              printf("Corrected value on the circle boundary!\n");
            } else {
              printf("Wrong value on the circle boundary!\n");
              exit(1);
            }
          }
        }

        for(ipsid=0;ipsid<order-1;ipsid++){
          nrnost++;
/*pointer to the free space for a node*/
          pno=pfno;
          pelem[iel]->nodes[nrnost]=pno;

          if(pno+1>MAXNO){
            printf("Not enough space for next node, Nrno= %d\n",Nrno);
            exit(1);
          }

          pfno += 1;
          Nmno += 1;
/*new space must be allocated for a new node*/
          pnode[pno] = (NODES *)malloc(sizeof(NODES));
          if(pnode[pno]==NULL){
            printf("Not enough space for node %d\nExiting !!!\n",pno);
            exit(1);
          }

          Nrno += 1;

/*indicate this is a mid-side node - we do not store elements for it*/
          pnode[pno]->type=2;
/*clear global number of a node*/
          pnode[pno]->glnr=0;
/*allocate the space for intermediate storage in nonlinear schemes*/
          if(Indit>0) pnode[pno]->ui=(double *)malloc(Nreq*sizeof(double));
/*fill in coordinates and solution values for a new node*/
          if(bc[isid]!=7){
/*for linear dependence on coordinates we just have zeros!!!*/
            pnode[pno]->x=0;
            pnode[pno]->y=0;
          }
          else{
/*unfortunatelly for circle we have to perform some kind of
interpolation*/ 

/*for a given circle*/
            gamma=1.0/order;gamma*=ipsid+1;xc=2.0;yc=0.0;rad=0.5;
            i=2;
            coorexact(i,&xp,&yp,x1,y1,x2,y2,gamma,xc-rad,xc+rad);
/*last checking*/
            daux=fabs((xp-xc)*(xp-xc)+(yp-yc)*(yp-yc)-rad*rad);
            if(daux>1e-6){
              printf("wrong circle on output %lf \n",daux);
            }

/* given point coordinates we have to find point's geometrical dofs */
            xp1=gamma*x1+(1-gamma)*x2;
            yp1=gamma*y1+(1-gamma)*y2;

            pnode[pno]->x = xp-xp1;
            pnode[pno]->y = yp-yp1;
 
          }
          for(j=0;j<Nreq;j++){
            pnode[pno]->u1[j] = 0;
          }
        }
      }
    }
/*^the end of loop over sides*/

    if(order>2){

/*create middle nodes*/
        for(i=0;i<(order-1)*(order-2)/2;i++){
          nrnost++;
/*pointer to the free space for a node*/
          pno=pfno;
          pelem[iel]->nodes[nrnost]=pno;

          if(pno+1>MAXNO){
            printf("Not enough space for next node, Nrno= %d\n",Nrno);
            exit(1);
          }

          pfno += 1;
          Nmno += 1;
/*new space must be allocated for a new node*/
          pnode[pno] = (NODES *)malloc(sizeof(NODES));
          if(pnode[pno]==NULL){
            printf("Not enough space for node %d\nExiting !!!\n",pno);
            exit(1);
          }

          Nrno += 1;

/*indicate this is a middle node - we do not store elements for it*/
          pnode[pno]->type=3;
/*clear global number of a node*/
          pnode[pno]->glnr=0;
/*allocate the space for intermediate storage in nonlinear schemes*/
          if(Indit>0) pnode[pno]->ui=(double *)malloc(Nreq*sizeof(double));
/*fill in coordinates and solution values for a new node*/
          pnode[pno]->x=0;
          pnode[pno]->y=0;
          for(j=0;j<Nreq;j++){
            pnode[pno]->u1[j] = 0;
          }
        }
    }
    if(nrnost+1!=nrnoel){printf("Wrong number of nodes\n");exit(1);}
  }
}

for(ino=1;ino<=Nmno;ino++){
  for(j=0;j<Nreq;j++){
    pnode[ino]->u0[j] = pnode[ino]->u1[j];
    pnode[ino]->u2[j] = pnode[ino]->u1[j];
  }
}

printf("Created %d nodes\n",Nmno);

}
