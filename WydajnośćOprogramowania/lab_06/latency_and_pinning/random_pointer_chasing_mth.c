#include <stdlib.h>
#include <stdio.h>
#include <sys/times.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include <pthread.h>


#include<sys/time.h>
#include<sys/resource.h>
static struct rusage rp;

static struct timeval tp;
static struct timezone tzp;

//#define PAPI_TEST
#ifdef PAPI_TEST
#include "papi_driver.h"
#endif

#define NO_TH 80
int sum=0; // for warming up thread system (see thread_task_empty)
void * thread_task_empty (void * arg_p);

#define SCALAR double // float and int require changes in the code

#define CACHE_LINE_SIZE 64 // 512 lines * 64 B = 32kB
#define ALIGNEMENT 64 // assumed cache line size 

#define MAX_STRIDE (16L*4096) // to separate subsequent accesses

// for multithreading
#define DEFAULT_REPEAT 400
#define DEFAULT_STRIDE 256
#define DEFAULT_WORKING_SIZE (1024*1024*8)

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

void pthread_control( void );
void * thread_task (void * arg_p);
void simple_barrier(void);
pthread_mutex_t mutex_return_results; 

void main( void ){

#ifdef PAPI_TEST
  papi_driver_mth_init();
#endif

  pthread_control();
  //int thread_id = 0;
  //thread_task(&thread_id);
}


