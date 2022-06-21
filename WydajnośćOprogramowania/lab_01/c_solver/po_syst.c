/*************************************************************
File contains SYSTEM DEPENDENT procedures:
  czas, uczas - to initialize nad print results of time measurements
  getdaytime, getcputime - to return day and cpu time after last measurement

*************************************************************/

#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

struct rusage rp,rk;
struct timeval tp,tk;
struct timezone tzp;

void czas()
{
   getrusage(RUSAGE_SELF, &rp);
   gettimeofday(&tp,&tzp);
}

double getdaytime()
{ 

  double daytime;

  gettimeofday(&tk, &tzp);

  daytime=(tk.tv_usec-tp.tv_usec)/1e6+tk.tv_sec-tp.tv_sec;

return(daytime);
}

double getcputime()
{ 

  double cputime;

  getrusage(RUSAGE_SELF, &rk);
  gettimeofday(&tk, &tzp);

  cputime = (rk.ru_utime.tv_usec-rp.ru_utime.tv_usec)/1e6;
  cputime += rk.ru_utime.tv_sec-rp.ru_utime.tv_sec;

return(cputime);
}

void uczas()
{ 

  double cputime,daytime;

  getrusage(RUSAGE_SELF, &rk);
  gettimeofday(&tk, &tzp);

  cputime = (rk.ru_utime.tv_usec-rp.ru_utime.tv_usec)/1e6;
  cputime += rk.ru_utime.tv_sec-rp.ru_utime.tv_sec;

  daytime=(tk.tv_usec-tp.tv_usec)/1e6+tk.tv_sec-tp.tv_sec;

  printf("cputime=%lf\n",cputime);
  printf("daytime=%lf\n",daytime);

}

