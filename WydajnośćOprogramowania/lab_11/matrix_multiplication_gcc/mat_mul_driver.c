#include<stdlib.h>
#include<stdio.h>
#include <math.h>
#include <omp.h>

#include <immintrin.h>
#include <emmintrin.h>

// definitions of: SCALAR, BLOCK_SIZE_S, BLOCK_SIZE_L and ALIGNMENT
#include "sizes.h"

#ifdef PAPI_TEST
#include "papi.h"
#include "papi_driver_mth.h"
#endif

void mat_mul_par_papi(SCALAR *a, SCALAR *b, SCALAR* c, int n);

int main()
{  
  int i,j,k,n;
  
  const SCALAR done=1.0;
  double nr_oper;
  double GFlops=0.0;
  double frequency=1.0;
  double nominal_frequency=NOMINAL_FREQUENCY;
  double clock_ratio=1.0;
  
#ifdef PAPI_TEST
  papi_driver_mth_init();
#endif
  
  // Matrices are stored in row-major order: 
  // // A(row, col) = A[row * N + col]
  
#define DEFAULT_SIZE 1080
  //#define DEFAULT_SIZE 1080 - dla wersji 4x12x4
  //#define DEFAULT_SIZE 2016 - dla wersji 4x12x4
  //#define DEFAULT_SIZE 1872 - dla wersji 4x12x4
  //#define DEFAULT_SIZE 10800 - each array ~1GB
  
  const int WYMIAR = (DEFAULT_SIZE/BLOCK_SIZE_L)*BLOCK_SIZE_L;
  printf("Default matrix size %d - adjusted for block size %d to %d\n",
         DEFAULT_SIZE, BLOCK_SIZE_L, WYMIAR);
  const int ROZMIAR = WYMIAR*WYMIAR;
  
  // create matrices
  n=WYMIAR;
  size_t alignment = ALIGNMENT;
  
  SCALAR *A, *B, *C, *D;
  posix_memalign( (void **)&A, alignment, ROZMIAR*sizeof(SCALAR));
  posix_memalign( (void **)&B, alignment, ROZMIAR*sizeof(SCALAR));
  posix_memalign( (void **)&C, alignment, ROZMIAR*sizeof(SCALAR));
  
  // should be done in the same way as eccesses during matrix-matrix multiplication
  // for proper NUMA allocation
  for(i=0;i<ROZMIAR;i++) A[i]=1.0*i/1000000.0;
  for(i=0;i<ROZMIAR;i++) B[i]=1.0*(ROZMIAR-i)/1000000.0;
  for(i=0;i<ROZMIAR;i++) C[i]=0.0;
  
#ifdef PAPI_TEST 
  posix_memalign( (void **)&D, alignment, ROZMIAR*sizeof(SCALAR));
  for(i=0;i<ROZMIAR;i++) D[i]=0.0;
#endif
  
  nr_oper= n*(n*(n*2.0));
  
#ifdef PAPI_TEST 
  printf("mat_mul_par_papi: nr_oper %lf, %lf\n", nr_oper, C[0]);
#else
  printf("mat_mul_par: nr_oper %lf, %lf\n", nr_oper, C[0]);
#endif
  
  double t1 = omp_get_wtime();
  
  mat_mul_par_papi(A, B, C, n);
  
  double t2 = omp_get_wtime(); 
  
#ifdef PAPI_TEST
  int thread_id = 0;
  clock_ratio = papi_return_clock_ratio_mth(thread_id);
  frequency = nominal_frequency*clock_ratio;
  printf("frequency: nominal %lf, ratio %lf -> real %lf\n",
	 nominal_frequency, clock_ratio, frequency);
#endif
  
  GFlops = nr_oper/(t2-t1)/1024/1024/1024;
  printf("Execution time - %lf, \tGFLOPS = %lf \t( flop/cycle = %lf  - %lf GHz )\n\n",
	 t2-t1, GFlops, GFlops/frequency, frequency);
  
  
#ifdef PAPI_TEST
  int ii,jj,kk;
  
  const int BLS = BLOCK_SIZE_S; 
  //#pragma omp parallel for default(none) shared(A,B,D,n) private(i,j,k) private(ii,jj,kk)
  for(i=0;i<n;i++){
    for(k=0;k<n;k++){
      for(j=0;j<n;j++){
	D[i*n+j] += A[i*n+k]*B[k*n+j];
      }
    }
  }
  
  //mat_mul_par(A, B, D, n); 
  /* //check results */
  for(i=0;i<n*n;i++){ 
    if(fabs(C[i]-D[i])/fabs(C[i])>1.e-9) { 
      printf("error: %lf%% (C[%d] = %lf, D[%d] = %lf)\n",  
  	     fabs(C[i]-D[i])/fabs(C[i]), 
  	     i, C[i], i, D[i] ); 
      //getchar();getchar(); 
    } 
  } 
#endif
  
  free(A);
  free(B);
  free(C);
#ifdef PAPI_TEST 
  free(D);
#endif
  
  return(0);
}














