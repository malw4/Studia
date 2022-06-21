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

    int i,j;   
#pragma omp for
    for(i=0;i<n;i++){
      y[i]=0.0;
      for(j=0;j<n;j++){
	y[i]+=a[i*n+j]*x[j];
      }
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
