#include<stdlib.h>
#include<stdio.h>

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
#include "papi.h"
#include "papi_driver_mth.h"
#endif

#define NO_TH 4 

#define MULT 80 

#define UNIT_SIZE  48 // optimal for Intel x86_64

#define NUM_ITER  10000000

#define LOCAL_SIZE (UNIT_SIZE*MULT/NO_TH)

#define ALIGNMENT 64 // assumed cache line size 

#define min(X,Y) ((X) < (Y) ?  (X) : (Y))

void init_counters(); // initialize time counters

double get_wallclock_seconds(); // using gettimeofday

double get_CPU_seconds(); // using getrusage

long get_page_faults() ; // using getrusage

double lg(double x); // log base 2

double function_fake(double * a, int n);
double result=0.0;

double global_time = 0.0;
double global_nr_oper = 0;
double global_sum = 0.0 ;

void pthread_control( void );
void * thread_task (void * arg_p);
void simple_barrier(void);
pthread_mutex_t mutex_return_results; 

//double *array_a, *array_b, *array_c;

void main( void ){

  double wallclock_time;

  size_t alignment =  ALIGNMENT; 
  size_t size_in_bytes = UNIT_SIZE*MULT*sizeof(double);

  //posix_memalign( (void **)&array_a, alignment, size_in_bytes);
  //array_a = (double *)_mm_malloc(size_in_bytes, ALIGNMENT);
  //array_b = (double *)_mm_malloc(size_in_bytes, ALIGNMENT);
  //array_c = (double *)_mm_malloc(size_in_bytes, ALIGNMENT);


#ifdef PAPI_TEST
  papi_driver_mth_init();
#endif


  wallclock_time = get_wallclock_seconds();

  pthread_control();

  wallclock_time = get_wallclock_seconds() - wallclock_time;

  printf("\nMain program - calculations based on local measurements (no system overhead)\n");
  printf("Time for executing %lf arithmetic operations:\n\t wallclock - %lf \n",
	 global_nr_oper, global_time/NO_TH);
  printf("Czas wykonania %lf operacji arytmetycznych:\n\t zegar - %lf\n",
	 global_nr_oper, global_time/NO_TH);
  printf("Wydajność: %lf GFlops\n", 1.0e-9*global_nr_oper/(global_time/NO_TH));
  printf("\n\n");

  printf("\nMain program - external measurements (include thread creation, etc.)\n");
  printf("Time for executing %lf arithmetic operations:\n\t wallclock - %lf (overhead %.2lf%%)\n",
	 global_nr_oper, wallclock_time, 
	 100*(wallclock_time-global_time/NO_TH)/(global_time/NO_TH));
  printf("Czas wykonania %lf operacji arytmetycznych:\n\t zegar - %lf (overhead %.2lf%%)\n",
	 global_nr_oper, wallclock_time, 
	 100*(wallclock_time-global_time/NO_TH)/(global_time/NO_TH));
  printf("Wydajność: %lf GFlops\n", global_nr_oper*1.0e-9/wallclock_time);

printf("Checksum %lf\n", result);
//  free(array_a);
//  free(array_b);
//  free(array_c);
}


