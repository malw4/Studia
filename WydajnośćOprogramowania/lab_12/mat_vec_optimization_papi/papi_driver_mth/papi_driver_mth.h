//  papi_driver_mth.h - a framework for using PAPI API in a simple way
//                  assumes Intel x86 processor and pthreads multithreading
//
//  papi_driver_mth_init - initialize 7 counters (2 hardcoded - number of instructions,
//                     number of reference clock cycles) and the rest free
//                     for user defined events (using papi_set_user_events() )
//  
//  papi_driver_mth_reset_events - reset array entries for counting events
//  papi_driver_mth_start_events - to start counting events
//  papi_driver_mth_stop_events - to stop counting events
//  papi_driver_mth_print_events - to print the number of events collected 
//
//

typedef struct papi_events{

  int eventset;
  char name[100];
  int number_of_results;
  long long current_result;
  long long high_result;
  long long low_result;
  long long sum_of_results;

} papi_events;

extern papi_events papi_event_mth[100][10]; // 10 structs with event data ...
 // ... for 100 threads - should be enough...


static const int number_of_events = 7; // for these simple version of using PAPI API


void papi_driver_mth_init( void );

void papi_driver_mth_add_events( int thread_id );

void papi_driver_mth_reset_events( int thread_id );

void papi_driver_mth_start_events( int thread_id );

void papi_driver_mth_stop_events( int thread_id );

void papi_driver_mth_print_events( int thread_id );


// function to be defined in papi_set_user_events.c - specific to each tested code
// (possibly changed for different runs to collect different data)
void papi_set_user_events_mth( int thread_id, int eventset );

