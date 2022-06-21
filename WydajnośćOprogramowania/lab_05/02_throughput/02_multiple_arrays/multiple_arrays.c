#include <stdlib.h>
#include <stdio.h>
#include <emmintrin.h>

#include <sys/times.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include<sys/time.h>
#include<sys/resource.h>
static struct rusage rp;

static struct timeval tp;
static struct timezone tzp;

#define PAPI_TEST
#ifdef PAPI_TEST
#include "papi_driver.h"
#endif


#define SCALAR double // float and int require changes in the code

#define CACHE_LINE_SIZE 64 // 512 lines * 64 B = 32kB
#define ALIGNEMENT 64 // assumed cache line size 

//#define MAX_STRIDE (16L*16*4096) // stride==1 for throughput measurements 

// set array size as multiple of cache line sizes (64B)
//#define SIZE_ARRAY_IN_LINES 4400000 // just big enough to catch interesting dependencies
// or 4k pages
#define PAGE_SIZE (512L)	// *8B per double
#define MULT (16*16*16*16) // to define the range of array size for experiment

#define SINGLE_RUN_TIME 0.1 // in seconds - let it be reasonable

#define min(X,Y) ((X) < (Y) ?  (X) : (Y))

void init_counters(); // initialize time counters

double get_wallclock_seconds(); // using gettimeofday

double get_CPU_seconds(); // using getrusage

long get_page_faults() ; // using getrusage

double lg(double x); // log base 2


SCALAR funkcja(SCALAR * a, SCALAR* b, SCALAR* c, SCALAR* d, SCALAR* e, int n);


int main(int argc, char* argv[])
{
  int NN, ntimes, i, j, it;


  double t_s, rmstime;
  register SCALAR dot, dot1, sum_dot;
  const int L1 = 4096; // * 8B
  
  int num_data_in_line = CACHE_LINE_SIZE/sizeof(SCALAR);
  
  long int array_size = PAGE_SIZE*MULT; 
  size_t size_in_bytes = array_size*sizeof(SCALAR);
  //size_t size_in_bytes = SIZE_ARRAY_IN_LINES*CACHE_LINE_SIZE;
  //long int array_size = SIZE_ARRAY_IN_LINES*num_data_in_line;
  SCALAR* array_a;
  SCALAR* array_b;
  SCALAR* array_c;
  SCALAR* array_d;
  SCALAR* array_e;
  //array = malloc(array_size*sizeof(SCALAR));
  size_t alignment =  ALIGNEMENT; 
  posix_memalign( (void **)&array_a, alignment, size_in_bytes);
  posix_memalign( (void **)&array_b, alignment, size_in_bytes);
  posix_memalign( (void **)&array_c, alignment, size_in_bytes);
  posix_memalign( (void **)&array_d, alignment, size_in_bytes);
  posix_memalign( (void **)&array_e, alignment, size_in_bytes);

#ifdef PAPI_TEST
  papi_driver_init();
#endif

  long int N = array_size;
  
  int NN_min = 100;
  for(NN=NN_min;NN<N;NN*=sqrt(2.0)){     
    
    for(i=0; i<NN; i++)  {
      array_a[i] = sqrt((SCALAR)(i+1));
      array_b[i] = sqrt((SCALAR)(i+1));
      array_c[i] = sqrt((SCALAR)(i+1));
      array_d[i] = sqrt((SCALAR)(i+1));
      array_e[i] = sqrt((SCALAR)(i+1));
    }
    
    int NTIMES = 10*(15-lg(NN * sizeof(SCALAR)));
    if(NTIMES<1) NTIMES=1;
    //printf("N = %d, ntimes = %d\n",NN,NTIMES); 
    
#ifdef PAPI_TEST
      papi_driver_reset_events();
      papi_driver_start_events();
#endif

    double secwc = 0.0;
    double tt1=0.0;
    long int steps = 0;
    while (tt1 < SINGLE_RUN_TIME) {
      
      double tt = get_wallclock_seconds();
      
      int kk;
      for (kk=0; kk<NTIMES; kk++)
	{
	  
	  
	  for (j=0; j<NN; j++){
	    //a[j] = b[j]+d[j]*c[j];
	    array_a[j] = array_e[j]*array_b[j]+array_d[j]*array_c[j];
	  }
	  j=NN/2;	
	  rmstime = array_e[j]*array_d[j]+array_c[j]*array_a[j];
	  if (rmstime<-1.0e-4) rmstime+=funkcja(array_a,array_b,array_c,array_d,array_e,NN);
	  //printf("kk %d\n",kk);
	}
      
      tt1 += get_wallclock_seconds() - tt;
      steps++;    
  
    }

      double clock_ratio=1.0;
#ifdef PAPI_TEST
      papi_driver_stop_events();
      //papi_driver_print_events();
double papi_return_clock_ratio();
      clock_ratio = papi_return_clock_ratio();
#endif

    long int nr_access = 5L * NTIMES * NN * steps; 

// calculate latency in clock cycles (access time / frequency)
// frequency is calculated taken nominal frequency and frequency ration from PAPI 
// for Estera nominal frequency is 2.2 GHz 
// 
      double frequency = 2.2*clock_ratio;
      double latency = ( tt1 * 1.e9 / nr_access ) * (frequency);
//printf("frequency %lf\n", frequency);       

    if(NN==NN_min) {
      printf("size is for all 5 arrays, access time and latency are for a single unknown with size %1d [B]!\n", sizeof(SCALAR));
      printf("size: [nr_double], [MB], throughput[GB/s], [B/cycle], access_time[ns], latency [cycles], run time\n");
    }    
    printf("%10d %10.3lf %11.4lf (%4.2lfGHz) %8.2lf %14.4lf %10.4lf %20.14lf \n",
	   5*NN, 5*NN*sizeof(SCALAR)/1024.0/1024.0,
	   1.0E-09 * sizeof(SCALAR) * nr_access /(tt1), frequency,  sizeof(SCALAR)/latency, 
	   1.e9*tt1/(nr_access), latency,
	   tt1/NTIMES);
    
    
    rmstime += funkcja(array_a,array_b,array_c,array_d,array_e,NN);
    
  }
  
  printf("%lf\n",rmstime);
  return 0;
}



