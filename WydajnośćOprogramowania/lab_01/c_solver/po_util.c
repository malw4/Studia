/*************************************************************
File contains procedures:
  answer - to return answer YES or NO
  unpack - to unpack a single integer into a vector
  chk_list, put_list, del_list - to manipulate with lists
  ludcmp, lusol - to solve by LU decomposition
  isetz, rsetz - to initialize arrays
  scprod, vecnorm, vecsum, copyvec, axpy - to perform basic vector operations
  mat4prod, mat4vec, mat4scal, vec4prod, vec4sum - as above in R^4 
  coorexact - to find a point in between two points on a curve
*************************************************************/

#include<stdlib.h>
#include<stdio.h>
#include<math.h>

#define LINE 80

/*answer - to return answer YES or NO*/
char answer()
{
char *pans,c;
pans = (char *)malloc(LINE*sizeof(char));
do {
scanf("%s",pans);getchar();
  } while ( *pans != 'Y' && *pans != 'y' && *pans != 'N' && *pans != 'n' );
if(*pans=='y') *pans='Y';
if(*pans=='n') *pans='N';

c = *pans;

free((char *)pans);

return(c);
}

/*
unpack - to unpack a single integer packed using base
into a vector comprising of several integers;
unpack returns the number of unpacked items.
*/
int unpack(Num,Base,Vec)
int Num,Base,*Vec;
{
int irest1,irest2,ipos;

irest1=Num;
ipos=0;
while(irest1!=0){
  irest2=irest1/Base;
  Vec[ipos++]=irest1-Base*irest2;
  irest1=irest2;
  }
return(ipos);
}

/*
chk_list - to check whether Num is on the list List
with length Ll
*/
int chk_list(Num, List, Ll)
int Num, *List, Ll;
{
int i, il;

for(i=0;i<Ll;i++){
  if((il=List[i])==0) break;
  /* found on the list on (i+1) position */
  if(Num==il) return(i+1);
  }
/* not found on the list */
return(0);
}

/*
routine checks whether Num is on the list List
with length Ll (filled with numbers and zeros at the end),
putting it in the place of first zero if not found
*/
int put_list(Num, List, Ll)
int Num, *List, Ll;
{
int i, il;

for(i=0;i<Ll;i++){
  if((il=List[i])==0) break;
  /* found on the list on (i+1) position */
  if(Num==il) return(i+1);
  }
/* if list is full return error message */
if(i==Ll) return(-1);
/* update the list and return*/
List[i]=Num;
return(0);
}

 /*
routine checks whether Num is on the list List
with length Ll (filled with numbers and zeros at the end),
deleting it if found and returning the position on which
it was found; if not found zero is returned
*/
int del_list(Num, List, Ll)
int Num, *List, Ll;
{
int i,j,il;

for(i=0;i<Ll;i++){
  if((il=List[i])==0) break;
  /* found on the list on (i+1) position */
  if(Num==il) {
    for(j=i+1;j<Ll;j++){
      List[j-1]=List[j];
      }
    List[Ll-1]=0;
    return(i+1);
    }
  }
/* not found - return 0 */
return(0);
}

/*standard procedures for quasi-LU decomposition of a matrix
and solving a set of linear equation*/

#define small 1.0e-35

void ludcmp(a,m,ips)
int m,*ips;   /*ips for partial pivoting information storage*/
double **a;
{

int i,j,k,mm1,kp1,ipiv,kpiv,ipivot;
double temp,pivot,big;

for(i=0;i<m;i++){ips[i]=i;}

mm1=m-1;
for(k=0;k<mm1;k++){
  big=0.0;
  for(i=k;i<m;i++){
    ipiv=ips[i];
    if(big<=fabs(a[ipiv][k])){
      big=fabs(a[ipiv][k]);
      ipivot=i;
      }
    }
  if(big<small){
    printf("Zero pivot in LU decomposition (%lf)\n",big);
    exit(1);
    }
  kpiv=ips[ipivot];
  if(ipivot!=k){
    ips[ipivot]=ips[k];
    ips[k]=kpiv;
    }
  pivot=a[kpiv][k];
  kp1=k+1;
  for(i=kp1;i<m;i++){
    ipiv=ips[i];
    temp=a[ipiv][k]/pivot;
    a[ipiv][k]=temp;
    for(j=kp1;j<m;j++) a[ipiv][j] -= temp*a[kpiv][j];
    }
  }
if(fabs(a[ips[mm1]][mm1])<small){
  printf("Zero pivot in LU decomposition (%lf)\n",a[ips[mm1]][mm1]);
  exit(1);
  }
}

void lusol(a,m,b,x,ips)
int m,*ips;   /*ips for partial pivoting information storage*/
double **a,*b,*x;