// actual computations are done by individual threads (no communication)
// the only synchronisation is done for the purpose of time measurements
// (to make sure the computations are parallel, not only concurrent)
void * thread_task (void * arg_p)
{

  int tab_l = LOCAL_SIZE;
  int i, j, k;
  double wallclock_time;

  int my_id = *( (int *) arg_p ); 
  int my_first_index = LOCAL_SIZE*my_id;

#ifdef PAPI_TEST
  if(my_id>=0){
    int retval = PAPI_register_thread(  );
    if ( retval != PAPI_OK ) {
      printf( "Thread %d not registered! Exiting.\n", my_id);
      getchar(); getchar();
      exit(0);
    }
    papi_driver_mth_add_events(my_id);
  }
#endif

double array_a[UNIT_SIZE*MULT], array_b[UNIT_SIZE*MULT], array_c[UNIT_SIZE*MULT];

//printf("my_id %d, my_first_index %d, tab_l %d, array_size %d\n",
//my_id, my_first_index, tab_l, UNIT_SIZE*MULT);

  // table initialization
  //
  for(i=0; i<tab_l; i++){
    array_a[my_first_index+i] = 1.000001+0.0000001*i;
    array_b[my_first_index+i] = 1.000002+0.0000001*i;
    array_c[my_first_index+i] = 1.000003+0.0000001*i;
  }

  // warm up
  //
  //for(i=0;i<NUM_ITER;i++){
  //  for(k=0; k<tab_l; k++){
  //    array_a[my_first_index+k] = 1.00000001*array_a[my_first_index+k]+0.0000001;
  //  }
  //}
  //for(i=0; i<tab_l; i++){
  //  array_a[my_first_index+i] *= 0.000000001;
  //}

  //printf("before simple_barrier 1 - thread %d\n",my_id);
  //printf("przed simple_barrier 1 - watek %d\n",my_id);

  //simple_barrier();

// version 1 - outer 
#ifdef PAPI_TEST
    papi_driver_mth_reset_events(my_id);
    papi_driver_mth_start_events(my_id);
    double time_tmp = get_wallclock_seconds();
#endif


  wallclock_time = get_wallclock_seconds();

  // computations with time measurements
  //
  int repeat = MULT/NO_TH;

//printf("my_first_index %d, repeat %d, max %d, array_size%d\n",
//my_first_index, repeat, my_first_index+(repeat-1)*UNIT_SIZE+UNIT_SIZE, UNIT_SIZE*MULT);

  for(j=0; j<repeat; j++){
    
    int ijk = my_first_index+j*UNIT_SIZE;

    // to prevent compiler from loop unrolling for j
    if(array_a[ijk]<-1e-9) result += function_fake(&array_a[ijk], UNIT_SIZE);

// version 2 - inner
#ifdef PAPI_TEST_2
    papi_driver_mth_reset_events(my_id);
    papi_driver_mth_start_events(my_id);
    double time_tmp = get_wallclock_seconds();
#endif


    for(i=0;i<NUM_ITER;i++){

      for(k=0; k<UNIT_SIZE; k++){
	
	array_a[ijk+k] = 1.00000001*array_a[ijk+k]+0.000001; 
        //array_b[ijk+k] = 1.00000001*array_b[ijk+k]+0.000001;
        //array_c[ijk+k] = 1.00000001*array_c[ijk+k]+0.000001;

      }
    }

// outer PAPI test
}

#ifdef PAPI_TEST
    papi_driver_mth_stop_events(my_id);
    //papi_driver_mth_print_events(my_id);
    double clock_ratio = papi_return_clock_ratio_mth(my_id);
    time_tmp = get_wallclock_seconds() - time_tmp;
    double nominal_frequency=2.2;
    double frequency = nominal_frequency*clock_ratio;
    //double nr_oper_tmp = NUM_ITER*UNIT_SIZE*2.0*1; // inner test
    double nr_oper_tmp = 2.0*repeat*NUM_ITER*UNIT_SIZE*1.0; // outer test
    double flops_per_cycle = 1.e-9 * nr_oper_tmp / time_tmp / frequency;
    if(my_id==0) printf("\nthread %d: flops %12.0lf, time %.4lf, frequency %.2lf, flops_per_cycle %.2lf\n", 
           my_id, nr_oper_tmp, time_tmp, frequency, flops_per_cycle);

#endif

// inner PAPI test
//  }
  
  double nr_oper_local = 1 * tab_l * 2.0 * NUM_ITER;

  wallclock_time = get_wallclock_seconds() - wallclock_time;

  double sum = 0.0;
  for(k=0; k<tab_l; k++){
    sum += array_a[my_first_index+k] + array_b[my_first_index+k] + array_c[my_first_index+k] ; 
  }

  pthread_mutex_lock(&mutex_return_results);
  global_sum += sum; // data race
  global_time += wallclock_time; 
  global_nr_oper += nr_oper_local;
  pthread_mutex_unlock(&mutex_return_results);

  //printf("before simple_barrier 2 - thread %d\n",my_id);
  //printf("przed simple_barrier 2 - watek %d\n",my_id);

  // to coordinate displaying the results
  /* simple_barrier(); */

  /* pthread_mutex_lock(&mutex_return_results);  */

  /* printf("\nThread %d\n", my_id);  */
  /* printf("Result of arithmetic operations: %lf\n", sum); */
  /* printf("Wynik operacji arytmetycznych: %lf\n", sum); */
  /* printf("\n");  */
  /* printf("Time for executing %lf arithmetic operations:\n\t wallclock - %lf\n",  */
  /* 	 nr_oper_local, wallclock_time);  */
  /* printf("Czas wykonania %lf operacji arytmetycznych:\n\t zegar - %lf\n",  */
  /* 	 nr_oper_local, wallclock_time);  */
  /* printf("Wydajność: %lf GFlops\n", 1.0e-9*nr_oper_local/wallclock_time);  */
  /* printf("\n\n");  */

  /* pthread_mutex_unlock(&mutex_return_results);  */


  pthread_exit( (void *)0);

  //return(NULL);
}


// technical details
pthread_t threads_ids[NO_TH];
pthread_mutex_t mutex_simple_barrier; 
pthread_cond_t cond_simple_barrier;
int counter_simple_barrier=0; 


void pthread_control( void ){

  int i, local_th_id[NO_TH]; for(i=0;i<NO_TH;i++) local_th_id[i]=i; 

  pthread_mutex_init( &mutex_simple_barrier, NULL );
  pthread_cond_init( &cond_simple_barrier, NULL );

  for(i=0; i<NO_TH; i++ ) {
    pthread_create( &threads_ids[i], NULL, thread_task, (void *) &local_th_id[i] );
  }

  for(i=0; i<NO_TH; i++ ) pthread_join( threads_ids[i], NULL );

  //pthread_exit( NULL); 
  return; 
}


void simple_barrier(void){
  
  pthread_mutex_lock (&mutex_simple_barrier);
  counter_simple_barrier++;
  if(counter_simple_barrier<NO_TH) {
    //printf("counter %d, no_th %d\n",counter_simple_barrier, NO_TH);
    pthread_cond_wait( &cond_simple_barrier, &mutex_simple_barrier );
  } else {
    counter_simple_barrier = 0;
    pthread_cond_broadcast( &cond_simple_barrier );
  }
  pthread_mutex_unlock ( &mutex_simple_barrier );
  //printf("leaving barrier - thread %lu\n", pthread_self());
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

double function_fake(double * a, int n){
  
  int i;
  for(i=0;i<n;i++) {
    a[i] = a[i]*a[i]-3.0*a[i];
    if(a[i]>4.0) a[i]+=5*a[i];
  }
  return(a[0]+a[n]+a[n/2]);
  
}

