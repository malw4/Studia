#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include "uth_time.h"

//#define PAPI_TEST
#ifdef PAPI_TEST
#include "papi_driver.h"
#endif

const int num_iter = 10000000;

void main( voi ){

  double a, b, c, d, e, f, g, h, o, p, r, s, t, u, w, v, x, y, z, sum;
  int i, j, k, l, m, n;
  double CPU_time, wallclock_time;

#ifdef PAPI_TEST
   papi_driver_init();
   papi_driver_reset_events();
   papi_driver_start_events();
#endif

  CPU_time = time_CPU();
  wallclock_time = time_clock();

  a = 1.000001;
  for(i=0;i<num_iter/2;i++){
    a = 1.000001*a+0.000001; 
  }

  CPU_time = time_CPU() - CPU_time;
  wallclock_time = time_clock() - wallclock_time;


  printf("\n");
  printf("Result of arithmetic operations: %lf (x=%lf)\n", a, x);
  printf("Wynik operacji arytmetycznych: %lf\n", a);
  printf("\n");
  printf("Time for executing %d arithmetic operations:\n\t CPU - %lf, wallclock - %lf\n",
	 2*num_iter/2, CPU_time, wallclock_time);
  printf("Czas wykonania %d operacji arytmetycznych:\n\t CPU - %lf, zegar - %lf\n",
	 2*num_iter/2, CPU_time, wallclock_time);
  printf("Wydajność: %lf GFlops\n", 1.0e-9*num_iter/wallclock_time);
  printf("\n");

#ifdef PAPI_TEST
  papi_driver_stop_events();
  papi_driver_print_events();
#endif

  printf("\n");
  printf("Result of arithmetic operations: %lf\n", a);
  printf("Wynik operacji arytmetycznych: %lf\n", a);
  printf("\n");
  printf("Time for executing %d arithmetic operations (with conditional branches):\n\t CPU - %lf, wallclock - %lf\n",
	 (int)(num_iter), CPU_time, wallclock_time);
  printf("Czas wykonania %d operacji arytmetycznych (ze skokami warunkowymi):\n\t CPU - %lf, zegar - %lf\n",
	 (int)(num_iter), CPU_time, wallclock_time);
  printf("Wydajność: %lf GFlops\n", 1.0e-9*num_iter/wallclock_time);
  printf("\n");

}

