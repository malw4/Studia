#include <stdlib.h>
#include <stdio.h>
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

//#define PAPI_TEST
#ifdef PAPI_TEST
#include "papi_driver.h"
#endif


#define SCALAR double // float and int require changes in the code

#define CACHE_LINE_SIZE 64 // 512 lines * 64 B = 32kB
#define ALIGNEMENT 64 // assumed cache line size 

#define MAX_STRIDE (16L*4096) // to separate subsequent accesses

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


int main() {
  
  long int i,j,k;
  
  int num_data_in_line = CACHE_LINE_SIZE/sizeof(SCALAR);
  
  long int array_size = PAGE_SIZE*MULT; 
  size_t size_in_bytes = array_size*sizeof(SCALAR);
  //size_t size_in_bytes = SIZE_ARRAY_IN_LINES*CACHE_LINE_SIZE;
  //long int array_size = SIZE_ARRAY_IN_LINES*num_data_in_line;
  SCALAR* array;
  array = malloc(array_size*sizeof(SCALAR));
  //size_t alignment =  ALIGNEMENT; 
  //posix_memalign( (void **)&array, alignment, size_in_bytes);
  
  //long int working_set_size_min = array_size/2; // for page faults
  long int working_set_size_min = PAGE_SIZE;  // for cache test
  long int working_set_size_max = array_size;
  
   
#ifdef PAPI_TEST
  papi_driver_init();
#endif
  
  long int working_set_size;
  for (working_set_size = working_set_size_min; 
       working_set_size <= working_set_size_max; 
       working_set_size *= 2) {
    
    long int stride;
    //stride = 1; { // several accesses per line possible
    //stride = num_data_in_line; { // only one access per cache line
    for (stride = 1; stride <= MAX_STRIDE ; stride *= 2) { 
      
      // break for temporal locality - which we do not want to be present
      if(working_set_size/stride < 1024) break;
      if(stride>=working_set_size) break;   

      double secwc = 0; /* initialize time accumulator */
      
      memset (array, 0, sizeof(array)); /* initialize the array */
           
      SCALAR dummy=0;
      
      // warm up - only for cache test
      int wu_size = working_set_size;
      if(wu_size>67108864) wu_size = 67108864; // 256 MB - larger than LLC
      for(i=0; i < 10; i++) {
	for (j = i; j < wu_size; j +=8) { // to visit every cache line
	  array[j]++; /* r+w one location in memory */
	  dummy++;
	} /* for j */
      } /* for i */
      
      init_counters();
      
#ifdef PAPI_TEST
      papi_driver_reset_events();
      papi_driver_start_events();
#endif
      
      int repeat = 1000/(working_set_size/stride);
      if(repeat<1) repeat = 1;
      //int repeat = 1; // for large arrays
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
	
	secwc += (get_wallclock_seconds()-secwc0);
	steps++; /* number of while loop iterations */
	
      } /* while sec */
      
#ifdef PAPI_TEST
      papi_driver_stop_events();
      papi_driver_print_events();
#endif
      
      int nr_page_faults =  get_page_faults();
      
      for(j = 0; j < working_set_size; j ++) dummy += array[j]/1e18;
      
      
      long int nr_accesses =  2L * repeat * ((int) ceil((working_set_size*1.0)/stride)) * steps; 
      
      //if(working_set_size == working_set_size_min ){
      if(stride==1){
	printf("\narray_size[MB])  stride[B]  access_time[ns]  throughput[GB/s]  nr_steps\n");
      }

      printf("%10.4f  %12ld %12.2lf %16.2lf %16ld    %le\n",
	     working_set_size * (sizeof(SCALAR)/1024.0/1024.0),
	     (stride * sizeof(SCALAR)),
	     secwc * 1.e9 / nr_accesses, 1.e-9 * nr_accesses * sizeof(SCALAR) / secwc,
	     steps*repeat, dummy);
      
	
    } /* for stride */
    
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

