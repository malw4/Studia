#include <stdlib.h>
#include <stdio.h>
#include <sys/times.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>
#include <string.h>

//#define PAPI_TEST
#ifdef PAPI_TEST
#include "papi_driver.h"
#endif

#include<sys/time.h>
#include<sys/resource.h>
static struct rusage rp;

static struct timeval tp;
static struct timezone tzp;

#define min(X,Y) ((X) < (Y) ?  (X) : (Y))

void init_counters(); // initialize time counters

double get_wallclock_seconds(); // using gettimeofday

double get_CPU_seconds(); // using getrusage

long get_page_faults() ; // using getrusage

double lg(double x); // log base 2

int main() {
  
#define PAGE_SIZE 512	// *8B per double
#define MULT (16*16*16*16) // to define the range of array size for experiment
  
#define SINGLE_RUN_TIME 0.4 // in seconds - let it be reasonable
  
  long int i,j,k;
  //long int array_size = 1024L*PAGE_SIZE*MULT; // for page faults - adjust properly!!!
                                                 // approx. DRAM size
  long int array_size = PAGE_SIZE*MULT; // for cache test
  //long int working_set_size_min = array_size/2; // for page faults
  long int working_set_size_min = PAGE_SIZE;  // for cache test
  long int working_set_size_max = array_size;
  
  double* array = malloc(array_size*sizeof(double));
  //int* array = _mm_malloc(array_size*sizeof(int), 16);
  //int* array = malloc(array_size*sizeof(int));
  
#ifdef PAPI_TEST
  papi_driver_init();
#endif
  
  long int working_set_size;
  for (working_set_size = working_set_size_min; 
       working_set_size <= working_set_size_max; 
       working_set_size *= 2) {
    
    long int stride;
    //for (stride = 1; stride <= working_set_size ; stride *= 2) { // for cache test
    //stride = PAGE_SIZE;  { // for page faults
    stride = 1; { // for cache size detection
      
      double secwc = 0; /* initialize time accumulator */
      
      memset (array, 0, sizeof(array)); /* initialize the array */
      
      double dummy=0;
      
      // warm up - only for cache test
      int wu_size = working_set_size;
      if(wu_size>67108864) wu_size = 67108864; // 256 MB - larger than LLC
      for(i=0; i < 10; i++) {
      	for (j = i; j < wu_size; j +=8) { // to visit every cache line
      	  array[j]++; /* r+w one location in memory */
	  dummy++;
      	} /* for j */
      } /* for i */
      
#ifdef PAPI_TEST
      papi_driver_reset_events();
      papi_driver_start_events();
#endif
      
      init_counters();
      
      int repeat = 100; // repeat > 1 - only for cache test
      long int steps = 0;
      while (secwc < SINGLE_RUN_TIME) { 
	
	
	double secwc0 =  get_wallclock_seconds();
	
	for (i = repeat; i != 0; i--) { 
	  
	  for (j = 0; j < working_set_size; j += stride) {
	    
	    //dummy += array[j]; /* r+w one location in memory */
	    //array[j]+=dummy; /* r+w one location in memory */
	    array[j]++; /* r+w one location in memory */
	    //dummy++;
	    
	  } /* for j */
	  
	} /* for i */
	
	steps++; /* number of while loop iterations */
	secwc += (get_wallclock_seconds()-secwc0);
	
      } /* while sec */
      
      
#ifdef PAPI_TEST
      papi_driver_stop_events();
      papi_driver_print_events();
#endif
      
      int nr_page_faults =  get_page_faults();
      
      for(j = 0; j < working_set_size; j ++) dummy += array[j];
      
      long int nr_accesses =  1L * repeat * ((int) ceil((working_set_size*1.0)/stride)) * steps;     
      printf("log_2(array_size[B])  log_2(stride[B])  access time  nr_locations nr_steps nr_accesses   dummy\n");
      printf("%15.0f %17.0f %16.2f %13ld %8d  %11ld  %le\n",
	     lg(working_set_size * sizeof(double)),
	     //lg(working_set_size * sizeof(int)),
	     lg(stride * sizeof(double)),
	     //lg(stride * sizeof(int)),
	     //secwc * 1e9 / (steps*(working_set_size/stride))/repeat,
	     secwc * 1e9 / (nr_accesses),
	     working_set_size/stride, steps, nr_accesses, dummy);
      
    } /* dummy - stride==1 */
  } /* for working_set_size */
  free(array);
} /* main */

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

