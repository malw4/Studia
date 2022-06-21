#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include"uth_time.h"
 
const int num_iter = 100000000;

void main( void ){

  int i, j, k, l;
  double CPU_time, wallclock_time;

  // attempt to use vector operations
#define LOCAL_SIZE 52 

  double a_tab[LOCAL_SIZE], b_tab[LOCAL_SIZE], c_tab[LOCAL_SIZE], d_tab[LOCAL_SIZE];

  int tab_l = LOCAL_SIZE;
  for(i=0; i<tab_l; i++){
    a_tab[i] = 1.000001+0.0000001*i;
    b_tab[i] = 1.000002+0.0000001*i;
    c_tab[i] = 1.000003+0.0000001*i;
    d_tab[i] = 1.000004+0.0000001*i;
    //_tab[i] = 1.000005+0.0000001*i;
  }

  // warm up
  //
  
  // computations with time measurments
  //
  CPU_time = time_CPU();
  wallclock_time = time_clock();

  for(i=0;i<num_iter;i++){
    
    for(k=0; k<tab_l; k++){

      a_tab[k] = 1.00000001*a_tab[k]+0.000001; 
      //}
      //for(k=0; k<tab_l; k++){
      //b_tab[k] = 1.00000001*b_tab[k]+0.000001; 
      //}
      //for(k=0; k<tab_l; k++){
      //c_tab[k] = 1.00000001*c_tab[k]+0.000001; 
      //}
      //for(k=0; k<tab_l; k++){
      //d_tab[k] = 1.00000001*d_tab[k]+0.000001; 

    }
    
  }

  double nr_oper_local = 1 * tab_l * 2.0 * num_iter;

  CPU_time = time_CPU() - CPU_time;
  wallclock_time = time_clock() - wallclock_time;

  double sum = 0.0;
  for(k=0; k<tab_l; k++){
    sum += a_tab[k] + b_tab[k] + c_tab[k] + d_tab[k];
  }

  printf("\n\n");
  printf("Result of arithmetic operations: %lf\n", sum);
  printf("Wynik operacji arytmetycznych: %lf\n", sum);
  printf("\n");
  printf("Time for executing %lf arithmetic operations:\n\t CPU - %lf, wallclock - %lf\n",
	 nr_oper_local, CPU_time, wallclock_time);
  printf("Czas wykonania %lf operacji arytmetycznych:\n\t CPU - %lf, zegar - %lf\n",
	 nr_oper_local, CPU_time, wallclock_time);
  printf("Wydajność: %lf GFlops\n", nr_oper_local*1.0e-9/wallclock_time);
  printf("\n\n");



}
