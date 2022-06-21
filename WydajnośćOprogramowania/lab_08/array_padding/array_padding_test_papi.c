#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "pomiar_czasu.h"

//#define PAPI_TEST
#ifdef PAPI_TEST
#include "papi.h"
#include "papi_driver_mth.h"
#endif

int main ()
{
  
#ifdef PAPI_TEST
  papi_driver_mth_init();
  int thread_id = 0;
#endif

#ifdef PAPI_TEST
    int retval = PAPI_register_thread(  );
    if ( retval != PAPI_OK ) {
      printf( "Thread %d not registered! Exiting.\n", thread_id);
      getchar(); getchar();
      exit(0);
    }
    papi_driver_mth_add_events(thread_id);
#endif


  double *a;
  long i,j,k;
  const long ione=1;
  const double done=1.0;
  const double dzero=0.0;
  double t1, t2;
  
  size_t alignment =  64; 

  double suma=0.0;

  long imult=100, n;
  for(imult=128; imult<129; imult++){
  
    for(n=imult*64-2;n<=imult*64+2; n++){
    
    long WYMIAR = n;
    if(n%8==0) WYMIAR++;


    long ROZMIAR = n*WYMIAR;
    double nr_oper= (n*(n));
    
    posix_memalign( (void **)&a, alignment, ROZMIAR*sizeof(double));
    
    
    for(i=0;i<ROZMIAR;i++) a[i]=1.0e-10*i;

    
    printf("poczatek: size %d ( %lf MB )\n", n, ROZMIAR*sizeof(double)/1024./1024);

#ifdef PAPI_TEST
    papi_driver_mth_reset_events(thread_id);
    papi_driver_mth_start_events(thread_id);
#endif

    k=0;
    t1 = czas_zegara();
    //for(k=0; k<100; k++)
      {
    for(i=0;i<n;i++){
      for(j=0;j<n;j++){
	suma+=a[i*WYMIAR+j];
      }
    }
    a[k%ROZMIAR]=0.27*k;
    }
    t2 = czas_zegara(); 

    double frequency;
#ifdef PAPI_TEST
    papi_driver_mth_stop_events(thread_id);
    //papi_driver_mth_print_events(thread_id);
    double clock_ratio = papi_return_clock_ratio_mth(thread_id);
    double nominal_frequency=2.2;
    frequency = nominal_frequency*clock_ratio;
#endif

    
    printf("%10d%20.10lf%20.10lf%20.10lf%20.10lf\n", n,(t2-t1),frequency,
	   1000*1000*1000*(t2-t1)/(n*n),(n*n/1024./1024./1024.)/(t2-t1)/frequency);

#ifdef PAPI_TEST
    papi_driver_mth_reset_events(thread_id);
    papi_driver_mth_start_events(thread_id);
#endif
    
    k=0;
    t1 = czas_zegara();
    //for(k=0; k<100; k++)
    {
	//for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      for(i=0;i<n;i++){
	suma+=a[i*WYMIAR+j];
      }
    }
    a[k%ROZMIAR]=0.27*k;
    }
    t2 = czas_zegara(); 
    
#ifdef PAPI_TEST
    papi_driver_mth_stop_events(thread_id);
    //papi_driver_mth_print_events(thread_id);
    clock_ratio = papi_return_clock_ratio_mth(thread_id);
    nominal_frequency=2.2;
    frequency = nominal_frequency*clock_ratio;
#endif

    
    printf("%10d%20.10lf%20.10lf%20.10lf%20.10lf\n", n,(t2-t1),frequency,
	   1000*1000*1000*(t2-t1)/(n*n),(n*n/1024./1024./1024.)/(t2-t1)/frequency);

    
    free(a);
    
  }
  }

    printf("suma %lf\n", suma);
}
