#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define WYMIAR 10000
#define ROZMIAR 100000000

void mat_vec(double* a, double* x, double* y, int n);

main ()
{
  static double a[ROZMIAR],x[WYMIAR],y[WYMIAR],z[WYMIAR];
  int n,i,j;
  const int ione=1;
  const double done=1.0;
  const double dzero=0.0;


  for(i=0;i<ROZMIAR;i++) a[i]=1.0*i/11110000.1;
  for(i=0;i<WYMIAR;i++) x[i]=1.0*(WYMIAR-i)/1010101.01;

  n=WYMIAR;
  printf("start time measurements\n");
  inicjuj_czas();
  mat_vec(a,x,y,n);
  drukuj_czas();
  printf("end time measurements\n");

  // test
  for(i=0;i<n;i++){
    z[i]=0.0;
    int in=i*n;
    for(j=0;j<n;j+=4){
      z[i]+=a[in+j]*x[j]+a[in+j+1]*x[j+1]+a[in+j+2]*x[j+2]+a[in+j+3]*x[j+3];
    }
  }

  int passed = 1;
  for(i=0;i<WYMIAR;i++){
    if(fabs(y[i]-z[i])>1.e-9*z[i]) {
      printf("For i=%d, y[i]=%lf != correct_result[i]=%lf. Exiting.\n",
	     i, y[i], z[i]);
      passed = 0;
    }
    //exit(0);
  }

  if(passed) printf("correctness test - passed\n");
  else printf("correctness test - failed\n");

  return 0;
}
