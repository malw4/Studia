#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#include"uth_time.h"
 
const int num_iter = 1000000;

void main( void ){

  double a, b, c, sum,*tab;
  int i, j, k, l;
  double CPU_time, wallclock_time;
  tab=(double*)malloc(num_iter * sizeof(double));

  time_init();

  k = -500000;
 /* for(i=0;i<num_iter;i++){

    printf("%d ",k+i);

  }
  printf("\n\n\n");

  printf("Time for executing %d input/output operations: \n",num_iter);
  printf("Czas wykonania %d operacji wejscia/wyjscia: \n",num_iter);

  time_print();


  CPU_time = time_CPU();
  wallclock_time = time_clock();
  a = 1.000001;
  for(i=0;i<num_iter/2;i++){

    a = 1.000001*a+0.000001; 

  }
  CPU_time = time_CPU() - CPU_time;
  wallclock_time = time_clock() - wallclock_time;

  printf("\n\n");
  printf("Result of arithmetic operations: %lf\n", a);
  printf("Wynik operacji arytmetycznych: %lf\n", a);
  printf("\n");
  printf("Time for executing %d arithmetic operations:\n\t CPU - %lf, wallclock - %lf\n",
	 num_iter, CPU_time, wallclock_time);
  printf("Czas wykonania %d operacji arytmetycznych:\n\t CPU - %lf, zegar - %lf\n",
	 num_iter, CPU_time, wallclock_time);
  printf("\n\n");
*/
time_init();
  srand(time(NULL));
sum = 0.0;
for(i=0;i<num_iter/2;i++){

   sum+= rand(); 

  }
 printf("Czas generowania liczb losowych: \n");

time_print();

  //printf("Enter two floating point numbers;\n");
  //printf("Podaj dwie liczby rzeczywiste:\n");
  //scanf("%lf %lf", &a, &b);
  a = 2.72; b = 3.14;
  printf("Generating %d random floating point numbers from the interval: %lf - %lf\n", 
	 num_iter, a, b);
  printf("Generowanie %d losowych liczb rzeczywistych z zakresu : %lf - %lf\n", 
	 num_iter, a, b);
  sum = 0.0;

  //time_init();
  CPU_time = time_CPU();
  wallclock_time = time_clock();

  for(i=0;i<num_iter;i++){

    c = a + (b-a)*(((double)rand())/(RAND_MAX));
    sum += c;
    // printf("%lf ",c);

#ifdef DEBUG
    if(c<a || c>b) {
      printf("Error: number %lf out of range. Exiting.\n", c); 
      printf("Blad generacji: %lf poza zakresem.\n", c); 
      exit(0);
    }

    if(c==a || c==b) printf("Trial %d - number %lf at one of interval ends\n", i, c);
    if(c==a || c==b) printf("Próba %d - liczba %lf na granicy przedziału\n", i, c);
#endif

  }

  CPU_time = time_CPU() - CPU_time;
  wallclock_time = time_clock() - wallclock_time;
  printf("\n");
  printf("Average of %d generated numbers: %lf [(a+b)/2 = %lf]\n", 
	 num_iter, sum/num_iter, (a+b)/2.0);
  printf("Wartość średnia %d wygenerowanych liczb: %lf [(a+b)/2 = %lf]\n", 
	 num_iter, sum/num_iter, (a+b)/2.0);
  printf("\n");
  printf("Time for generating %d floating point numbers:\n\t CPU - %lf, wallclock - %lf\n",
	 num_iter, CPU_time, wallclock_time);
  printf("Czas generowania %d losowych liczb rzeczywistych:\n\t CPU - %lf, wallclock - %lf\n",
	 num_iter, CPU_time, wallclock_time);
  //time_print();
  printf("\n\n");
printf("Generowanie %d losowych liczb rzeczywistych z zakresu : %lf - %lf do tablicy\n", 
	 num_iter, a, b);
CPU_time = time_CPU();
  wallclock_time = time_clock();


for(i=0;i<num_iter;i++){
tab[i] = a + (b-a)*(((double)rand())/(RAND_MAX));

}
CPU_time = time_CPU() - CPU_time;
  wallclock_time = time_clock() - wallclock_time;
  printf("\n");
printf("Czas generowania %d losowych liczb rzeczywistych do tablicy:\n\t CPU - %lf, wallclock - %lf\n",
	 num_iter, CPU_time, wallclock_time);
printf("Odczytywanie %d losowych liczb rzeczywistych  z tablicy do zakresu : %lf - %lf\n", 
	 num_iter, a, b);
CPU_time = time_CPU();
  wallclock_time = time_clock();

for(i=0;i<num_iter;i++){
#ifdef DEBUG
    if(tab[i]<a || tab[i]>b) {
      printf("Error: number %lf out of range. Exiting.\n", tab[i]); 
      printf("Blad generacji: %lf poza zakresem.\n", tab[i]); 
      exit(0);
    }

    if(tab[i]==a || tab[i]==b) printf("Trial %d - number %lf at one of interval ends\n", i, tab[i]);
    if(tab[i]==a ||tab[i]==b) printf("Próba %d - liczba %lf na granicy przedziału\n", i, tab[i]);
#endif
}
CPU_time = time_CPU() - CPU_time;
  wallclock_time = time_clock() - wallclock_time;
  printf("\n");
printf("Czas odczytu liczb z tablicy:\n\t CPU - %lf, wallclock - %lf\n",
	 num_iter, CPU_time, wallclock_time);

  //time_print();
  printf("\n\n");

}