{
int i,j,ipiv;
double sum;

x[0]=b[ips[0]];
for(i=1;i<m;i++){
  ipiv=ips[i];
  sum=b[ipiv];
  for(j=0;j<i;j++){ sum -= a[ipiv][j]*x[j]; }
  x[i]=sum;
  }
x[m-1]=x[m-1]/a[ipiv][m-1];
for(i=m-2;i>=0;i--){
  ipiv=ips[i];
  sum=x[i];
  for(j=i+1;j<m;j++){ sum -= a[ipiv][j]*x[j]; }
  x[i]= sum / a[ipiv][i];
  }
}

void rsetz(Vec, Num)
int Num;
double *Vec;
{
int i;

for(i=0;i<Num;i++){
  Vec[i]=0;
  }
}

void isetz(Vec, Num)
int Num;
int *Vec;
{
int i;

for(i=0;i<Num;i++){
  Vec[i]=0;
  }
}

void mat4prod(m1,m2,m3)
double m1[4][4],m2[4][4],m3[4][4];
{
int i,j,k;

for(i=0;i<4;i++){
  for(j=0;j<4;j++){
    m3[i][j]=0.0;
    for(k=0;k<4;k++){
      m3[i][j] += m1[i][k]*m2[k][j];
      }
    }
  }
}

void mat4vec(m1,v1,v2)
double m1[4][4],v1[4],v2[4];
{
int i,k;

for(i=0;i<4;i++){
  v2[i]=0.0;
  for(k=0;k<4;k++){
    v2[i] += m1[i][k]*v1[k];
    }
  }
}

void mat4scal(m0,s0)
double m0[4][4],s0;
{
int i,j;

for(i=0;i<4;i++){
  for(j=0;j<4;j++){
    m0[i][j] *= s0;
    }
  }
}

double vec4prod(v1,v2)
double v1[4],v2[4];
{
int i;
double sc;

sc = 0.0;
for(i=0;i<4;i++){
  sc += v1[i]*v2[i];
  }
return(sc);
}

void vec4sum(v1,v2,v3)
double v1[4],v2[4],v3[4];
{
int i;

for(i=0;i<4;i++){
  v3[i] = v1[i] + v2[i];
  }
}

double scprod(v1,v2,lv)
double *v1,*v2;
int lv;
{
int i;
double sc;

sc = 0.0;
for(i=0;i<lv;i++){
  sc += v1[i]*v2[i];
  }
return(sc);
}

double vecnorm(v1,lv1)
double *v1;
int lv1;
{
int i;
double vnorm;

vnorm = 0.0;
for(i=0;i<lv1;i++){
  vnorm += v1[i]*v1[i];
  }
return(sqrt(vnorm));
}

void vecsum(v1,v2,lv,v3)
double *v1,*v2,*v3;
int lv;
{
int i;

for(i=0;i<lv;i++){
  v3[i] = v1[i] + v2[i];
  }
}

void copyvec(v1,v2,lv)
double *v1,*v2;
int lv;
{
int i;

for(i=0;i<lv;i++){
  v2[i]=v1[i];
  }
return;
}

void axpy(v1,v2,lv,alpha,beta)
double *v1,*v2,alpha,beta;
int lv;
{
int i;

for(i=0;i<lv;i++){
   v1[i]=alpha*v1[i]+beta*v2[i];
   }
return;
}

   
void mat3prod(m1,m2,m3)
double m1[3][3],m2[3][3],m3[3][3];
{
int i,j,k;

for(i=0;i<3;i++){
  for(j=0;j<3;j++){
    m3[i][j]=0.0;
    for(k=0;k<3;k++){
      m3[i][j] += m1[i][k]*m2[k][j];
      }
    }
  }
}

void mat3vec(m1,v1,v2)
double m1[3][3],v1[3],v2[3];
{
int i,k;

for(i=0;i<3;i++){
  v2[i]=0.0;
  for(k=0;k<3;k++){
    v2[i] += m1[i][k]*v1[k];
    }
  }
}

void mat3scal(m0,s0)
double m0[3][3],s0;
{
int i,j;

for(i=0;i<3;i++){
  for(j=0;j<3;j++){
    m0[i][j] *= s0;
    }
  }
}

double vec3prod(v1,v2)
double v1[3],v2[3];
{
int i;
double sc;

sc = 0.0;
for(i=0;i<3;i++){
  sc += v1[i]*v2[i];
  }
return(sc);
}

void vec3sum(v1,v2,v3)
double v1[3],v2[3],v3[3];
{
int i;

for(i=0;i<3;i++){
  v3[i] = v1[i] + v2[i];
  }
}

