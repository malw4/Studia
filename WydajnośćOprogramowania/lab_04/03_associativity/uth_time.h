#ifndef _uth_time_
#define _uth_time_
/******************************************************************************
File uth_time.h - interface with time measurement functions

Time measurements:
  time_C - (C standard procedure) to return time in seconds from some date
           warning: may not be implemented in stdlib
  time_init   - to initiate time measurements
  time_clock  - to return wall clock time from initialization
  time_CPU    - to return CPU time from initialization
  time_print  - to print CPU and wall clock time from initialization
******************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

/**--------------------------------------------------------
  time_init   - to initiate time measurements
---------------------------------------------------------*/
extern void time_init();

/**--------------------------------------------------------
  time_C - (C standard procedure) to return time in seconds from some date
---------------------------------------------------------*/
extern double time_C();

/**--------------------------------------------------------
  time_clock  - to return wall clock time from initialization
---------------------------------------------------------*/
extern double time_clock();

/**--------------------------------------------------------
  time_CPU    - to return CPU time from initialization
---------------------------------------------------------*/
extern double time_CPU();

/**--------------------------------------------------------
  time_print  - to print CPU and wall clock time from initialization
---------------------------------------------------------*/
extern void time_print();


#ifdef __cplusplus
}
#endif

#endif
