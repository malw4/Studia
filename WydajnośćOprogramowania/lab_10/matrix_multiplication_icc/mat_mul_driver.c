#include<stdlib.h>
#include<stdio.h>
#include <math.h>

#ifdef _OPENMP
#include <omp.h>
#else
#error "This compiler does not understand OPENMP"
#endif

#include <immintrin.h>
#include <emmintrin.h>

#include "sizes.h"

//#define PAPI_TEST
#ifdef PAPI_TEST
#include "papi.h"
#include "papi_driver_mth.h"
#endif

// Matrices are stored in row-major order: 
// A(row, col) = A[row * N + col]
#define MULT (ALIGNMENT/4)
#define WYMIAR (MULT*BLOCK_SIZE_L) // assumed to be a multiple of large block size
#define ROZMIAR (WYMIAR*WYMIAR)

void mat_mul_par(SCALAR *a, SCALAR *b, SCALAR* c, int n);
void mat_mul_avx_2(SCALAR *a, SCALAR *b, SCALAR* c, int n);
void mat_mul_avx_1(SCALAR *a, SCALAR *b, SCALAR* c, int n);

int main()
{

  int i,j,n;

  const SCALAR done=1.0;
  double nr_oper;
  double t1,t2;

#ifdef PAPI_TEST
  papi_driver_mth_init();
#endif

  // create matrices
  n=WYMIAR;
  size_t alignment = ALIGNMENT;
  SCALAR* A = (SCALAR *) _mm_malloc(ROZMIAR*sizeof(SCALAR), alignment);
  SCALAR* B = (SCALAR *) _mm_malloc(ROZMIAR*sizeof(SCALAR), alignment);
  SCALAR* C = (SCALAR *) _mm_malloc(ROZMIAR*sizeof(SCALAR), alignment);
  SCALAR* D = (SCALAR *) _mm_malloc(ROZMIAR*sizeof(SCALAR), alignment);

  //SCALAR *A, *B, *C, *D;
  //posix_memalign( (void **)&A, alignment, ROZMIAR*sizeof(SCALAR));
  //posix_memalign( (void **)&B, alignment, ROZMIAR*sizeof(SCALAR));
  //posix_memalign( (void **)&C, alignment, ROZMIAR*sizeof(SCALAR));
  //posix_memalign( (void **)&D, alignment, ROZMIAR*sizeof(SCALAR));

  // should be done in the same way as eccesses during matrix-matrix multiplication
  // for proper NUMA allocation
  for(i=0;i<ROZMIAR;i++) A[i]=1.0*i/1000000.0;
  for(i=0;i<ROZMIAR;i++) B[i]=1.0*(ROZMIAR-i)/1000000.0;
  for(i=0;i<ROZMIAR;i++) C[i]=0;
  for(i=0;i<ROZMIAR;i++) D[i]=0.0;

  nr_oper= n*(n*(n*2.0));

  // warm up - may be commented out
  mat_mul_par(A, B, C, n);
  printf("mat_mul_par: nr_oper %lf, %lf\n", nr_oper, C[0]);

  for(i=0;i<ROZMIAR;i++) C[i]=0.0;
  t1 = omp_get_wtime();
  mat_mul_par(A, B, C, n);
  t2 = omp_get_wtime(); 

  printf("Execution time - %lf, \tGFLOPS = %lf\n\n",
	 t2-t1, nr_oper/(t2-t1)/1024/1024/1024);

  for(i=0;i<ROZMIAR;i++) D[i]=0.0;
  // warm up - may be commented out
  mat_mul_avx_1(A, B, D, n);
  printf("mat_mul_avx 4x4x4: nr_oper %lf, %lf\n", nr_oper, D[0]);

  for(i=0;i<ROZMIAR;i++) D[i]=0.0;
  t1 = omp_get_wtime();
  mat_mul_avx_1(A, B, D, n);
  t2 = omp_get_wtime(); 

  printf("Execution time - %lf, \tGFLOPS = %lf\n\n",
	 t2-t1, nr_oper/(t2-t1)/1024/1024/1024);

 //check results
  for(i=0;i<n*n;i++){
    if(fabs(C[i]-D[i])/fabs(C[i])>1.e-9) {
      printf("error: %lf%% (C[%d] = %lf, D[%d] = %lf)\n", 
	     fabs(C[i]-D[i])/fabs(C[i]),
	     i, C[i], i, D[i] );
      //getchar();getchar();
    }
  }
  
  for(i=0;i<ROZMIAR;i++) D[i]=0.0;
  // warm up - may be commented out
  mat_mul_avx_2(A, B, D, n);
  printf("mat_mul_avx 4x12x4: nr_oper %lf, %lf\n", nr_oper, D[0]);

  for(i=0;i<ROZMIAR;i++) D[i]=0.0;
  t1 = omp_get_wtime();
  mat_mul_avx_2(A, B, D, n);
  t2 = omp_get_wtime(); 

  printf("Execution time - %lf, \tGFLOPS = %lf\n\n",
	 t2-t1, nr_oper/(t2-t1)/1024/1024/1024);

 //check results
  for(i=0;i<n*n;i++){
    if(fabs(C[i]-D[i])/fabs(C[i])>1.e-9) {
      printf("error: %lf%% (C[%d] = %lf, D[%d] = %lf)\n", 
	     fabs(C[i]-D[i])/fabs(C[i]),
	     i, C[i], i, D[i] );
      //getchar();getchar();
    }
  }
  
  //test
  //printf("LAPACK\n");
  for(i=0;i<ROZMIAR;i++) D[i]=0.0;
  // warm up - may be commented out
  //sgemm_("T", "T", &n, &n, &n, &done, A, &n, B, &n, &done, D, &n);
  dgemm_("T", "T", &n, &n, &n, &done, A, &n, B, &n, &done, D, &n);
  printf("LAPACK: nr_oper %lf, %lf\n", nr_oper, D[0]);

  for(i=0;i<ROZMIAR;i++) D[i]=0.0;
  t1 = omp_get_wtime();
  //sgemm_("T", "T", &n, &n, &n, &done, A, &n, B, &n, &done, D, &n);
  dgemm_("T", "T", &n, &n, &n, &done, A, &n, B, &n, &done, D, &n);
  t2 = omp_get_wtime();

  printf("Execution time - %lf, \tGFLOPS = %lf\n\n",
 	 t2-t1, nr_oper/(t2-t1)/1024/1024/1024);

 //check results
  for(i=0;i<WYMIAR;i++){
    for(j=0;j<WYMIAR;j++){
      if(fabs(C[i*n+j]-D[j*n+i])/fabs(C[i*n+j])>1.e-9) { // for double precision
      //if(fabs(C[i*n+j]-D[j*n+i])/fabs(C[i*n+j])>1.e-4) { // for single precision
        printf("error: %lf%% (C[%d,%d] = %lf, D[%d,%d] = %lf)\n",
             fabs(C[i*n+j]-D[j*n+i])/fabs(C[i*n+j]),
 	     i, j, C[i*n+j], j, i, D[i+n*j] );
	//getchar();getchar();
      }
    }
  }

  //free(A);
  //free(B);
  //free(C);
  //free(D);
  _mm_free(A);
  _mm_free(B);
  _mm_free(C);
  _mm_free(D);

  return(0);
}

