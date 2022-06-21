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

#define SIZE_ARRAY_IN_LINES 1100000 // just big enough to catch interesting dependencies


#define min(X,Y) ((X) < (Y) ?  (X) : (Y))

void init_counters(); // initialize time counters

double get_wallclock_seconds(); // using gettimeofday

double get_CPU_seconds(); // using getrusage

long get_page_faults() ; // using getrusage

double lg(double x); // log base 2

void function_fake(SCALAR* a, SCALAR* suma_p);

void  print_throughput();

SCALAR suma=0;


#define OFFSET_LOOP_COUNT 54 // size of loop over different OFFSETs (54 - OFFSETs up to 1024, 1025)
#define AVERAGING_FACTOR 10 // number of repetitions for calculating average time (recreated arrays)

double throughput[AVERAGING_FACTOR*OFFSET_LOOP_COUNT];

#define NITER 100000
// for each OFFSET (one of OFFSET_LOOP_COUNT values computed for o_loop parameter
// there are AVERAGING_FACTOR experiments with different recreated arrays
// and for each array there are NITER repetitions of loop over cache lines
// (there are USED_CACHE_LINES lines visited in each iteration hence there are
// USED_CACHE_LINES*nr_iter data accesses for each value of OFFSET and each experiment

int main() {
  
  int i,j,k;
  
  SCALAR* array;
  
  int num_data_in_line = CACHE_LINE_SIZE/sizeof(SCALAR);
  
  size_t alignment = ALIGNEMENT;
  size_t size_in_bytes = SIZE_ARRAY_IN_LINES*CACHE_LINE_SIZE;
  int size = SIZE_ARRAY_IN_LINES*num_data_in_line;

#ifdef PAPI_TEST
  papi_driver_init();
#endif

  
  printf("\nIn infinite loop test combinations of OFFSET and USED_CACHE_LINES parameters\n");
  printf("(to finish just enter ^C)\n");

  /* int averaging=AVERAGING_FACTOR; int i_ave; */
  /* for(i_ave=0;i_ave<averaging;i_ave++){ */
  while (1) { // fake - no averaging for asociativity detection    
    // just infinite loop to repeat experiments until ^C

    posix_memalign( (void **)&array, alignment, size_in_bytes);
    
    int i;
    for(i=0;i<size;i++) array[i] = 3.14e-9; //*pow(i, 3.14);
    
    //printf("Dynamically allocated on %dB boundary, size %dB \n",  alignment, size);
    

    // two kinds of loop over parameters:
    // 1. OFFSET (constant USED_CACHE_LINES = 512 - for throughput)
    // 2. USED_CACHE_LINES (constant OFFSET=512 - for cache associativity detection)
    /* int o_loop; */
    /* for(o_loop=1;o_loop<OFFSET_LOOP_COUNT;o_loop+=1){ */
    {  // fake - no loop over OFFSETs - just one OFFSET selected for asociativity detection    

//#define OFFSET 1 // by how many lines we separate subsequent entries in array
      int OFFSET;
//#define USED_CACHE_LINES 512 // number of visited cache lines during computations
      int USED_CACHE_LINES;

      int nr_iter = NITER;

      // for throughput
      /* USED_CACHE_LINES = 512; */
      /* if(o_loop<33) OFFSET = o_loop; */
      /* else OFFSET = pow(2, o_loop/2-16)+o_loop%2; */
      /* nr_iter = NITER; */

      // for associativity detection (czache size 512 lines * 64B = 32kB)

      //printf("\nSpecify OFFSET (distance in cache lines between visited array entries) or ^C to stop: ");
      //scanf("%d", &OFFSET);
      printf("For predefined OFFSET equal to L1 cache size (32kB=512lines)...\n");
      OFFSET = 512;
      printf("Specify USED_CACHE_LINES (the total number of visited array lines) or ^C to stop: ");
      scanf("%d", &USED_CACHE_LINES);
      
      if((OFFSET+1)*USED_CACHE_LINES > SIZE_ARRAY_IN_LINES) {
	
	printf("OFFSET %d, USED_CACHE_LINES %d: %d > SIZE_ARRAY_IN_LINES %d\n",
	       OFFSET, USED_CACHE_LINES,
	       (OFFSET+1)*USED_CACHE_LINES, SIZE_ARRAY_IN_LINES);
	getchar();getchar();
	break;
      }
      
#ifdef PAPI_TEST
  papi_driver_reset_events();
  papi_driver_start_events();
#endif

      double time_total=get_wallclock_seconds();
      
      for(j=0;j<nr_iter;j++){
		
	int i_cache_line=0; 
	int i_loop;
	for(i_loop=0; i_loop < USED_CACHE_LINES; i_loop++){ // loop over cache lines 
	  
	  // USED_CACHE_LINES locations (lines) updated in the loop
	  // locations separated by OFFSET lines
	  // the required array size = USED_CACHE_LINES*OFFSET*num_data_in_line
	  // the acteual array size = SIZE_ARRAY_IN_LINES*num_data_in_line
	  
	  suma +=
	    array[ (i_cache_line)*(num_data_in_line) ];
	  
	  i_cache_line += OFFSET;
	  
	}   
      	
	//printf("%lf\n", time_total);
	if(suma<0) function_fake(array, &suma);
      
      } 	// nr_iter  
      
      time_total = get_wallclock_seconds() - time_total;

#ifdef PAPI_TEST
  papi_driver_stop_events();
  papi_driver_print_events();
#endif

      // no averaging for associativity detection
      //throughput[o_loop+i_ave*OFFSET_LOOP_COUNT] = 
      //1.e-9*USED_CACHE_LINES*nr_iter*sizeof(SCALAR)/time_total;
      
      
      long int nr_accesses =  1L*USED_CACHE_LINES*nr_iter;     
      printf("array_size[B]  stride[B]  stride[nr_lines]  access time  nr_accesses   dummy\n");
      printf("%10d %12d %12d %16.2f   %11ld  %le\n",
	     OFFSET * USED_CACHE_LINES *  num_data_in_line * sizeof(double),
	     OFFSET * num_data_in_line *  sizeof(double),
	     OFFSET,
	     time_total * 1e9 / (nr_accesses),
	     nr_accesses, suma);
          
    }
  
    free(array);
    
  }
  
  
  printf("suma %e\n",suma);
  //print_throughput();
  
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


void function_fake(SCALAR* array, SCALAR* suma_p)
{
  int size = SIZE_ARRAY_IN_LINES*CACHE_LINE_SIZE/sizeof(SCALAR);
  int i;
  for(i=0;i<size;i++) array[i+4]*=3.27*array[i];
  for(i=0;i<size;i++) suma+=array[i];
  for(i=0;i<size;i++) *suma_p+=array[i];
  printf(" in fake %e\n",suma);
}

void  print_throughput()
{

  int o_loop;
  for(o_loop=1;o_loop<OFFSET_LOOP_COUNT;o_loop++){
    
    double average_throughput = 0; int i_ave;
    for(i_ave=0;i_ave<AVERAGING_FACTOR;i_ave++){
      
      average_throughput += throughput[o_loop+i_ave*OFFSET_LOOP_COUNT];
      
    }
    
    int OFFSET;
    if(o_loop<33) OFFSET = o_loop;
    else OFFSET = pow(2, o_loop/2-16)+o_loop%2;
    
    printf("average_throughput for OFFSET (stride in lines) %d: %10.4lf GB/s\n", 
	   OFFSET, average_throughput/AVERAGING_FACTOR);
    
  }
  
}
