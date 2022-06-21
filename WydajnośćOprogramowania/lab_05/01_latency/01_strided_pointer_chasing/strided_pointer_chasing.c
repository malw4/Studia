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
double papi_return_clock_ratio( void );
#endif

#define SCALAR int // float and double require changes in the code

#define CACHE_LINE_SIZE 64 // 512 lines * 64 B = 32kB
#define ALIGNEMENT 64 // assumed cache line size 

#define MAX_STRIDE (16L*4096) // to separate subsequent accesses

// set array size as multiple of cache line sizes (64B)
//#define SIZE_ARRAY_IN_LINES 4400000 // just big enough to catch interesting dependencies
// or 4k pages
#define PAGE_SIZE (1024L)	// *4B per int
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
  
  long int array_size =PAGE_SIZE*MULT; 
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
    for (stride = 1; stride <= MAX_STRIDE ; stride *= 2) { // for cache test
      //stride = PAGE_SIZE;  { // for page faults

      working_set_size = stride*(working_set_size/stride);

      // break for temporal locality - which we do not want to be present
      if(working_set_size/stride < 1024) break;
      if(stride>=working_set_size) break;   

      memset (array, 0, sizeof(array)); /* initialize the array */

      // fill array with the index of the next visited element
      int index;
      for (index=0; index < working_set_size; index+=stride){
	array[index] = index + stride; /* pointer to next */
      }
      array[index-stride] = 0; /* loop back to beginning */

      
      double secwc = 0; /* initialize time accumulator */
      
            
      double dummy=0;

      // warm up - only for cache test
      int wu_size = working_set_size;
      if(wu_size>67108864) wu_size = 67108864; // 256 MB - larger than LLC
      for(i=0; i < 10; i++) {
      	for (j = i; j < wu_size; j +=8) { // to visit every cache line
	  dummy+=array[j];
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
	
	if (dummy>1000000) dummy *= 0.00000001;
	
	double secwc0 =  get_wallclock_seconds();
	
	long int istep=0;
	for (i = repeat; i != 0; i--) { 
	     
	  int nextstep = 0;
	  do {
	    nextstep = array[nextstep]; 
	    //dummy++;
	    istep++;
	    //printf("%d\n",nextstep);
	  } /* dependency */
	  while (nextstep != 0);
	  
	} /* for i */
	
	secwc += (get_wallclock_seconds()-secwc0);
	steps+=istep; /* number of while loop iterations */
	
      } /* while sec */
      
     double clock_ratio=1.0;
#ifdef PAPI_TEST
      papi_driver_stop_events();
      //papi_driver_print_events();
      clock_ratio = papi_return_clock_ratio();
#endif

    long int nr_accesses =  steps;

// calculate latency in clock cycles (access time / frequency)
// frequency is calculated taken nominal frequency and frequency ration from PAPI
// for Estera nominal frequency is 2.2 GHz 
      double frequency = 2.2*clock_ratio;
      double latency = ( secwc * 1.e9 / nr_accesses ) * (frequency);

      int nr_page_faults =  get_page_faults();

      for(j = 0; j < working_set_size; j ++) dummy += array[j];
      
      //if(working_set_size == working_set_size_min ){
      if(stride==1){
        printf("access time and latency for a single unknown with size %1d [B]", sizeof(SCALAR));
        printf("\narray_size[MB])  stride[B]  access_time[ns]  latency[cycles]  throughput[GB/s] [B/cycle]  nr_steps      dummy\n");
      }

     printf("%11.4f  %10ld %10.2lf (%4.2lf GHz)     %8.2lf         %8.3lf    %6.3lf   %10ld    %le\n",
             working_set_size * (sizeof(SCALAR)/1024.0/1024.0),
             (stride * sizeof(SCALAR)),
             secwc * 1.e9 / nr_accesses, frequency, latency,
             1.e-9 * nr_accesses * sizeof(SCALAR) / secwc, sizeof(SCALAR)/latency,
             steps, dummy);
	
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