void * thread_task (void * arg_p)
{

  int my_id = *( (int *) arg_p ); 

  long int i,j,k;

  int num_data_in_line = CACHE_LINE_SIZE/sizeof(SCALAR);
  
  //long int array_size = PAGE_SIZE*MULT; 
  long int array_size = DEFAULT_WORKING_SIZE; 
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
      papi_driver_mth_add_events();
#endif
  
  
  long int working_set_size;
  /* for (working_set_size = working_set_size_min;  */
  /*      working_set_size <= working_set_size_max;  */
  /*      working_set_size *= 2) { */
    
  working_set_size = DEFAULT_WORKING_SIZE;
  {

    long int stride;
    /* for (stride = 1; stride <= MAX_STRIDE ; stride *= 2) { // for cache test */
      //stride = PAGE_SIZE;  { // for page faults

    stride = DEFAULT_STRIDE; // * sizeof(SCALAR)
    {

      working_set_size = stride*(working_set_size/stride);

      //if(stride>=working_set_size) break;   

      memset (array, 0, sizeof(array)); /* initialize the array */

      // fill array with the index of the next visited element
      int index;
      for (index=0; index < working_set_size; index+=stride){
	array[index] = index + stride; /* pointer to next */
      }
      array[index-stride] = 0; /* loop back to beginning */

      srand(time(NULL)); // initialize random number generator
      
      if(index!=working_set_size) {printf("Error 123. Exiting!\n"); exit(0);}
      
      
      // permute pointers
      for (index=0; index < working_set_size-stride; index+=stride){
	int next = index+stride*((rand()%(working_set_size-2))/stride);
	if(next>working_set_size-3) next = next - working_set_size + stride;
	if(next==index || next==index+1 || next <= 0) {
	  continue;
	  //printf("Error 213. Exiting!\n"); exit(0);
	}
	//if(next==array[next]) {printf("Error 223. Exiting!\n"); exit(0);}
	if(next>=working_set_size-2) {printf("Error 222. Exiting!\n"); exit(0);}
	
	int true_next = array[next];
	array[next] = array[true_next];
	array[true_next] = array[index];
	array[index] = true_next; /* pointer to next */
      }
      
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
      
      //init_counters(); - for page faults only
      
#ifdef PAPI_TEST
      papi_driver_mth_reset_events();
      papi_driver_mth_start_events();
#endif
      
      //int repeat = 10000/(working_set_size/stride);
      int repeat = DEFAULT_REPEAT;
      if(repeat<1) repeat = 1;
      //int repeat = 1; // for large arrays
      long int steps = 0;
      //while (secwc < SINGLE_RUN_TIME) { 
	
	if (dummy>1000000) dummy *= 0.00000001;
	
	double secwc0 =  get_wallclock_seconds();
	
	long int istep=0;
	for (i = repeat; i != 0; i--) { 
	     
	  int nextstep = 0;
	  do {
	    nextstep = array[nextstep]; 
	    //dummy++;
	    istep++;
	    //if(repeat==i) printf("%d  ",nextstep);
	  } /* dependency */
	  while (nextstep != 0);

	  //if(i==repeat) printf("\n\n");
	  
	} /* for i */
	
	secwc += (get_wallclock_seconds()-secwc0);
	steps+=istep; /* number of while loop iterations */
	
	//} /* while sec */
      
      int nr_page_faults =  get_page_faults();

      for(j = 0; j < working_set_size; j ++) dummy += array[j];
      
      long int nr_accesses =  repeat*working_set_size/stride;
      if( (nr_accesses-steps)*1.0/steps >  0.001 ){
	printf("error 173627, nr_accesses %ld != steps %ld. Exiting\n",nr_accesses,steps);
	exit(0);
      }      

      //if(working_set_size == working_set_size_min ){
      //if(stride==1)
      /* { */
      /* 	printf("\narray_size[MB])  stride[B]  access_time[ns]  throughput[GB/s]  nr_steps\n"); */
      /* } */

      /* printf("%10.4f  %12ld %12.2lf %16.2lf %16ld    %le\n", */
      /* 	     working_set_size * (sizeof(SCALAR)/1024.0/1024.0), */
      /* 	     (stride * sizeof(SCALAR)), */
      /* 	     secwc * 1.e9 / nr_accesses, 1.e-9 * nr_accesses * sizeof(SCALAR) / secwc, */
      /* 	     steps, dummy); */
      
	
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



pthread_t threads_ids[NO_TH];
pthread_mutex_t mutex_simple_barrier; 
pthread_cond_t cond_simple_barrier;
int counter_simple_barrier=0; 

void * thread_task_dummy (void * arg_p);

void pthread_control( void ){

  int i, local_th_id[NO_TH]; for(i=0;i<NO_TH;i++) local_th_id[i]=i; 
  double CPU_time, wallclock_time;

  pthread_mutex_init( &mutex_simple_barrier, NULL );
  pthread_cond_init( &cond_simple_barrier, NULL );

  // warm up - creating and destroying threads
  for(i=0; i<NO_TH; i++ ) {
    pthread_create( &threads_ids[i], NULL, thread_task_empty, (void *) &local_th_id[i] );
  }
  
  for(i=0; i<NO_TH; i++ ) pthread_join( threads_ids[i], NULL );

  double time_dummy =  get_wallclock_seconds();
  for(i=0; i<NO_TH; i++ ) {
    pthread_create( &threads_ids[i], NULL, thread_task_dummy, (void *) &local_th_id[i] );
  }
  
  for(i=0; i<NO_TH; i++ ) pthread_join( threads_ids[i], NULL );
  time_dummy = get_wallclock_seconds() - time_dummy ;
  printf("External execution dummy time %lf\n", time_dummy);



  //CPU_time = time_CPU();
  wallclock_time = get_wallclock_seconds();
  //printf("External execution time %lf\n", wallclock_time);

  for(i=0; i<NO_TH; i++ ) {
    pthread_create( &threads_ids[i], NULL, thread_task, (void *) &local_th_id[i] );
  }

  for(i=0; i<NO_TH; i++ ) pthread_join( threads_ids[i], NULL );

  //CPU_time = time_CPU() - CPU_time;
  double tmp = get_wallclock_seconds();
  //printf("External execution time %lf\n", tmp);
  wallclock_time = tmp - wallclock_time;
  //wallclock_time = get_wallclock_seconds() - wallclock_time;

  /* int tab_l = LOCAL_SIZE; // the same as in thread_task */
  /* int nr_tables = 3; // must be adjusted to actual calculations  */
  /* unsigned nr_oper = 2*nr_tables*tab_l*num_iter*NO_TH;  */

  /* printf("\n\n"); */
  /* printf("Result of arithmetic operations: %lf\n", global_sum); */
  /* printf("Time for executing %ld arithmetic operations:\n\t CPU - %lf,  wallclock - %lf\n", */
  /* 	 nr_oper, CPU_time, wallclock_time); */
  /* printf("Czas wykonania %ld operacji arytmetycznych:\n\t CPU - %lf, zegar - %lf\n", */
  /* 	 nr_oper, CPU_time, wallclock_time); */
  /* printf("Performance/Wydajność: %lf GFlops\n", 1.0e-9*nr_oper/wallclock_time); */
  printf("External execution time %lf ( - dummy_time = %lf)\n", 
	 wallclock_time,wallclock_time - time_dummy);
  wallclock_time = wallclock_time - time_dummy;

  printf("\narray_size[MB])  stride[B]  access_time[ns]  throughput[GB/s]  nr_steps\n");
  
  long int repeat =  DEFAULT_REPEAT;
  int stride = DEFAULT_STRIDE;
  int working_set_size = DEFAULT_WORKING_SIZE;
  long int nr_accesses =  NO_TH*repeat*working_set_size/stride;
  //long int nr_accesses =  repeat*working_set_size/stride;
  
  printf("%10.4f  %12ld %12.4lf %16.4lf \n",
	 NO_TH*working_set_size * (sizeof(SCALAR)/1024.0/1024.0),
	 (stride * sizeof(SCALAR)),
	 wallclock_time * 1.e9 / nr_accesses, 
	 1.e-9 * nr_accesses * sizeof(SCALAR) / wallclock_time);
  printf("\n\n");
  
  pthread_exit( NULL);  
}

// not used in this version
void simple_barrier(void){
  
  pthread_mutex_lock (&mutex_simple_barrier);
  counter_simple_barrier++;
  if(counter_simple_barrier<NO_TH) {
    pthread_cond_wait( &cond_simple_barrier, &mutex_simple_barrier );
  } else {
    counter_simple_barrier = 0;
    pthread_cond_broadcast( &cond_simple_barrier );
  }
  pthread_mutex_unlock ( &mutex_simple_barrier );


}

void * thread_task_dummy (void * arg_p)
{

  int my_id = *( (int *) arg_p ); 

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
      papi_driver_mth_add_events();
#endif
  
  
  long int working_set_size;
  /* for (working_set_size = working_set_size_min;  */
  /*      working_set_size <= working_set_size_max;  */
  /*      working_set_size *= 2) { */
    
  working_set_size = DEFAULT_WORKING_SIZE;
  {

    long int stride;
    /* for (stride = 1; stride <= MAX_STRIDE ; stride *= 2) { // for cache test */
      //stride = PAGE_SIZE;  { // for page faults

    stride = DEFAULT_STRIDE; // * sizeof(SCALAR)
    {

      working_set_size = stride*(working_set_size/stride);

      //if(stride>=working_set_size) break;   

      memset (array, 0, sizeof(array)); /* initialize the array */

      // fill array with the index of the next visited element
      int index;
      for (index=0; index < working_set_size; index+=stride){
	array[index] = index + stride; /* pointer to next */
      }
      array[index-stride] = 0; /* loop back to beginning */

      srand(time(NULL)); // initialize random number generator
      
      if(index!=working_set_size) {printf("Error 123. Exiting!\n"); exit(0);}
      
      
      // permute pointers
      for (index=0; index < working_set_size-stride; index+=stride){
	int next = index+stride*((rand()%(working_set_size-2))/stride);
	if(next>working_set_size-3) next = next - working_set_size + stride;
	if(next==index || next==index+1 || next <= 0) {
	  continue;
	  //printf("Error 213. Exiting!\n"); exit(0);
	}
	//if(next==array[next]) {printf("Error 223. Exiting!\n"); exit(0);}
	if(next>=working_set_size-2) {printf("Error 222. Exiting!\n"); exit(0);}
	
	int true_next = array[next];
	array[next] = array[true_next];
	array[true_next] = array[index];
	array[index] = true_next; /* pointer to next */
      }
      
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
      
      //init_counters(); - for page faults only
      
#ifdef PAPI_TEST
      papi_driver_mth_reset_events();
      papi_driver_mth_start_events();
#endif
      
      //int repeat = 10000/(working_set_size/stride);
      int repeat = DEFAULT_REPEAT;
      if(repeat<1) repeat = 1;
      //int repeat = 1; // for large arrays
      long int steps = 0;
      //while (secwc < SINGLE_RUN_TIME) { 
	
	if (dummy>1000000) dummy *= 0.00000001;
	
	double secwc0 =  get_wallclock_seconds();
	
	long int istep=0;
	for (i = repeat; i != 0; i--) { 
	     
	  int nextstep = 0;
	  /* do { */
	  /*   nextstep = array[nextstep];  */
	  /*   //dummy++; */
	  /*   istep++; */
	  /*   //if(repeat==i) printf("%d  ",nextstep); */
	  /* } /\* dependency *\/ */
	  /* while (nextstep != 0); */

	  //if(i==repeat) printf("\n\n");
	  
	} /* for i */
	
	secwc += (get_wallclock_seconds()-secwc0);
	//steps+=istep; /* number of while loop iterations */
	
	//} /* while sec */
      
      int nr_page_faults =  get_page_faults();

      for(j = 0; j < working_set_size; j ++) dummy += array[j];
      
      /* long int nr_accesses =  repeat*working_set_size/stride; */
      /* if( (nr_accesses-steps)*1.0/steps >  0.001 ){ */
      /* 	printf("error 173627, nr_accesses %ld != steps %ld. Exiting\n",nr_accesses,steps); */
      /* 	exit(0); */
      /* }       */

      //if(working_set_size == working_set_size_min ){
      //if(stride==1)
      /* { */
      /* 	printf("\narray_size[MB])  stride[B]  access_time[ns]  throughput[GB/s]  nr_steps\n"); */
      /* } */

      /* printf("%10.4f  %12ld %12.2lf %16.2lf %16ld    %le\n", */
      /* 	     working_set_size * (sizeof(SCALAR)/1024.0/1024.0), */
      /* 	     (stride * sizeof(SCALAR)), */
      /* 	     secwc * 1.e9 / nr_accesses, 1.e-9 * nr_accesses * sizeof(SCALAR) / secwc, */
      /* 	     steps, dummy); */
      
	
    } /* for stride */
    
  } /* for working_set_size */
  
  free(array);

} /* main */


void * thread_task_empty (void * arg_p)
{

  int my_id = *( (int *) arg_p ); 

  sum+= my_id;

}
