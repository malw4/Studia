//  papi_driver.c - a framework for using PAPI API in a simple way
//                  assumes Intel x86 processor
//
//  papi_driver_init - initialize 7 counters (3 hardcoded - number of instructions,
//                     number of core cycles, number of reference clock cycles)
//                     and 4 free for user defined events (using papi_set_events() )
//  
//  papi_driver_reset_events - reset array entries for counting events
//  papi_driver_start_events - to start counting events
//  papi_driver_stop_events - to stop counting events
//  papi_driver_print_events - to print the number of events collected 
//
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "papi.h"
#include "papi_driver.h"

static int eventset=PAPI_NULL;

papi_events papi_event[10]; // 10 structs with event data - should be enough...

static long long count[10] = {0};


// papi_driver_init - to initialize structures storing events data
void papi_driver_init( )
{

  int i, retval;
 
  /* Init the PAPI library */
  retval = PAPI_library_init(PAPI_VER_CURRENT);
  if (retval != PAPI_VER_CURRENT) { 
    printf("PAPI error %d: PAPI_VER_CURRENT %d\n", retval, PAPI_VER_CURRENT); 
    getchar();getchar();
  }
  
  // limit to current thread
  PAPI_thread_init(pthread_self);

  // PAPI_get_hardware_info
  // PAPI_get_real_cyc
  // PAPI_get_real_usec
  // PAPI_num_cmp_hwctrs
  // PAPI_num_hwctrs

  // create eventset
  retval=PAPI_create_eventset(&eventset);
  if (retval!=PAPI_OK) { printf("PAPI error in PAPI_create_eventset  %d\n", retval); }
  else printf("PAPI success in PAPI_create_eventset  %d\n", eventset);

  // create structures for events and assign events to eventset
  papi_set_user_events(eventset);

}


void papi_driver_reset_events( void ){

  int i;
  for(i=0; i<number_of_events; i++){
    papi_event[i].number_of_results = 0;
    papi_event[i].high_result = 0;
    papi_event[i].low_result = -1;
    papi_event[i].sum_of_results = 0;
  }

  int retval=PAPI_reset(eventset);
  if (retval!=PAPI_OK) { printf("PAPI error in PAPI_reset %d\n", retval); }

}


void papi_driver_start_events( void ){
  
  int retval=PAPI_start(eventset);
  if (retval!=PAPI_OK) { printf("PAPI error in PAPI_start %d\n", retval); }
  
}

void papi_driver_stop_events( void ){

  int i;

  int retval=PAPI_stop(eventset, count);
  if (retval!=PAPI_OK) { printf("PAPI error in PAPI_stop %d\n", retval); }

  for(i=0; i<number_of_events; i++){

    papi_event[i].number_of_results++;
    papi_event[i].current_result = count[i];
    if(papi_event[i].current_result>papi_event[i].high_result){
      papi_event[i].high_result = papi_event[i].current_result;
    }
    if(papi_event[i].low_result==-1 || papi_event[i].current_result<papi_event[i].low_result){
      papi_event[i].low_result = papi_event[i].current_result;
    }
    papi_event[i].sum_of_results += papi_event[i].current_result;


  }

}

void papi_driver_print_events( void ){

  printf("\n");

  int i;
  for(i=0; i<number_of_events; i++){

    printf("PAPI results event %d:\n", i);

    printf("\tlow %16ld,     high %16ld,     average %16ld\n",
	   papi_event[i].low_result, papi_event[i].high_result,
	   papi_event[i].sum_of_results/papi_event[i].number_of_results);
  }
  printf("\n");

}
