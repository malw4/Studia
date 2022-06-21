//  papi_driver.h - a framework for using PAPI API in a simple way
//                  assumes Intel x86 processor
//
//  papi_driver_init - initialize 7 counters (3 hardcoded - number of instructions,
//                     number of core cycles, number of reference clock cycles)
//                     and 4 free for user defined events (using papi_set_user_events() )
//  
//  papi_driver_reset_events - reset array entries for counting events
//  papi_driver_start_events - to start counting events
//  papi_driver_stop_events - to stop counting events
//  papi_driver_print_events - to print the number of events collected 
//
//

typedef struct papi_events{

  char name[100];
  int number_of_results;
  long long current_result;
  long long high_result;
  long long low_result;
  long long sum_of_results;

} papi_events;

extern papi_events papi_event[10]; // 10 structs with event data - should be enough...


static const int number_of_events = 7; // for these simple version of using PAPI API


void papi_driver_init( void );

void papi_driver_reset_events( void );

void papi_driver_start_events( void );

void papi_driver_stop_events( void );

void papi_driver_print_events( void );


// function to be defined in papi_set_user_events.c - specific to each tested code
// (possibly changed for different runs to collect different data)
void papi_set_user_events( int eventset );

