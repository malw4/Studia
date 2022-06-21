//  papi_driver_mth.c - a framework for using PAPI API in a simple way
//                  assumes Intel x86 processor
//
//  papi_driver_mth_init - initialize PAPI for multithreading
//  
//  papi_driver_mth_add_events - initialize 7 counters (3 hardcoded - number of 
//                    instructions, number of core cycles, number of reference clock 
//                    cycles) and 4 free for user defined events (using papi_set_events() )
//  papi_driver_mth_reset_events - reset array entries for counting events
//  papi_driver_mth_start_events - to start counting events
//  papi_driver_mth_stop_events - to stop counting events
//  papi_driver_mth_print_events - to print the number of events collected 
//
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "papi.h"
#include "papi_driver_mth.h"


papi_events papi_event_mth[100][10]; // 10 structs with event data ...
static long long count[100][10] = {0}; // ... for 100 threads - should be enough...


// papi_driver_init - to initialize structures storing events data
void papi_driver_mth_init( void )
{

  int i, retval;
 
  /* Init the PAPI library */
  retval = PAPI_library_init(PAPI_VER_CURRENT);
  if (retval != PAPI_VER_CURRENT) { 
    printf("PAPI error %d: PAPI_VER_CURRENT %d\n", retval, PAPI_VER_CURRENT); 
    getchar();getchar();
  }
  
  // limit PAPI to current calling thread
  PAPI_thread_init(pthread_self);

  // PAPI_get_hardware_info
  // PAPI_get_real_cyc
  // PAPI_get_real_usec
  // PAPI_num_cmp_hwctrs
  // PAPI_num_hwctrs
}


void papi_driver_mth_add_events( int thread_id )
{

  int eventset=PAPI_NULL;
  // create eventset
  int retval=PAPI_create_eventset(&eventset);
  if (retval!=PAPI_OK) { 
    printf("PAPI error in PAPI_create_eventset for thread %d, retval %d\n", 
	   thread_id, retval); 
  }
  else printf("PAPI success in PAPI_create_eventset  %d\n", eventset);

  papi_event_mth[thread_id][0].eventset = eventset;
  // create structures for events and assign events to eventset
  papi_set_user_events_mth(eventset, thread_id);

}


void papi_driver_mth_reset_events(  int thread_id ){

  int i;
  for(i=0; i<number_of_events; i++){
    papi_event_mth[thread_id][i].number_of_results = 0;
    papi_event_mth[thread_id][i].high_result = 0;
    papi_event_mth[thread_id][i].low_result = -1;
    papi_event_mth[thread_id][i].sum_of_results = 0;
  }

  int eventset = papi_event_mth[thread_id][0].eventset;
  int retval=PAPI_reset(eventset);
  if (retval!=PAPI_OK) { printf("PAPI error in PAPI_reset %d\n", retval); }

}


void papi_driver_mth_start_events(  int thread_id ){
  
  int eventset = papi_event_mth[thread_id][0].eventset;
  int retval=PAPI_start(eventset);
  if (retval!=PAPI_OK) { printf("PAPI error in PAPI_start %d\n", retval); }
  
}

void papi_driver_mth_stop_events(  int thread_id ){

  int i;

  int eventset = papi_event_mth[thread_id][0].eventset;
  int retval=PAPI_stop(eventset, count[thread_id]);
  if (retval!=PAPI_OK) { printf("PAPI error in PAPI_stop %d\n", retval); }

  for(i=0; i<number_of_events; i++){

    papi_event_mth[thread_id][i].number_of_results++;
    papi_event_mth[thread_id][i].current_result = count[thread_id][i];
    if(papi_event_mth[thread_id][i].current_result>papi_event_mth[thread_id][i].high_result){
      papi_event_mth[thread_id][i].high_result = papi_event_mth[thread_id][i].current_result;
    }
    if(papi_event_mth[thread_id][i].low_result==-1 || 
       papi_event_mth[thread_id][i].current_result<papi_event_mth[thread_id][i].low_result){
      papi_event_mth[thread_id][i].low_result = papi_event_mth[thread_id][i].current_result;
    }
    papi_event_mth[thread_id][i].sum_of_results += papi_event_mth[thread_id][i].current_result;


  }

}

void papi_driver_mth_print_events(  int thread_id ){

  printf("\n");

  int i;
  for(i=0; i<number_of_events; i++){

    printf("PAPI results event %d:\n", i);

    printf("\tlow %16ld,     high %16ld,     average %16ld\n",
	   papi_event_mth[thread_id][i].low_result, papi_event_mth[thread_id][i].high_result,
	   papi_event_mth[thread_id][i].sum_of_results/papi_event_mth[thread_id][i].number_of_results);
  }
  printf("\n");

}
