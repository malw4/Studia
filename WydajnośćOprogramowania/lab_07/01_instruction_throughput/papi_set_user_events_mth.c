//  papi_driveri_mth.c - a framework for using PAPI API in a simple way - for multithreaded
//                  execution (assumes Intel x86 processor and Pthreads)
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


// Molka events:

// L1
// perf::L1-DCACHE-LOADS - depends on the width of access
// perf::L1-DCACHE-STORES - depends on the width of access

// L1-L2
// perf::L1-DCACHE-LOAD-MISSES - counts lines brought to L1 (reads and RFO for writes)
// perf::L1-DCACHE-LOAD-MISSES = L2 HIT + L3 HIT + L3 MISS (components are incorrect)
// L2_TRANS:L1D_WB - lines written back from L1 to L2
// L2_TRANS:(ALL_)DEMAND_DATA_RD + L2_TRANS:RFO - lines brought from L2 to L1
// perf::L1-DCACHE-LOAD-MISSES read-> L2_TRANS:(ALL_)DEMAND_DATA_RD - ALL with HW prefetch
//                             write->  L2_TRANS:RFO

// L2
// OFFCORE_RESPONSE_0:ANY_DATA:ANY_RFO:L3_HIT:SNP_ANY - ???
// OFFCORE_RESPONSE_0:ANY_DATA:ANY_RFO:L3_MISS_LOCAL:SNP_ANY - local DRAM ???
// OFFCORE_RESPONSE_0/1:ANY_DATA:ANY_RFO:L3_MISS_REMOTE_HOP1:L3_MISS_REMOTE_HOP2:SNP_ANY
// sum of the three above -> data read from uncore (L3) to the core
// L2_TRANS:L2_WB - data written from the core to uncore (L3?)
// L2_LINES_IN ????????

// no way to measure DRAM transfers by OFFCORE_RESPONSE

// L3
// UNC_C_LLC_LOOKUP:WRITE - lines written to L3
// ( UNC_C_LLC_LOOKUP:ANY - UNC_C_LLC_LOOKUP:WRITE ) - lines read from L3 (demand and RFO) 
// UNC_C TOR_INSERTS:OPCODE:OPC_DRD / OPC_RFO - lines read from L3 (demand and RFO)

// DRAM
// UNC_H_REQUESTS:READS - lines read from memory controller (DRAM?)
// UNC H IMC WRITES:FULL - lines written to memory controller (DRAM?)
// UNC_Q_RXL_FLITS_G1:DRS_DATA - QPI traffic IN (8 events per line)
// UNC_Q_TXL_FLITS_G1:DRS_DATA - QPI traffic OUT (8 events per line)

// + events for memory latency


