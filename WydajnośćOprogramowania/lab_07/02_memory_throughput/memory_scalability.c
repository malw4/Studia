#include <stdlib.h>
#include <stdio.h>
#include <emmintrin.h>

#include <sys/times.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include<sys/time.h>
#include<sys/resource.h>
static struct rusage rp;

static struct timeval tp;
static struct timezone tzp;

#define SCALAR double // float and int require changes in the code

#define min(X,Y) ((X) < (Y) ?  (X) : (Y))

void init_counters(); // initialize time counters

double get_wallclock_seconds(); // using gettimeofday

double get_CPU_seconds(); // using getrusage

long get_page_faults() ; // using getrusage

double lg(double x); // log base 2

#define OMP_OK
#ifdef OMP_OK
#include <omp.h>
#else
int omp_get_num_threads(void){return 1;}
int omp_get_thread_num(void){return 0;}
#endif

SCALAR funkcja(SCALAR * a, SCALAR* b, SCALAR* c, SCALAR* d, SCALAR* e, int n);
double rmstime = 0.0;

#define MULT_MEM_MAX 160 // should be a multiple of any considered number of threads
#define MULT 1

int main(int argc, char* argv[])
{
  
  double time_global=0.0;
   
    int i, j, k;

    // for finding the best parameters for a given architecture    
//#define NR_ARRAY_SIZES 15
    //int size_array[NR_ARRAY_SIZES] = {      100,  200,  400,  800, 1600, 3200, 6400, 12800, 25600, 51200, 102400, 204800, 409600, 819200, 1638400 };
    //int repeat_array[NR_ARRAY_SIZES] = {  16384, 8192, 4096, 2048, 1024,  512,  256,   128,    64,    32,     16,      8,      4,      2,       1 }; 
    //int mult_comp_array[NR_ARRAY_SIZES] = {  10,   10,   10,   10,   10,   10,   10,    10,    10,     5,      1,      1,      1,      1,       1 };
    
    //#define NR_ARRAY_SIZES 4 // should contain 4 selected sizes for L1, L2, L3 and DRAM in a given system with proper number of repetitions
    //int size_array[NR_ARRAY_SIZES] = {     };
    //int repeat_array[NR_ARRAY_SIZES] = {   }; 
    //int mult_comp_array[NR_ARRAY_SIZES] = {  };
    
// for ESTERA
#define NR_ARRAY_SIZES 4 // should contain 4 selected sizes for a given system with proper number of repetitions
    //int size_array[NR_ARRAY_SIZES] = { 400, 3200, 25600, 409600 };
    //int repeat_array[NR_ARRAY_SIZES] = { 4096, 512, 64, 4  }; 
    //int mult_comp_array[NR_ARRAY_SIZES] = { 10, 10, 10, 1  };
    
// DRAM
//    int size_array[NR_ARRAY_SIZES] = { 409600, 409600, 409600, 409600 };
//    int repeat_array[NR_ARRAY_SIZES] = { 4, 4, 4, 4  };
//    int mult_comp_array[NR_ARRAY_SIZES] = { 1, 1, 1, 1  };

// L1
//    int size_array[NR_ARRAY_SIZES] = { 400, 400, 400, 400 };
//    int repeat_array[NR_ARRAY_SIZES] = { 4096, 4096, 4096, 4096  };
//    int mult_comp_array[NR_ARRAY_SIZES] = { 10, 10, 10, 10  };

// L2
//    int size_array[NR_ARRAY_SIZES] = { 3200, 3200, 3200, 3200 };
//    int repeat_array[NR_ARRAY_SIZES] = { 512, 512, 512, 512  };
//    int mult_comp_array[NR_ARRAY_SIZES] = { 10, 10, 10, 10  };

// L3
    int size_array[NR_ARRAY_SIZES] = { 25600, 25600, 25600, 25600 };
    int repeat_array[NR_ARRAY_SIZES] = { 64, 64, 64, 64  };
    int mult_comp_array[NR_ARRAY_SIZES] = { 10, 10, 10, 10  };



#define ALIGNMENT  64   
    
    long int array_size = MULT_MEM_MAX*size_array[NR_ARRAY_SIZES-1]; 
    size_t size_in_bytes = array_size*sizeof(SCALAR);
    SCALAR* array_a;
    SCALAR* array_b;
    SCALAR* array_c;
    SCALAR* array_d;
    SCALAR* array_e;
    size_t alignment =  ALIGNMENT; 
    
    // POSIX function - portable, but may inhibit icc vectorization
    //  posix_memalign( (void **)&array_a, alignment, size_in_bytes);
    //  posix_memalign( (void **)&array_b, alignment, size_in_bytes);
    //  posix_memalign( (void **)&array_c, alignment, size_in_bytes);
    //  posix_memalign( (void **)&array_d, alignment, size_in_bytes);
    //  posix_memalign( (void **)&array_e, alignment, size_in_bytes);
    
    // icc extensions
    array_a = (double *)_mm_malloc(size_in_bytes, ALIGNMENT);
    array_b = (double *)_mm_malloc(size_in_bytes, ALIGNMENT);
    array_c = (double *)_mm_malloc(size_in_bytes, ALIGNMENT);
    array_d = (double *)_mm_malloc(size_in_bytes, ALIGNMENT);
    array_e = (double *)_mm_malloc(size_in_bytes, ALIGNMENT);
    
    
    int i_size; 
    for(i_size=0; i_size<NR_ARRAY_SIZES; i_size++){     
      
      int working_set_size = size_array[i_size];;
      int NTIMES = MULT*mult_comp_array[i_size]*repeat_array[i_size];

#pragma omp master
      {
	time_global = 0.0;
      }

      //  parallel processing of 5 shared arrays
#pragma omp parallel default(none) shared(i_size, time_global,  working_set_size, NTIMES, array_a, array_b, array_c, array_d, array_e, rmstime  )
      {
	

	int fragments_per_thread = MULT_MEM_MAX/omp_get_num_threads();
	
	int i;
	for(i=0; i<fragments_per_thread;i++){
	    
	  int jk = (fragments_per_thread*omp_get_thread_num()+i)*working_set_size;
	    
          int j; 
          for (j=0; j<working_set_size; j++){
	    int ii = jk+j;
	    //for(ii=0; ii<array_size; ii++)  {
	    array_a[ii] = sqrt((SCALAR)(ii+1));
	    array_b[ii] = sqrt((SCALAR)(ii+1));
	    array_c[ii] = sqrt((SCALAR)(ii+1));
	    array_d[ii] = sqrt((SCALAR)(ii+1));
	    array_e[ii] = sqrt((SCALAR)(ii+1));
	  }
	}

#pragma omp barrier
	
	double time_external;
	#pragma omp master
	{
	  time_external = get_wallclock_seconds();
	//time_external = omp_get_wtime();
	}
	
	double time_local = get_wallclock_seconds();
	//time_local = omp_get_wtime();
	
	for(i=0; i<fragments_per_thread;i++){
	    
	  int jk = (fragments_per_thread*omp_get_thread_num()+i)*working_set_size;
	    
	  //printf("thread %d, index %d\n", omp_get_thread_num(), jk);
	  int kk;
	  for (kk=0; kk<NTIMES; kk++) {
	        
	    int j; int ijk;
	    for (j=0; j<working_set_size; j++){
	      ijk = jk+j;
	      //a[j] = b[j]+d[j]*c[j];
#define NR_ARRAYS 5L // 5 arrays for full utilization of registers
	      array_a[ijk] = array_e[ijk]*array_b[ijk]+array_d[ijk]*array_c[ijk];
	      // 4 arrays
	      //array_a[ijk] = array_b[ijk]+array_d[ijk]*array_c[ijk];
	            
	    }
	          
	    // to prevent optimizing out benchmark loops
	    ijk=fragments_per_thread/2;
	    rmstime = array_e[ijk]*array_d[ijk]+array_c[ijk]*array_a[ijk];
	    if (rmstime<-1.0e-4) rmstime+=funkcja(array_a,array_b,array_c,array_d,array_e,fragments_per_thread);
	    //printf("kk %d\n",kk);
	  }
        }
	      
	time_local = get_wallclock_seconds() - time_local;
	//time_local = omp_get_wtime() - time_local;
	      
#pragma omp atomic
	time_global += time_local;
	//printf("local %lf, global %lf\n", time_local, time_global);

#pragma omp barrier

#pragma omp master
	{
          time_external = get_wallclock_seconds() - time_external;
	}

#pragma omp master
	{   
	  long int nr_access = NR_ARRAYS * NTIMES * working_set_size * MULT_MEM_MAX ; 
	        
	  time_global = time_global / omp_get_num_threads();
	  //time_external = get_wallclock_seconds() - time_external;
	  //printf("external %lf, global %lf\n", time_external, time_global);
	  
	  printf("\nMemory scalability benchmark for chunk size %d (+parallel overhead calculations)\n", working_set_size);
	  printf("total for %d arrays %d (%7.3lf[MB]), total array size %d (%7.3lf[MB])\n",
		 NR_ARRAYS, NR_ARRAYS*working_set_size, 
		 NR_ARRAYS*working_set_size*sizeof(SCALAR)/1024.0/1024.0,
		 MULT_MEM_MAX*working_set_size,
		 MULT_MEM_MAX*working_set_size*sizeof(SCALAR)/1024.0/1024.0);
	  //if(i_size==0) {
	  printf(" nr_accesses,  throughput[GB/s],  access_time[ns],  execution time[s] (+)\n");
	  //}    
	  printf("%12ld  %10.2lf  %16.3lf   %12.3lf (= %5.3lf + overhead: %5.2lf%% )\n",
		 nr_access,
		 1.0E-09 * sizeof(SCALAR) * nr_access /(time_external),  
		 1.e9*time_external/(nr_access),
		 time_external, time_global, 100*(time_external-time_global)/time_global );
	    
	    
	  rmstime += funkcja(array_a,array_b,array_c,array_d,array_e,working_set_size);
	}    
      }
    }
      
  
  printf("\n Checksum: %lf\n",rmstime);
  return 0;
}