SCALAR funkcja(SCALAR * a, SCALAR* b, SCALAR* c, SCALAR* d, SCALAR* e, int n){
  
  int i;
  for(i=0;i<n;i++) {
    a[i] = b[i]*c[i]-e[i]*d[i];
    if(a[i]>b[i]) c[i]+=e[i]*d[i];
  }
  return(a[0]+a[n]+c[n/2]);
  
}



void init_counters(){
  getrusage(RUSAGE_SELF, &rp);
  gettimeofday(&tp,&tzp);
}

double get_wallclock_seconds() { /* to read time */
  struct tms rusage;
  
  struct timeval tk;
  struct timezone tzp;
  double daytime;
  
  gettimeofday(&tk, &tzp);
  
  daytime=(tk.tv_usec-tp.tv_usec)/1e6+tk.tv_sec-tp.tv_sec;
  
  return (daytime);
}

double get_CPU_seconds() { /* to read time */
  
  struct rusage rk;
  double cputime;
  
  getrusage(RUSAGE_SELF, &rk);
  
  cputime = (rk.ru_utime.tv_usec-rp.ru_utime.tv_usec)/1e6;
  cputime += rk.ru_utime.tv_sec-rp.ru_utime.tv_sec;
  
  return (cputime);
}

long get_page_faults() { /* to read time */
  
  struct rusage rk;
  long page_faults;
  
  getrusage(RUSAGE_SELF, &rk);
  
  page_faults = rk.ru_majflt - rp.ru_majflt;
  
  return (page_faults);
}


double lg(double x) { /* log base 2 */
  return (log(x)/log(2.0));
}

