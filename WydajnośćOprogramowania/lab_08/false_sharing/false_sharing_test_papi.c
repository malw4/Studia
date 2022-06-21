#include <stdlib.h>
#include <stdio.h>

#include <sys/times.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <pthread.h>

//#define PAPI_TEST
#ifdef PAPI_TEST
#include "papi.h"
#include "papi_driver_mth.h"
#endif

#include<sys/time.h>
#include<sys/resource.h>
static struct rusage rp;

static struct timeval tp;
static struct timezone tzp;

#define NO_TH 8

#define STRIDE 8

#define NITER 100 

void pthread_control( void );
void * thread_task (void * arg_p);
void simple_barrier(void);
pthread_mutex_t mutex_return_results; 

#define min(X,Y) ((X) < (Y) ?  (X) : (Y))

void init_counters(); // initialize time counters

double get_wallclock_seconds(); // using gettimeofday

double get_CPU_seconds(); // using getrusage

void pthread_control_false_sharing( void );
void * thread_task_false_sharing (void * arg_p);

#define ARRAY_SIZE (1024*1024) // to fit into cache
double suma=0.0; 

void funkcja_fake(double* aa, double* ba, double* ca, double* da)
{
  double suma=0.0;
  int i;
  for(i=0;i<ARRAY_SIZE;i++) {
    suma += aa[i]*ba[i]-ca[i];
    suma -= da[i]*aa[i];
  }
  printf(" in fake %e\n",suma);
}

double *a, *b, *c, *d;

int main( void ){
  
#ifdef PAPI_TEST
  papi_driver_mth_init();
#endif
  
  pthread_mutex_init( &mutex_return_results, NULL );
  
  size_t alignment = 64; 
  //size_t alignment = 4096; 
  size_t size_in_bytes = ARRAY_SIZE*sizeof(double);
  
  posix_memalign( (void **)&a, alignment, size_in_bytes);
  posix_memalign( (void **)&b, alignment, size_in_bytes);
  posix_memalign( (void **)&c, alignment, size_in_bytes);
  posix_memalign( (void **)&d, alignment, size_in_bytes);
  
  int i,j,k;
  
  int sign = 1;
  for(i=0;i<ARRAY_SIZE;i++) {
    sign = (-1)*sign;
    a[i]=0.0;
    b[i]=-sign*7.25e-6*i;
    c[i]=sign*sign*i*1e-9;
    d[i]=-sign*(3.14+i)/1e9;
  }
  
  
  suma=0.0;
  for(i=0;i<ARRAY_SIZE;i++) suma+=a[i]+b[i]+c[i]+d[i];
  printf("checksum before %e\n",suma);

  double time = get_wallclock_seconds();
  
  pthread_control_false_sharing();
  //thread_task_false_sharing(&thread_id);
  
  time = get_wallclock_seconds()-time;

  suma=0.0;
  for(i=0;i<ARRAY_SIZE;i++) suma+=a[i]+b[i]+c[i]+d[i];
  printf("checksum after %e, execution time %lf\n",suma,time);
  printf("liczba dostepow %d, przepustowosc %lf GB/s\n",
	 2*NITER*ARRAY_SIZE, 2*1.e-9*NITER*ARRAY_SIZE*sizeof(double)/time);
  
  free(a);
  free(b);
  free(c);
  free(d);
}


void * thread_task_false_sharing (void * arg_p){
  
  int thread_id = *((int *)arg_p);
  printf("thread %d, START!!!!!!!!!!!!!!!!!\n", thread_id);
  
#ifdef PAPI_TEST
  if(thread_id>=0){
    int retval = PAPI_register_thread(  );
    if ( retval != PAPI_OK ) {
      printf( "Thread %d not registered! Exiting.\n", thread_id);
      getchar(); getchar();
      exit(0);
    }
    papi_driver_mth_add_events(thread_id);
  }
#endif
  
  
#ifdef PAPI_TEST
  if(thread_id>=0){
    papi_driver_mth_reset_events(thread_id);
    papi_driver_mth_start_events(thread_id);
  }
#endif
  
  double t = get_wallclock_seconds();
  
  int i,j,k;
  
  for(j=0;j<NITER;j++){
    
    for(i=thread_id*ARRAY_SIZE/NO_TH;i<(thread_id+1)*ARRAY_SIZE/NO_TH;i++) {
      a[STRIDE*thread_id]+=j*c[i]*c[i];
      if(a[STRIDE*thread_id]<0) funkcja_fake(a,b,c,d);
    }
    
  }
  
  t = get_wallclock_seconds()-t;
  
#ifdef PAPI_TEST
  if(thread_id>=0){
    papi_driver_mth_stop_events(thread_id);
    pthread_mutex_lock(&mutex_return_results);
    printf("thread %d: RESULTS\n", thread_id);
    papi_driver_mth_print_events(thread_id);
    pthread_mutex_unlock(&mutex_return_results);
  }
#endif
  
  simple_barrier();  
  double suma=0.0; 
  //for(i=0;i<ARRAY_SIZE;i++) suma+=af[i]+bf[i]+cf[i]+df[i]+ef[i];
  for(i=0;i<ARRAY_SIZE;i++) suma+=a[i];
  printf("thread %d, checksum %e\n", thread_id, suma);
  
  printf("liczba dostepow %d, czas %lf, przepustowosc %lf GB/s\n",
	 2*NITER*ARRAY_SIZE, t, 2*1.e-9*NITER*ARRAY_SIZE*sizeof(double)/t);
  
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

pthread_t threads_ids[NO_TH];
pthread_mutex_t mutex_simple_barrier; 
pthread_cond_t cond_simple_barrier;
int counter_simple_barrier=0; 

void pthread_control_false_sharing( void ){
  
  int i, local_th_id[NO_TH]; for(i=0;i<NO_TH;i++) local_th_id[i]=i; 
  double CPU_time, wallclock_time;
  
  pthread_mutex_init( &mutex_simple_barrier, NULL );
  pthread_cond_init( &cond_simple_barrier, NULL );
  
  for(i=0; i<NO_TH; i++ ) {
    pthread_create( &threads_ids[i], NULL, thread_task_false_sharing, (void *) &local_th_id[i] );
  }
  
  for(i=0; i<NO_TH; i++ ) pthread_join( threads_ids[i], NULL );
  
  //pthread_exit( NULL);  
}


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