/* coorexact - to find a point (xp,yp) lying on a curve in a relative 
distance gamma between two other points (x1,y1) and (x2,y2) */
void coorexact(Indyk,pxp,pyp,x1,y1,x2,y2,gamma,xr1,xr2)
int Indyk; /*indicator which exact function to use*/
double *pxp,*pyp,x1,y1,x2,y2,gamma,xr1,xr2;
{
/*we need a double precision function which returns exact y coordinate
for a given point on the curve with specified x coordinate*/
double exacty();

double xp,yp,ye,vp1,vp2,xp1,yp1,ye1,xp2,yp2,ye2,alf,dokl;
int i,iprint,maxiter;

iprint=0;

dokl=1e-9;
maxiter=100;

/*kbw*/
if(iprint==1){
  printf("initial data for bisection: point1 ( %lf, %lf ), point2  ( %lf, %lf )\n",x1,y1,x2,y2);
}
/*kbw*/

/*check initial data */
if(fabs(y1-exacty(Indyk,x1,y1))>dokl||fabs(y2-exacty(Indyk,x2,y1))>dokl){
  printf("wrong input to coorexact! (%lf != %lf\n",y1,exacty(Indyk,x1,y1));
  exit(1);
}

/*specify the first point on a line segment between (x1,y1) and (x2,y2)*/
xp1=xp=gamma*x1+(1-gamma)*x2;
yp1=yp=gamma*y1+(1-gamma)*y2;
ye1=ye=exacty(Indyk,xp1,yp1);

/*kbw*/
if(iprint==1){
  printf("entering %lf bisection for point %lf, %lf (diff= %lf)\n",gamma,xp1,yp1,ye1-yp1);
}
/*kbw*/

/*maybe we are lucky enough to get it in one shot...*/
if(fabs(ye-yp)<dokl){
  *pxp = xp;
  *pyp = yp;
  return;
}

/*specify direction orthogonal to (x1,y1)(x2,y2) */
vp2 = x1-x2; 
vp1= -y1+y2; 

/*try to find the second point*/
alf=gamma;
if(1-gamma<alf) alf=1-gamma;

do{
  xp2=xp+alf*vp1;
  yp2=yp+alf*vp2;
  ye2=exacty(Indyk,xp2,yp2);

/*check we are on the right side of the curve*/
  if((yp1-ye1)*(yp2-ye2)>=0){
    alf *= -1;
    xp2=xp+alf*vp1;
    yp2=yp+alf*vp2;
    ye2=exacty(Indyk,xp2,yp2);
  }
  alf*=2;
} while((yp1-ye1)*(yp2-ye2)>0&&alf<1e3);

if(alf>=1e3) {
  printf("cannot find points on two sides of a curve in coorexact !\n");
  exit(1);
}

/*check we are not out of the range */
if(xp2<xr1){
  alf *= (xp-xr1)/(xp-xp2);
  xp2=xr1;
  yp2=yp+alf*vp2;
}
else if(xp2>xr2){
  alf *= (xp-xr2)/(xp-xp2);
  xp2=xr2;
  yp2=yp+alf*vp2;
}

 
/*kbw*/
if(iprint==1){
  printf("initial search 2 for point %lf, %lf (diff= %lf)\n",xp2,yp2,ye2);
}
/*kbw*/


for(i=1;i<maxiter;i++){

  xp = 0.5*(xp1 + xp2);
  yp = 0.5*(yp1 + yp2);
  ye = exacty(Indyk,xp,yp);

/*kbw*/
if(iprint==1){
  printf("after %d step of bisection for point %lf, %lf (diff= %lf)\n",i,xp,yp,ye-yp);
}
/*kbw*/

  if(fabs(ye-yp)<dokl){
    *pxp = xp;
    *pyp = yp;

/*kbw*/
if(iprint==1){
  printf("leaving bisection with point %lf, %lf (diff= %lf)\n",xp,yp,ye-yp);
}
/*kbw*/

    return;
  }

  if((yp1-ye1)*(yp-ye)>0){

    xp1=xp; yp1=yp;

  }
  else{

    xp2=xp; yp2=yp;

  }

}

printf("Bisection not succeded !\n");
getchar();
return;
}

/* to provide y-coordinate for points with given x-coordinate lying on:
Indyk = 1 or 2 - circle, Indyk = 3 - NACA 0012 wing profile */
double exacty(Indyk,xp,yp)
int Indyk;
/* xp - x-coordinate of a point, yp - guess for y-coordinate*/
double xp,yp;
{
double ye;
double xc,yc,rad,rad2,daux; 

if(Indyk==1||Indyk==2){

  if(Indyk==1){
/*circle with centre at (2,0) and radius 1*/
    xc=2.0;yc=0.0;rad=1.0;rad2=rad*rad;
  }
  else if(Indyk==2){
/*circle with centre at (2,0) and radius 0.5*/
    xc=2.0;yc=0.0;rad=0.5;rad2=rad*rad;
  }

  if((daux=rad2-(xp-xc)*(xp-xc))>0.0){
    ye = sqrt(daux);
  }
  else{
    ye=0.0;
  }
  if(yp<yc) ye *= -1;
  ye+=yc;
}
else if(Indyk==3){

  ye = 0.6*(0.2969*sqrt(xp)-0.126*xp-0.3516*xp*xp+0.2843*xp*xp*xp-0.1015*xp*xp*xp*xp);
  if(yp<0) ye *= -1;
}

return(ye);
}