#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void mat_vec(double* a, double* x, double* y, int n)
{
  
  int i,j;
  double t0,t1;  
  for(i=0;i<n;i+=2){
//double temp=0.0;
  register  double temp=0.0;
  register double temp2=0.0;
    int in=n*i;
    for(j=0;j<n;j+=2){
      t0=x[j];
      t1=x[j+1];
//temp+=a[in+j]*x[j];
      temp+=a[in+j]*t0+a[in+j+1]*t1;
      temp2 +=a[(i+1)*n+j]*t0+a[(i+1)*n+j+1]*t1;
    }
    y[i] = temp;
    y[i+1]=temp2;
  }
    
}