// to assign entries in papi_events array to specific events
void papi_set_user_events_mth( int thread_id, int eventset )
{

  int i, retval;

  for(i=0; i<number_of_events; i++){

    switch(i){

/* PAPI success in creating event 0: PAPI_TOT_CYC */
/* PAPI success in creating event 1: PAPI_L1_TCM */
/* PAPI success in creating event 2: L1D:REPLACEMENT */
/* PAPI success in creating event 3: MEM_LOAD_UOPS_RETIRED.L1_HIT */
/* PAPI success in creating event 0: MEM_LOAD_UOPS_RETIRED.L1_MISS */
/* PAPI success in creating event 2: MEM_LOAD_UOPS_RETIRED.HIT_LFB */
/* PAPI success in creating event 1: MEM_LOAD_UOPS_RETIRED.L2_HIT */
/* PAPI success in creating event 3: MEM_LOAD_UOPS_RETIRED.L2_MISS */
/* PAPI success in creating event 2: MEM_LOAD_UOPS_RETIRED.L3_HIT */
/* PAPI success in creating event 3: MEM_LOAD_UOPS_RETIRED.L3_MISS */
/* PAPI success in creating event 1: MEM_UOPS_RETIRED.ALL_LOADS */

// ?  MEM_UOPS_RETIRED.ALL_LOADS = MEM_LOAD_UOPS_RETIRED.L1_HIT + MEM_LOAD_UOPS_RETIRED.HIT_LFB + MEM_LOAD_UOPS_RETIRED.L1_MISS
// ?  MEM_LOAD_UOPS_RETIRED.L1_MISS = MEM_LOAD_UOPS_RETIRED.L2_HIT + MEM_LOAD_UOPS_RETIRED.L2_MISS
// ?  MEM_LOAD_UOPS_RETIRED.L2_MISS = MEM_LOAD_UOPS_RETIRED.L3_HIT + MEM_LOAD_UOPS_RETIRED.L3_MISS


// L1
    /* case 0: */
    /*   strncpy(papi_event[0].name, "MEM_UOPS_RETIRED.ALL_LOADS", 100); */
    /*   break; */

    /* case 1: */
    /*   strncpy(papi_event[1].name, "MEM_LOAD_UOPS_RETIRED.L1_HIT", 100); */
    /*   break; */

    /* case 2: */
    /*   strncpy(papi_event[2].name, "MEM_LOAD_UOPS_RETIRED.HIT_LFB", 100); */
    /*   break; */

    /* case 3: */
    /*   strncpy(papi_event[3].name, "MEM_LOAD_UOPS_RETIRED.L1_MISS", 100); */
    /*   break; */

// L2
    /* case 0: */
    /*   strncpy(papi_event[0].name, "MEM_UOPS_RETIRED.ALL_LOADS", 100); */
    /*   break; */

    /* case 1: */
    /*   strncpy(papi_event[1].name, "MEM_LOAD_UOPS_RETIRED.L1_MISS", 100); */
    /*   break; */

    /* case 2: */
    /*   strncpy(papi_event[2].name, "MEM_LOAD_UOPS_RETIRED.L2_HIT", 100); */
    /*   break; */

    /* case 3: */
    /*   strncpy(papi_event[3].name, "MEM_LOAD_UOPS_RETIRED.L2_MISS", 100); */
    /*   break; */

// L3
    /* case 0: */
    /*   strncpy(papi_event[0].name, "MEM_UOPS_RETIRED.ALL_LOADS", 100); */
    /*   break; */

    /* case 1: */
    /*   strncpy(papi_event[1].name, "MEM_LOAD_UOPS_RETIRED.L2_MISS", 100); */
    /*   break; */

    /* case 2: */
    /*   strncpy(papi_event[2].name, "MEM_LOAD_UOPS_RETIRED.L3_HIT", 100); */
    /*   break; */

    /* case 3: */
    /*   strncpy(papi_event[3].name, "MEM_LOAD_UOPS_RETIRED.L3_MISS", 100); */
    /*   break; */


    case 0:
      strncpy(papi_event_mth[thread_id][0].name, "PAPI_TOT_CYC", 100);
      break;

    case 1:
      strncpy(papi_event_mth[thread_id][1].name, "PAPI_REF_CYC", 100);
      break;


//    case 2:
//      strncpy(papi_event_mth[thread_id][2].name, "CPU_CLK_THREAD_UNHALTED:THREAD_P", 100);
//      break;

//    case 3:
//      strncpy(papi_event_mth[thread_id][3].name, "CPU_CLK_THREAD_UNHALTED:REF_P", 100);
//      break;

//    case 4:
//      strncpy(papi_event_mth[thread_id][4].name, "CPU_CLK_UNHALTED", 100);
//      break;

//    case 5:
//      strncpy(papi_event_mth[thread_id][5].name, "CPU_CLK_THREAD_UNHALTED:REF_XCLK", 100);
//      break;

//    case 6:
//      strncpy(papi_event_mth[thread_id][6].name, "INST_RETIRED.ANY", 100);
//      break;

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

  double clock_ratio = (double)papi_event_mth[thread_id][0].sum_of_results/(double)papi_event_mth[thread_id][1].sum_of_results;

  return (clock_ratio);

}

