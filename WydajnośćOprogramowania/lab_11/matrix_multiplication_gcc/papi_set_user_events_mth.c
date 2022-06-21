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
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "papi.h"
#include "papi_driver_mth.h"


/* All pre-defined events: */
/* Adding PAPI_L1_DCM   successful */
/* Adding PAPI_L1_ICM   successful */
/* Adding PAPI_L2_DCM   successful */
/* Adding PAPI_L2_ICM   successful */
/* Adding PAPI_L1_TCM   successful */
/* Adding PAPI_L2_TCM   successful */
/* Adding PAPI_L3_TCM   successful */
/* Adding PAPI_CA_SNP   successful */
/* Adding PAPI_CA_SHR   successful */
/* Adding PAPI_CA_CLN   successful */
/* Adding PAPI_CA_INV   successful */
/* Adding PAPI_CA_ITV   successful */
/* Adding PAPI_L3_LDM   successful */
/* Adding PAPI_TLB_DM   successful */
/* Adding PAPI_TLB_IM   successful */
/* Adding PAPI_L1_LDM   successful */
/* Adding PAPI_L1_STM   successful */
/* Adding PAPI_L2_LDM   successful */
/* Adding PAPI_L2_STM   successful */
/* Adding PAPI_PRF_DM   successful */
/* Adding PAPI_MEM_WCY  successful */
/* Adding PAPI_STL_ICY  successful */
/* Adding PAPI_FUL_ICY  successful */
/* Adding PAPI_STL_CCY  successful */
/* Adding PAPI_FUL_CCY  successful */
/* Adding PAPI_BR_UCN   successful */
/* Adding PAPI_BR_CN    successful */
/* Adding PAPI_BR_TKN   successful */
/* Adding PAPI_BR_NTK   successful */
/* Adding PAPI_BR_MSP   successful */
/* Adding PAPI_BR_PRC   successful */
/* Adding PAPI_TOT_INS  successful */
/* Adding PAPI_LD_INS   successful */
/* Adding PAPI_SR_INS   successful */
/* Adding PAPI_BR_INS   successful */
/* Adding PAPI_RES_STL  successful */
/* Adding PAPI_TOT_CYC  successful */
/* Adding PAPI_LST_INS  successful */
/* Adding PAPI_L2_DCA   successful */
/* Adding PAPI_L3_DCA   successful */
/* Adding PAPI_L2_DCR   successful */
/* Adding PAPI_L3_DCR   successful */
/* Adding PAPI_L2_DCW   successful */
/* Adding PAPI_L3_DCW   successful */
/* Adding PAPI_L2_ICH   successful */
/* Adding PAPI_L2_ICA   successful */
/* Adding PAPI_L3_ICA   successful */
/* Adding PAPI_L2_ICR   successful */
/* Adding PAPI_L3_ICR   successful */
/* Adding PAPI_L2_TCA   successful */
/* Adding PAPI_L3_TCA   successful */
/* Adding PAPI_L2_TCR   successful */
/* Adding PAPI_L3_TCR   successful */
/* Adding PAPI_L2_TCW   successful */
/* Adding PAPI_L3_TCW   successful */
/* Adding PAPI_SP_OPS   successful */
/* Adding PAPI_DP_OPS   successful */
/* Adding PAPI_VEC_SP   successful */
/* Adding PAPI_VEC_DP   successful */
/* Adding PAPI_REF_CYC  successful */