SCALAR funkcja(SCALAR * a, SCALAR* b, SCALAR* c, SCALAR* d, SCALAR* e, int n){
  
  int i;
  for(i=0;i<n;i++) {
    a[i] = b[i]*c[i]-e[i]*d[i];
    if(a[i]>b[i]) c[i]+=e[i]*d[i];
  }
  return(a[0]+a[n]+c[n/2]);
  
}



void init_counters(){
  getrusage(RUSAGE_SELF, &rp);
  gettimeofday(&tp,&tzp);
}

double get_wallclock_seconds() { /* to read time */
  struct tms rusage;
  
  struct timeval tk;
  struct timezone tzp;
  double daytime;
  
  gettimeofday(&tk, &tzp);
  
  daytime=(tk.tv_usec-tp.tv_usec)/1e6+tk.tv_sec-tp.tv_sec;
  
  return (daytime);
}

double get_CPU_seconds() { /* to read time */
  
  struct rusage rk;
  double cputime;
  
  getrusage(RUSAGE_SELF, &rk);
  
  cputime = (rk.ru_utime.tv_usec-rp.ru_utime.tv_usec)/1e6;
  cputime += rk.ru_utime.tv_sec-rp.ru_utime.tv_sec;
  
  return (cputime);
}

long get_page_faults() { /* to read time */
  
  struct rusage rk;
  long page_faults;
  
  getrusage(RUSAGE_SELF, &rk);
  
  page_faults = rk.ru_majflt - rp.ru_majflt;
  
  return (page_faults);
}


double lg(double x) { /* log base 2 */
  return (log(x)/log(2.0));
}

