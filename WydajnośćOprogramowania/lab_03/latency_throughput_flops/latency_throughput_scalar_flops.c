#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include"uth_time.h"
 
const int num_iter = 100000000;

void main( void ){

  double a, b, c, d, e, f, g, h, r, s, t, u, w, v, x, y, z, sum;
  int i, j, k, l;
  double CPU_time, wallclock_time;


  // scalar operations

  a = 1.000001;
  b = 1.000002;
  c = 1.000003;
  d = 1.000004;
  e = 1.000005;
  f = 1.000006;
  g = 1.000007;
  h = 1.000008;
  r = 1.000009;
  s = 1.000010;
  t = 1.000011;
  u = 1.000012;
  w = 1.000013;
  v = 1.000014;
  x = 1.000015;
  y = 1.000016;
  z = 1.000017;

// warm up
//

// calculations with time measurments
//
  CPU_time = time_CPU();
  wallclock_time = time_clock();

  for(i=0;i<num_iter;i++){

    a = 1.00000001*a+0.000001; 
   // b = 1.00000001*b+0.000001; 
   //c = 1.00000001*c+0.000001; 
  // d = 1.00000001*d+0.000001; 
  // e = 1.00000001*e+0.000001; 
  // f = 1.00000001*f+0.000001; 
   // g = 1.00000001*g+0.000001; 
    //h = 1.00000001*h+0.000001; 
   // r = 1.00000001*r+0.000001; 
    //s = 1.00000001*s+0.000001; 
   // t = 1.00000001*t+0.000001; 
   // u = 1.00000001*u+0.000001; 
    //w = 1.00000001*w+0.000001; 
   // v = 1.00000001*v+0.000001; 
    //x = 1.00000001*x+0.000001; 
    //y = 1.00000001*y+0.000001; 
    //z = 1.00000001*z+0.000001; 

  }
  double nr_oper_local = 1 * 2.0 * num_iter;

  CPU_time = time_CPU() - CPU_time;
  wallclock_time = time_clock() - wallclock_time;

  sum = a+b+c+d+e+f+g+h+r+s+t+u+w+v+x+y+z;
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