// to assign entries in papi_events array to specific events
void papi_set_user_events_mth(  int thread_id, int eventset )
{

  int i, retval;

  for(i=0; i<number_of_events; i++){

    switch(i){

    case 0:
      strncpy(papi_event_mth[thread_id][0].name, "PAPI_REF_CYC", 100);
      // Fixed counters:
      //   CPU_CLK_UNHALTED.   REF_TSC     REF_XCLK            ->  PAPI_REF_CYC
      //   CPU_CLK_UNHALTED.   THREAD (_P) .CORE (_P) ???
      //   INST_RETIRED.ANY                                    ->  PAPI_TOT_INS
      break;

    case 1:
      strncpy(papi_event_mth[thread_id][1].name, "PAPI_TOT_CYC", 100);
      //strncpy(papi_event_mth[thread_id][1].name, "PAPI_TOT_INS", 100);
      break;

    case 2:
      strncpy(papi_event_mth[thread_id][2].name, "MEM_UOPS_RETIRED.ALL_LOADS", 100);
      //strncpy(papi_event_mth[thread_id][2].name, "MEM_UOPS_RETIRED.ALL_STORES", 100);
      //strncpy(papi_event_mth[thread_id][2].name, "MEM_LOAD_UOPS_RETIRED.L1_HIT", 100);

// MEM_UOPS_RETIRED.ALL_LOADS = MEM_LOAD_UOPS_RETIRED.L1_HIT + MEM_LOAD_UOPS_RETIRED.L1_MISS + MEM_LOAD_UOPS_RETIRED.HIT_LFB
// MEM_LOAD_UOPS_RETIRED.L1_MISS = MEM_LOAD_UOPS_RETIRED.L2_HIT + MEM_LOAD_UOPS_RETIRED.L2_MISS
// MEM_LOAD_UOPS_RETIRED.L2_MISS = MEM_LOAD_UOPS_RETIRED.L3_HIT + MEM_LOAD_UOPS_RETIRED.L3_MISS
// L1D.REPLACEMENT - OK
// L2_LINES_IN.ALL - OK
// ? L2_LINES_IN.ALL = OFFCORE_RESPONSE_0:ANY_DATA:ANY_RFO:L3_HIT:SNP_ANY + OFFCORE_RESPONSE_0:ANY_DATA:ANY_RFO:L3_MISS_LOCAL:SNP_ANY ???

      break;

    case 3:
      //strncpy(papi_event_mth[thread_id][3].name, "MEM_UOPS_RETIRED.ALL_LOADS", 100);
      //strncpy(papi_event_mth[thread_id][3].name, "MEM_UOPS_RETIRED.ALL_STORES", 100);
      strncpy(papi_event_mth[thread_id][3].name, "L1D.REPLACEMENT", 100);
      //strncpy(papi_event_mth[thread_id][3].name, "L2_LINES_IN.ALL", 100);
      //strncpy(papi_event_mth[thread_id][3].name, "MEM_LOAD_UOPS_RETIRED.L1_HIT", 100);
      //strncpy(papi_event_mth[thread_id][3].name, "MEM_LOAD_UOPS_RETIRED.L1_MISS", 100);
      //strncpy(papi_event_mth[thread_id][3].name, "MEM_LOAD_UOPS_RETIRED.L2_HIT", 100);
      //strncpy(papi_event_mth[thread_id][3].name, "MEM_LOAD_UOPS_RETIRED.L2_MISS", 100);
      //strncpy(papi_event_mth[thread_id][3].name, "MEM_LOAD_UOPS_RETIRED.L3_HIT", 100);
      //strncpy(papi_event_mth[thread_id][3].name, "MEM_LOAD_UOPS_RETIRED.L3_MISS", 100);
      //strncpy(papi_event_mth[thread_id][3].name, "MEM_LOAD_UOPS_L3_MISS_RETIRED.LOCAL_DRAM", 100); 
      break;

    case 4:
      //strncpy(papi_event_mth[thread_id][4].name, "L1D.REPLACEMENT", 100);
      strncpy(papi_event_mth[thread_id][4].name, "L2_LINES_IN.ALL", 100);
      //strncpy(papi_event_mth[thread_id][4].name, "MEM_LOAD_UOPS_RETIRED.L1_MISS", 100); 
      //strncpy(papi_event_mth[thread_id][4].name, "MEM_LOAD_UOPS_RETIRED.L2_HIT", 100);
      //strncpy(papi_event_mth[thread_id][4].name, "MEM_LOAD_UOPS_RETIRED.L2_MISS", 100);
      //strncpy(papi_event_mth[thread_id][4].name, "MEM_LOAD_UOPS_RETIRED.L3_HIT", 100);
      //strncpy(papi_event_mth[thread_id][4].name, "MEM_LOAD_UOPS_RETIRED.L3_MISS", 100);
      //strncpy(papi_event_mth[thread_id][4].name, "MEM_LOAD_UOPS_L3_MISS_RETIRED.LOCAL_DRAM", 100); 
      //strncpy(papi_event_mth[thread_id][4].name, "OFFCORE_RESPONSE_0:ANY_DATA:ANY_RFO:L3_HIT:SNP_ANY", 100);
      //strncpy(papi_event_mth[thread_id][4].name, "OFFCORE_RESPONSE_0:ANY_DATA:ANY_RFO:L3_MISS_LOCAL:SNP_ANY", 100);

      //strncpy(papi_event_mth[thread_id][4].name, "L2_RQSTS.DEMAND_DATA_RD_MISS", 100); 
//   Demand data read requests that missed L2, no rejects.
      //strncpy(papi_event_mth[thread_id][4].name, "L2_RQSTS.DEMAND_DATA_RD_HIT", 100); 
//   Demand data read requests that hit L2 cache.
      //strncpy(papi_event_mth[thread_id][4].name, "L2_RQSTS.ALL_DEMAND_DATA_RD", 100); 
//   Counts any demand and L1 HW prefetch data load requests to L2.
      //strncpy(papi_event_mth[thread_id][4].name, "L2_RQSTS.RFO_HIT", 100); 
//   Counts the number of store RFO requests that hit the L2 cache.
      //strncpy(papi_event_mth[thread_id][4].name, "L2_RQSTS.RFO_MISS", 100); 
//   Counts the number of store RFO requests that miss the L2 cache.
      //strncpy(papi_event_mth[thread_id][4].name, "L2_RQSTS.ALL_RFO", 100); 
//   Counts all L2 store RFO requests.
      //strncpy(papi_event_mth[thread_id][4].name, "L2_RQSTS.ALL_DEMAND_MISS", 100); 
//   Demand requests that miss L2 cache.
      //strncpy(papi_event_mth[thread_id][4].name, "L2_RQSTS.ALL_DEMAND_REFERENCES", 100); 
//   Demand requests to L2 cache.
      //strncpy(papi_event_mth[thread_id][4].name, "L2_RQSTS.L2_PF_HIT", 100); 
//  Counts all L2 HW prefetcher requests that hit L2.
      //strncpy(papi_event_mth[thread_id][4].name, "L2_RQSTS.L2_PF_MISS", 100); 
//  Counts all L2 HW prefetcher requests that missed L2.
      //strncpy(papi_event_mth[thread_id][4].name, "L2_RQSTS.ALL_PF", 100); 
//  Counts all L2 HW prefetcher requests.
      //strncpy(papi_event_mth[thread_id][4].name, "L2_RQSTS.MISS", 100); 
//  All requests that missed L2.
      //strncpy(papi_event_mth[thread_id][4].name, "L2_RQSTS.REFERENCES", 100); 
//  All requests to L2 cache.


      break;

    case 5:
      //strncpy(papi_event_mth[thread_id][5].name, "MEM_LOAD_UOPS_RETIRED.L1_MISS", 100); 
// Retired load uops missed L1 cache as data sources.
      //strncpy(papi_event_mth[thread_id][5].name, "MEM_LOAD_UOPS_RETIRED.L2_MISS", 100); 
// Retired load uops missed L2. Unknown data source
      //strncpy(papi_event_mth[thread_id][5].name, "MEM_LOAD_UOPS_RETIRED.L3_MISS", 100); 
// Retired load uops missed L3. Excludes unknown data 
      //strncpy(papi_event_mth[thread_id][5].name, "MEM_LOAD_UOPS_RETIRED.HIT_LFB", 100); 
// Retired load uops which data sources were load uops missed L1 but hit FB due to preceding miss 
//                                                 to the same cache line with data not ready.
      //strncpy(papi_event_mth[thread_id][5].name, "MEM_LOAD_UOPS_L3_HIT_RETIRED.XSNP_MISS", 100); 
// Retired load uops which data sources were L3 hit and cross-core snoop missed in on-pkg core cache.
      //strncpy(papi_event_mth[thread_id][5].name, "MEM_LOAD_UOPS_L3_HIT_RETIRED.XSNP_HIT", 100); 
// Retired load uops which data sources were L3 and cross-core snoop hits in on-pkg core cache.
      //strncpy(papi_event_mth[thread_id][5].name, "MEM_LOAD_UOPS_L3_HIT_RETIRED.XSNP_HITM", 100); 
// Retired load uops which data sources were HitM responses from shared L3.
      //strncpy(papi_event_mth[thread_id][5].name, "MEM_LOAD_UOPS_L3_HIT_RETIRED.XSNP_NONE", 100); 
// Retired load uops which data sources were hits in L3 without snoops required.
      //strncpy(papi_event_mth[thread_id][5].name, "MEM_LOAD_UOPS_L3_MISS_RETIRED.LOCAL_DRAM", 100); 
// Retired load uops which data sources missed L3 but ...
      //strncpy(papi_event_mth[thread_id][5].name, "LONGEST_LAT_CACHE.MISS", 100); 
      //strncpy(papi_event_mth[thread_id][5].name, "LONGEST_LAT_CACHE.REFERENCE", 100); 
      //strncpy(papi_event_mth[thread_id][5].name, "OFFCORE_REQUESTS_OUTSTANDING.ALL_DATA_RD", 100); // ONLY WITHOUT HT
      //strncpy(papi_event_mth[thread_id][5].name, "OFFCORE_REQUESTS.ALL_DATA_RD", 100); // ONLY WITHOUT HT

// Molka events:

// L1
// perf::L1-DCACHE-LOADS - depends on the width of access                              (== MEM_UOPS_RETIRED.ALL_LOADS ?)
      //strncpy(papi_event_mth[thread_id][5].name, "perf::L1-DCACHE-LOADS", 100);
// perf::L1-DCACHE-STORES - depends on the width of access
      //strncpy(papi_event_mth[thread_id][5].name, "perf::L1-DCACHE-STORES", 100);

// L1-L2
// perf::L1-DCACHE-LOAD-MISSES - counts lines brought to L1 (reads and RFO for writes) (== L1D.REPLACEMENT ?)
      //strncpy(papi_event_mth[thread_id][5].name, "perf::L1-DCACHE-LOAD-MISSES", 100);
// L2_TRANS:L1D_WB - lines written back from L1 to L2
      //strncpy(papi_event_mth[thread_id][5].name, "L2_TRANS:L1D_WB", 100);
// L2_TRANS:(ALL_)DEMAND_DATA_RD + L2_TRANS:RFO - lines brought from L2 to L1
      //strncpy(papi_event_mth[thread_id][5].name, "L2_TRANS:ALL_DATA_RD", 100);
      //strncpy(papi_event_mth[thread_id][5].name, "L2_TRANS:RFO", 100);
//                             

// L2
// OFFCORE_RESPONSE_0:ANY_DATA:ANY_RFO:L3_HIT:SNP_ANY - ???
      //strncpy(papi_event_mth[thread_id][5].name, "OFFCORE_RESPONSE_0:ANY_DATA:ANY_RFO:L3_HIT:SNP_ANY", 100);
// OFFCORE_RESPONSE_0:ANY_DATA:ANY_RFO:L3_MISS_LOCAL:SNP_ANY - local DRAM ???
      strncpy(papi_event_mth[thread_id][5].name, "OFFCORE_RESPONSE_0:ANY_DATA:ANY_RFO:L3_MISS_LOCAL:SNP_ANY", 100);
// OFFCORE_RESPONSE_0/1:ANY_DATA:ANY_RFO:L3_MISS_REMOTE_HOP1:L3_MISS_REMOTE_HOP2:SNP_ANY
      //strncpy(papi_event_mth[thread_id][5].name, "", 100);
// sum of the three above -> data read from uncore (L3) to the core

// L2_TRANS:L2_WB - data written from the core to uncore (L3?)
      //strncpy(papi_event_mth[thread_id][5].name, "L2_TRANS:L2_WB", 100);
// L2_LINES_IN 
      //strncpy(papi_event_mth[thread_id][5].name, "L2_LINES_IN", 100);

// no way to measure DRAM transfers by OFFCORE_RESPONSE

// + events for memory latency

      break;

    case 6:
      //strncpy(papi_event_mth[thread_id][6].name, "MEM_LOAD_UOPS_L3_MISS_RETIRED.LOCAL_DRAM", 100);
      break;

    }

    papi_event_mth[thread_id][i].number_of_results = 0;
    papi_event_mth[thread_id][i].high_result = 0;
    papi_event_mth[thread_id][i].low_result = -1;
    papi_event_mth[thread_id][i].sum_of_results = 0;

    retval=PAPI_add_named_event(eventset,papi_event_mth[thread_id][i].name);
    if (retval!=PAPI_OK) { 
      printf("PAPI error in creating event %d: %s\n",
	     i, papi_event_mth[thread_id][i].name); 
    }
    else{    
      printf("PAPI success in creating event %d: %s\n",
	     i, papi_event_mth[thread_id][i].name); 
    }
  }


}

double papi_return_clock_ratio_mth( int thread_id ){

  double clock_ratio = (double)papi_event_mth[thread_id][1].sum_of_results/(double)papi_event_mth[thread_id][0].sum_of_results;

  return (clock_ratio);

}
