/******************************************************************************
uts_time.c - implementation of time measurement functions for Linux/Unix
uts_time.c - procedury pomiaru czasu dla systemów Linux/Unix

// ONLY time_CPU and time_clock are thread safe !!!

Time measurements:
  time_C - (C standard procedure) to return time in seconds from some date
           warning: may not be implemented in stdlib
  time_init   - to initiate time measurments
  time_clock  - to return wall clock time from initialization
  time_CPU    - to return CPU time from initialization
  time_print  - to print CPU and wall clock time from initialization

Procedury wykorzystujace funkcje standardowe C:
  time_C - zwraca czas CPU w sekundach od rozpoczecia dzialania lub -1 jesli
           funkcja clock() nie jest prawidlowo zaimplementowana w systemie 

Procedury UNIX-owe:
  time_init   - inicjacja pomiaru czasu
  time_print  - pomiar i wydruk czasu CPU i zegarowego od momentu zainicjowania

  time_CPU    - zwrocenie czasu CPU od momentu zainicjowania
  time_clock  - zwrocenie czasu zegarowego od momentu zainicjowania

Sposob uzycia:
  zgodnie z interfejsem w pliku pomiar_czasu.h

------------------------------  			
History:
      02.2002 - Krzysztof Banas, pobanas@cyf-kr.edu.pl - initial version
******************************************************************************/

#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<sys/time.h>
#include<sys/resource.h>

#ifdef _OPENMP
#include<omp.h>
#endif

#include "uth_time.h" // IMPLEMENTED

// variables for time measurements - see getrusage and gettimeofday in man 3 
// static variables - the values are retained between subsequent calls
/* zmienne statyczne do wielokrotnego wykorzystania procedur pomiaru */
static clock_t ct;
static struct rusage rp;
static struct timeval tp;
static struct timezone tzp;
//static struct timespec ts; // POSIX 2008

/*---------------------------------------------------------
  time_C - (C standard procedure) to return time in seconds from some date
  time_C - zwraca czas CPU w sekundach od rozpoczecia dzialania lub -1 jesli
           funkcja clock() nie jest prawidlowo zaimplementowana w systemie 
---------------------------------------------------------*/
double time_C()
{        
  clock_t time;

  time = clock();

  if(time==-1) return( (double) time);
  else return ( (double) time / (double) CLOCKS_PER_SEC );
}

/*---------------------------------------------------------
  time_init - to initiate time measurements (initializes tp, tzp and rp)
  time_init - inicjuje pomiar czasu nadajac wartosci 
               poczatkowe strukturom tp, tzp i rp
---------------------------------------------------------*/
void time_init()
{
  ct = clock();
  getrusage(RUSAGE_SELF, &rp);
  gettimeofday(&tp,&tzp);
}


/*---------------------------------------------------------
  time_clock - to return wall clock time from initialization
  time_clock - procedura zwraca czas zegarowy w sekundach od momentu
                zainicjowania (jako liczbe podwojnej precyzji) 
---------------------------------------------------------*/
double time_clock()
{ 


  //struct timeval tk;
  //struct timezone tzp;
  struct timespec tsl; // POSIX 2008
  
  //gettimeofday(&tk, &tzp);
  clock_gettime(CLOCK_REALTIME, &tsl); // POSIX 2008

  //daytime=(tk.tv_usec)/1e6+tk.tv_sec;
  double daytime=(tsl.tv_nsec)/1e9+tsl.tv_sec; // POSIX 2008

  return(daytime);

  // alternative using OpenMP function 
  // return(omp_get_wtime());

}

/*---------------------------------------------------------
  time_CPU - to return CPU time from initialization
  time_CPU - procedura zwraca czas CPU w sekundach od momentu
             zainicjowania (jako liczbe podwojnej precyzji) 
 ---------------------------------------------------------*/
double time_CPU()
{ 
  
  struct rusage rk;
  double cputime;
  
  getrusage(RUSAGE_SELF, &rk);
  
  cputime = (rk.ru_utime.tv_usec)/1e6;
  cputime += rk.ru_utime.tv_sec;
  
  return(cputime);
}
 
/*---------------------------------------------------------
  time_print - to print CPU and wall clock time from initialization
  time_print - pomiar i wydruk czasu CPU i zegarowego 
               w sekundach od momentu zainicjowania pomiaru czasu
 ---------------------------------------------------------*/
void time_print()
{ 
  
  clock_t time;
  struct rusage rk;
  struct timeval tk;
  double stdtime, cputime,daytime;
  
  time = clock();
  getrusage(RUSAGE_SELF, &rk);
  gettimeofday(&tk, &tzp);
  
  stdtime = (double) (time - ct) / (double)  CLOCKS_PER_SEC ;

  cputime = ( rk.ru_utime.tv_usec - rp.ru_utime.tv_usec ) / 1.0e6 ;
  cputime += rk.ru_utime.tv_sec - rp.ru_utime.tv_sec;
  
  daytime = ( tk.tv_usec - tp.tv_usec ) / 1.0e6 + tk.tv_sec - tp.tv_sec ;
  
  printf("time C library   = %lf\n",stdtime);
  printf("time CPU         = %lf\n",cputime);
  printf("time wallclock   = %lf\n",daytime);
  
}
