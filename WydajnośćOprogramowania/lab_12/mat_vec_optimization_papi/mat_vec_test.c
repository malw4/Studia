#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#ifdef _OPENMP
#include <omp.h>
#else
#error "This compiler does not understand OPENMP"
#endif

//#define PAPI_TEST
#ifdef PAPI_TEST
#include "papi.h"
#include "papi_driver_mth.h"
#endif

#define WYMIAR 10000
#define ROZMIAR (WYMIAR*WYMIAR)

void mat_vec(double* a, double* x, double* y, int n);

main ()
{
  //static double a[ROZMIAR],x[WYMIAR],y[WYMIAR],z[WYMIAR];
  double *a, *x, *y, *z;
  size_t size = WYMIAR;
  size_t alignment = 64;
  //a = (double *)_mm_malloc(size*size*sizeof(double), alignment);
  //x = (double *)_mm_malloc(size*sizeof(double), alignment);
  //y = (double *)_mm_malloc(size*sizeof(double), alignment);
  //z = (double *)_mm_malloc(size*sizeof(double), alignment);

  posix_memalign( (void **)&a, alignment, size*size*sizeof(double));
  posix_memalign( (void **)&x, alignment, size*sizeof(double));
  posix_memalign( (void **)&y, alignment, size*sizeof(double));
  posix_memalign( (void **)&z, alignment, size*sizeof(double));

  int n,i,j;
  const int ione=1;
  const double done=1.0;
  const double dzero=0.0;

#ifdef PAPI_TEST
  papi_driver_mth_init();
#endif

  for(i=0;i<ROZMIAR;i++) a[i]=1.0*i/11110000.1;
  for(i=0;i<WYMIAR;i++) x[i]=1.0*(WYMIAR-i)/1010101.01;

  n=WYMIAR;

  printf("start time measurements\n");
  double t1 = omp_get_wtime();
  mat_vec(a,x,y,n);
  double t2 = omp_get_wtime();
  printf("end time measurements\n");

  double nr_oper= (n*(n*2.0));
  double exec_time_ns = 1024*1024*1024*(t2-t1);
  printf("czas wykonania %.0lf operacji zmiennoprzecinkowych - %lf\n", nr_oper, t2-t1);
  printf("liczba dostepow: min %.0lf, max %.0lf, czas dostepu: min %lf, max %lf\n",
	 nr_oper, nr_oper*2, exec_time_ns/(nr_oper), exec_time_ns/(nr_oper/2.0));
  printf("GFLOPS = %lf,    GB/s = min %lf , max %lf \n\n", nr_oper/exec_time_ns,
	 1.0*n*n*sizeof(double)/exec_time_ns, 2.0*n*n*sizeof(double)/exec_time_ns);
/*  
  // test
  for(i=0;i<n;i++){
    z[i]=0.0;
    for(j=0;j<n;j++){
      z[i]+=a[i*n+j]*x[j];
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
  else printf("correctness test - failed\n");*/
/* */

  free(a);
  free(x);
  free(y);
  free(z);
  //_mm_free(a);
  //_mm_free(x);
  //_mm_free(y);
  //_mm_free(z);

  return 0;
}
