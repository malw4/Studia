#include <stdio.h>
#include <stdlib.h>
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

void mat_vec(double* a, double* x, double* y, int n)
{
  
  // __assume_aligned(a, 64);
  // __assume_aligned(x, 64);
  // __assume_aligned(y, 64);
  

#pragma omp parallel default(none) shared(a,x,y,n)
  {
    
    int thread_id = omp_get_thread_num();
    
#ifdef PAPI_TEST
    int retval = PAPI_register_thread(  );
    if ( retval != PAPI_OK ) {
      printf( "Thread %d not registered! Exiting.\n", thread_id);
      getchar(); getchar();
      exit(0);
    }
    papi_driver_mth_add_events(thread_id);
#endif
    
#ifdef PAPI_TEST
  if(thread_id>=0){
    papi_driver_mth_reset_events(thread_id);
    papi_driver_mth_start_events(thread_id);
  }
#endif

    register int i;
#pragma omp for
    for(i=0;i<n;i+=4){
      
      register int j;
      register double ty1 = 0;
      register double ty2 = 0;
      register double ty3 = 0;
      register double ty4 = 0;
      for(j=0;j<n;j+=4){
	register double t0=x[j];
	register double t1=x[j+1];
	register double t2=x[j+2];
	register double t3=x[j+3];
	register int n2=2*n;
	register int n3=3*n;
	register int k= i*n+j;
	ty1  +=a[k]*t0    +a[k+1]*t1  +a[k+2]*t2 +a[k+3]*t3;
	ty2+=a[k+n]*t0+a[k+1+n]*t1+a[k+2+n]*t2+a[k+3+n]*t3;
	ty3+=a[k+n2]*t0+a[k+1+n2]*t1+a[k+2+n2]*t2+a[k+3+n2]*t3;
	ty4+=a[k+n3]*t0+a[k+1+n3]*t1+a[k+2+n3]*t2+a[k+3+n3]*t3;
      }
      y[i]  = ty1;
      y[i+1]=ty2;
      y[i+2]=ty3;
      y[i+3]=ty4;
    }
    
#ifdef PAPI_TEST
    if(thread_id>=0){
      papi_driver_mth_stop_events(thread_id);
#pragma omp critical(print_1)
      {
	printf("thread %d: RESULTS\n", thread_id);
	papi_driver_mth_print_events(thread_id);
      }
    }

    PAPI_unregister_thread();
#endif
    
  }

}

