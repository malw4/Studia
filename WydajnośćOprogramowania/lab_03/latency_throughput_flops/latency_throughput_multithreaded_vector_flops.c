#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include"uth_time.h"
 
#define NO_TH 4

const int num_iter = 100000000;

double global_time = 0.0;
double global_nr_oper = 0;
double global_sum = 0.0 ;

void pthread_control( void );
void * thread_task (void * arg_p);
void simple_barrier(void);
pthread_mutex_t mutex_return_results; 


void main( void ){

  double CPU_time, wallclock_time;

  CPU_time = time_CPU();
  wallclock_time = time_clock();

  pthread_control();

  CPU_time = time_CPU() - CPU_time;
  wallclock_time = time_clock() - wallclock_time;

  printf("\nMain program - calculations based on local measurements (no system overhead)\n");
  printf("Time for executing %lf arithmetic operations:\n\t wallclock - %lf \n",
	 global_nr_oper, global_time/NO_TH);
  printf("Czas wykonania %lf operacji arytmetycznych:\n\t zegar - %lf\n",
	 global_nr_oper, global_time/NO_TH);
  printf("Wydajność: %lf GFlops\n", 1.0e-9*global_nr_oper/(global_time/NO_TH));
  printf("\n\n");

  printf("\nMain program - external measurements (include thread creation, etc.)\n");
  printf("Time for executing %lf arithmetic operations:\n\t CPU - %lf, wallclock - %lf\n",
	 global_nr_oper, CPU_time, wallclock_time);
  printf("Czas wykonania %lf operacji arytmetycznych:\n\t CPU - %lf, zegar - %lf\n",
	 global_nr_oper, CPU_time, wallclock_time);
  printf("Wydajność: %lf GFlops\n", global_nr_oper*1.0e-9/wallclock_time);

}


// should be optimal (at least for recent Intel architectures)
#define LOCAL_SIZE 16

// actual computations are done by individual threads (no communication)
// the only synchronisation is done for the purpose of time measurements
// (to make sure the computations are parallel, not only concurrent)
void * thread_task (void * arg_p)
{

  double a_tab[LOCAL_SIZE], b_tab[LOCAL_SIZE], c_tab[LOCAL_SIZE], d_tab[LOCAL_SIZE];
  int tab_l = LOCAL_SIZE;
  int i, j, k;
  double CPU_time, wallclock_time;

  int my_id = *( (int *) arg_p ); 

  // table initialization
  //
  for(i=0; i<tab_l; i++){
    a_tab[i] = 1.000001+0.0000001*i;
    b_tab[i] = 1.000002+0.0000001*i;
    c_tab[i] = 1.000003+0.0000001*i;
    d_tab[i] = 1.000004+0.0000001*i;
    //_tab[i] = 1.000005+0.0000001*i;
  }

  // warm up
  //
  for(i=0;i<num_iter;i++){
    for(k=0; k<tab_l; k++){
      a_tab[k] = 1.00000001*a_tab[k]+0.0000001;
    }
  }
  for(i=0; i<tab_l; i++){
    a_tab[i] *= 0.000000001;
  }

  //printf("before simple_barrier 1 - thread %d\n",my_id);
  //printf("przed simple_barrier 1 - watek %d\n",my_id);

  simple_barrier();

  CPU_time = time_CPU();
  wallclock_time = time_clock();

  // computations with time measurements
  //
  for(i=0;i<num_iter;i++){
    
    for(k=0; k<tab_l; k++){
      a_tab[k] = 1.00000001*a_tab[k]+0.000001; 
      //}
      //for(k=0; k<tab_l; k++){
      b_tab[k] = 1.00000001*b_tab[k]+0.000001; 
      //}
      //for(k=0; k<tab_l; k++){
      c_tab[k] = 1.00000001*c_tab[k]+0.000001; 
      //}
      //for(k=0; k<tab_l; k++){
      //d_tab[k] = 1.000001*d_tab[k]+0.000001; 
    }
    
  }
  
  double nr_oper_local = 3 * tab_l * 2.0 * num_iter;

  CPU_time = time_CPU() - CPU_time;
  wallclock_time = time_clock() - wallclock_time;

  double sum = 0.0;
  for(k=0; k<tab_l; k++){
    sum += a_tab[k] + b_tab[k] + c_tab[k] + d_tab[k];
  }

  pthread_mutex_lock(&mutex_return_results);
  global_sum += sum; // data race
  global_time += wallclock_time; 
  global_nr_oper += nr_oper_local;
  pthread_mutex_unlock(&mutex_return_results);

  //printf("before simple_barrier 2 - thread %d\n",my_id);
  //printf("przed simple_barrier 2 - watek %d\n",my_id);

  // to coordinate displaying the results
  simple_barrier();

  pthread_mutex_lock(&mutex_return_results); 

  printf("\nThread %d\n", my_id); 
  printf("Result of arithmetic operations: %lf\n", sum);
  printf("Wynik operacji arytmetycznych: %lf\n", sum);
  printf("\n"); 
  printf("Time for executing %lf arithmetic operations:\n\t CPU - %lf, wallclock - %lf\n", 
  	 nr_oper_local, CPU_time, wallclock_time); 
  printf("Czas wykonania %lf operacji arytmetycznych:\n\t CPU - %lf, zegar - %lf\n", 
  	 nr_oper_local, CPU_time, wallclock_time); 
  printf("Wydajność: %lf GFlops\n", 1.0e-9*nr_oper_local/wallclock_time); 
  printf("\n\n"); 

  pthread_mutex_unlock(&mutex_return_results); 


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

