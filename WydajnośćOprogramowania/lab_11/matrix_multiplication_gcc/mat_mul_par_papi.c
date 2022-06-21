#include <stdlib.h>
#include <stdio.h>
#include <immintrin.h>
#include <emmintrin.h>

#ifdef _OPENMP
#include <omp.h>
#else
#error "This compiler does not understand OPENMP"
#endif

// definitions of: SCALAR, BLOCK_SIZE_S, BLOCK_SIZE_L and ALIGNMENT
#include "sizes.h"

#ifdef PAPI_TEST
#include "papi.h"
#include "papi_driver_mth.h"
#endif

#define WERSJA 4
// WERSJA 5 wymaga rozmiaru macierzy podzielnego przez 12

void mat_mul_par_papi(SCALAR *a, SCALAR *b, SCALAR* c, int n)
{
  
//#pragma omp parallel default(none) shared(a,b,c,n)
  {
    
    int thread_id = omp_get_thread_num();
    
    
#ifdef PAPI_TEST
    int retval = PAPI_register_thread(  );
    if ( retval != PAPI_OK ) {
      printf( "Thread %d not registered! Exiting.\n", thread_id);
      getchar(); getchar();
      exit(0);
    }
    papi_driver_mth_add_events(thread_id);
#endif
    
#ifdef PAPI_TEST
    if(thread_id>=0){
      papi_driver_mth_reset_events(thread_id);
      papi_driver_mth_start_events(thread_id);
    }
#endif
    
    int i,j,k;
    int ii,jj,kk; 
    
    const int BLS = BLOCK_SIZE_S;    
    
    
    // matrix c initialized in mat_mul_driver.c
    
    
#if WERSJA == 1 	
    printf("wersja naiwna\n");
//#pragma omp for
    for(i=0;i<n;i++){
      for(j=0;j<n;j++){
	for(k=0;k<n;k++){
	  c[i*n+j] += a[i*n+k]*b[k*n+j];
	}
      }
    }
    
#elif WERSJA == 2 	
    printf("wersja poprawna niezoptymalizowana\n");
//#pragma omp for
    for(i=0;i<n;i++){
      for(k=0;k<n;k++){
	for(j=0;j<n;j++){
	  c[i*n+j] += a[i*n+k]*b[k*n+j];
	}
      }
    }
    
#elif WERSJA == 3
    printf("wersja cache blocking\n");

    #pragma omp parallel for default(none) shared(a,b,c,n) private(i,j,k,ii,jj,kk)
  for(i=0;i<n;i+=BLOCK_SIZE_S){
    for(k=0;k<n;k+=BLOCK_SIZE_S){
      for(j=0;j<n;j+=BLOCK_SIZE_S){ 
	for(ii=i;ii<i+BLOCK_SIZE_S;ii++){
    	 for(kk=k;kk<k+BLOCK_SIZE_S;kk++){
      	  for(jj=j;jj<j+BLOCK_SIZE_S;jj++){

	c[ii*n+jj] += a[ii*n+kk]*b[kk*n+jj];
}
}
}
      }
    }
  }


    
#elif WERSJA == 4 					
  printf("wersja cache blocking+wektoryzacja (4x4x4)\n");
//#pragma omp for
  for(i=0;i<n;i+=BLS){
    for(j=0;j<n;j+=BLS){
      for(k=0;k<n;k+=BLS){
    	for(ii=i;ii<i+BLS;ii+=4){
  	  for(kk=k;kk<k+BLS;kk+=4){
  	    for(jj=j;jj<j+BLS;jj+=4){
	     
	           
  	      register int iin = ii*n;
  	      register int ii1n = (ii+1)*n;
  	      register int ii2n = (ii+2)*n;
  	      register int ii3n = (ii+3)*n;
	      
  	      register int kkn = kk*n;
  	      register int kk1n = (kk+1)*n;
  	      register int kk2n = (kk+2)*n;
  	      register int kk3n = (kk+3)*n;

  	      __m256d v_c11 = _mm256_load_pd(&c[iin+jj]);
  	      __m256d v_c21 = _mm256_load_pd(&c[ii1n+jj]);
  	      __m256d v_c31 = _mm256_load_pd(&c[ii2n+jj]);
  	      __m256d v_c41 = _mm256_load_pd(&c[ii3n+jj]);
	      
              __m256d v_a11 = _mm256_broadcast_sd(&a[iin+kk]);
              __m256d v_a21 = _mm256_broadcast_sd(&a[ii1n+kk]);
              __m256d v_a31 = _mm256_broadcast_sd(&a[ii2n+kk]);
              __m256d v_a41 = _mm256_broadcast_sd(&a[ii3n+kk]);
	      
  	      __m256d v_b11 = _mm256_load_pd(&b[kkn+jj]);
	      
  	      v_c11 = _mm256_fmadd_pd(v_a11, v_b11, v_c11);
  	      v_c21 = _mm256_fmadd_pd(v_a21, v_b11, v_c21);
  	      v_c31 = _mm256_fmadd_pd(v_a31, v_b11, v_c31);
  	      v_c41 = _mm256_fmadd_pd(v_a41, v_b11, v_c41);
	      
	      
              __m256d v_a12 = _mm256_broadcast_sd(&a[iin+(kk+1)]);
              __m256d v_a22 = _mm256_broadcast_sd(&a[ii1n+(kk+1)]);
              __m256d v_a32 = _mm256_broadcast_sd(&a[ii2n+(kk+1)]);
              __m256d v_a42 = _mm256_broadcast_sd(&a[ii3n+(kk+1)]);
	      
  	      __m256d v_b21 = _mm256_load_pd(&b[kk1n+jj]);
	      
  	      v_c11 = _mm256_fmadd_pd(v_a12, v_b21, v_c11);
  	      v_c21 = _mm256_fmadd_pd(v_a22, v_b21, v_c21);
  	      v_c31 = _mm256_fmadd_pd(v_a32, v_b21, v_c31);
  	      v_c41 = _mm256_fmadd_pd(v_a42, v_b21, v_c41);
	      
	      
              __m256d v_a13 = _mm256_broadcast_sd(&a[iin+(kk+2)]);
              __m256d v_a23 = _mm256_broadcast_sd(&a[ii1n+(kk+2)]);
              __m256d v_a33 = _mm256_broadcast_sd(&a[ii2n+(kk+2)]);
              __m256d v_a43 = _mm256_broadcast_sd(&a[ii3n+(kk+2)]);
	      
  	      __m256d v_b31 = _mm256_load_pd(&b[kk2n+jj]);
	      
  	      v_c11 = _mm256_fmadd_pd(v_a13, v_b31, v_c11);
  	      v_c21 = _mm256_fmadd_pd(v_a23, v_b31, v_c21);
  	      v_c31 = _mm256_fmadd_pd(v_a33, v_b31, v_c31);
  	      v_c41 = _mm256_fmadd_pd(v_a43, v_b31, v_c41);
	      
	      
              __m256d v_a14 = _mm256_broadcast_sd(&a[iin+(kk+3)]);
              __m256d v_a24 = _mm256_broadcast_sd(&a[ii1n+(kk+3)]);
              __m256d v_a34 = _mm256_broadcast_sd(&a[ii2n+(kk+3)]);
              __m256d v_a44 = _mm256_broadcast_sd(&a[ii3n+(kk+3)]);
	      
  	      __m256d v_b41 = _mm256_load_pd(&b[kk3n+jj]);
	      
	      
  	      v_c11 = _mm256_fmadd_pd(v_a14, v_b41, v_c11);
  	      v_c21 = _mm256_fmadd_pd(v_a24, v_b41, v_c21);
  	      v_c31 = _mm256_fmadd_pd(v_a34, v_b41, v_c31);
  	      v_c41 = _mm256_fmadd_pd(v_a44, v_b41, v_c41);
	      
	      
  	      _mm256_store_pd(&c[iin+jj], v_c11);
  	      _mm256_store_pd(&c[ii1n+jj], v_c21);
  	      _mm256_store_pd(&c[ii2n+jj], v_c31);
  	      _mm256_store_pd(&c[ii3n+jj], v_c41);
	      
	      
            }
          }
        }
	
      }
    }
  }

#elif WERSJA == 5					
  printf("wersja cache blocking+wektoryzacja (4x12x4)\n");


  //const int bbl=BLOCK_SIZE_L; // in sizes.h
  // to get single level blocking
  const int bbl=n;  // 
  const int bls=BLOCK_SIZE_S; // in sizes.h
  //const int bls=108; // (108 for L1+L2)

  // another way to get single level blocking
  // const int bbl=BLOCK_SIZE_S;  
  // const int bls=BLOCK_SIZE_S; // (108 for L1+L2)
 
  
  // for size=1080 - only single thread version reasonable
//#pragma omp  for 
  
 
  // two level cache blocking - large blocks (e.g. for L3)	
  for(i=0;i<n;i+=bbl){
    for(j=0;j<n;j+=bbl){
      for(k=0;k<n;k+=bbl){
	
	register int kkk,jjj,iii;
	
	// two level cache blocking - small blocks (e.g. for L1+L2)	
	for(jjj=j;jjj<j+bbl;jjj+=bls){
	  for(iii=i;iii<i+bbl;iii+=bls){
	    for(kkk=k;kkk<k+bbl;kkk+=bls){
	      
	      register int kk,jj,ii; // for single level blocking
	      		  
	      // two level cache blocking - final register blocking
	      for(ii=iii;ii<iii+bls;ii+=4){
		for(jj=jjj;jj<jjj+bls;jj+=3*4){

		  register int iin = ii*n;
		  register int ii1n = (ii+1)*n;
		  register int ii2n = (ii+2)*n;
		  register int ii3n = (ii+3)*n;
		  
		  __m256d v_c11 = _mm256_load_pd(&c[iin+jj]);
		  __m256d v_c21 = _mm256_load_pd(&c[ii1n+jj]);
		  __m256d v_c31 = _mm256_load_pd(&c[ii2n+jj]);
		  __m256d v_c41 = _mm256_load_pd(&c[ii3n+jj]);
		  
		  __m256d v_c12 = _mm256_load_pd(&c[iin+jj+4]);
		  __m256d v_c22 = _mm256_load_pd(&c[ii1n+jj+4]);
		  __m256d v_c32 = _mm256_load_pd(&c[ii2n+jj+4]);
		  __m256d v_c42 = _mm256_load_pd(&c[ii3n+jj+4]);
		  
		  __m256d v_c13 = _mm256_load_pd(&c[iin+jj+8]);
		  __m256d v_c23 = _mm256_load_pd(&c[ii1n+jj+8]);
		  __m256d v_c33 = _mm256_load_pd(&c[ii2n+jj+8]);
		  __m256d v_c43 = _mm256_load_pd(&c[ii3n+jj+8]);
		  
		  // two level cache blocking - final register blocking
		  for(kk=kkk;kk<kkk+bls;kk+=4){
		    
		    register int kkn = kk*n;
		    register int kk1n = (kk+1)*n;
		    register int kk2n = (kk+2)*n;
		    register int kk3n = (kk+3)*n;
		    	    
		    __m256d v_a = _mm256_broadcast_sd(&a[iin+kk]);
		    __m256d v_b1 = _mm256_load_pd(&b[kkn+jj]);
		    v_c11 = _mm256_fmadd_pd(v_a, v_b1, v_c11);
		    __m256d v_b2 = _mm256_load_pd(&b[kkn+jj+4]);
		    v_c12 = _mm256_fmadd_pd(v_a, v_b2, v_c12);
		    __m256d v_b3 = _mm256_load_pd(&b[kkn+jj+8]);
		    v_c13 = _mm256_fmadd_pd(v_a, v_b3, v_c13);

		    v_a = _mm256_broadcast_sd(&a[ii1n+kk]);
		    v_c21 = _mm256_fmadd_pd(v_a, v_b1, v_c21);
		    v_c22 = _mm256_fmadd_pd(v_a, v_b2, v_c22);
		    v_c23 = _mm256_fmadd_pd(v_a, v_b3, v_c23);

		    v_a = _mm256_broadcast_sd(&a[ii2n+kk]);
		    v_c31 = _mm256_fmadd_pd(v_a, v_b1, v_c31);
		    v_c32 = _mm256_fmadd_pd(v_a, v_b2, v_c32);
		    v_c33 = _mm256_fmadd_pd(v_a, v_b3, v_c33);

		    v_a = _mm256_broadcast_sd(&a[ii3n+kk]);
		    v_c41 = _mm256_fmadd_pd(v_a, v_b1, v_c41);
		    v_c42 = _mm256_fmadd_pd(v_a, v_b2, v_c42);
		    v_c43 = _mm256_fmadd_pd(v_a, v_b3, v_c43);


		    v_a = _mm256_broadcast_sd(&a[iin+kk+1]);
		    v_b1 = _mm256_load_pd(&b[kk1n+jj]);
		    v_c11 = _mm256_fmadd_pd(v_a, v_b1, v_c11);
		    v_b2 = _mm256_load_pd(&b[kk1n+jj+4]);
		    v_c12 = _mm256_fmadd_pd(v_a, v_b2, v_c12);
		    v_b3 = _mm256_load_pd(&b[kk1n+jj+8]);
		    v_c13 = _mm256_fmadd_pd(v_a, v_b3, v_c13);

		    v_a = _mm256_broadcast_sd(&a[ii1n+kk+1]);
		    v_c21 = _mm256_fmadd_pd(v_a, v_b1, v_c21);
		    v_c22 = _mm256_fmadd_pd(v_a, v_b2, v_c22);
		    v_c23 = _mm256_fmadd_pd(v_a, v_b3, v_c23);

		    v_a = _mm256_broadcast_sd(&a[ii2n+kk+1]);
		    v_c31 = _mm256_fmadd_pd(v_a, v_b1, v_c31);
		    v_c32 = _mm256_fmadd_pd(v_a, v_b2, v_c32);
		    v_c33 = _mm256_fmadd_pd(v_a, v_b3, v_c33);

		    v_a = _mm256_broadcast_sd(&a[ii3n+kk+1]);
		    v_c41 = _mm256_fmadd_pd(v_a, v_b1, v_c41);
		    v_c42 = _mm256_fmadd_pd(v_a, v_b2, v_c42);
		    v_c43 = _mm256_fmadd_pd(v_a, v_b3, v_c43);


		    v_a = _mm256_broadcast_sd(&a[iin+kk+2]);
		    v_b1 = _mm256_load_pd(&b[kk2n+jj]);
		    v_c11 = _mm256_fmadd_pd(v_a, v_b1, v_c11);
		    v_b2 = _mm256_load_pd(&b[kk2n+jj+4]);
		    v_c12 = _mm256_fmadd_pd(v_a, v_b2, v_c12);
		    v_b3 = _mm256_load_pd(&b[kk2n+jj+8]);
		    v_c13 = _mm256_fmadd_pd(v_a, v_b3, v_c13);

		    v_a = _mm256_broadcast_sd(&a[ii1n+kk+2]);
		    v_c21 = _mm256_fmadd_pd(v_a, v_b1, v_c21);
		    v_c22 = _mm256_fmadd_pd(v_a, v_b2, v_c22);
		    v_c23 = _mm256_fmadd_pd(v_a, v_b3, v_c23);

		    v_a = _mm256_broadcast_sd(&a[ii2n+kk+2]);
		    v_c31 = _mm256_fmadd_pd(v_a, v_b1, v_c31);
		    v_c32 = _mm256_fmadd_pd(v_a, v_b2, v_c32);
		    v_c33 = _mm256_fmadd_pd(v_a, v_b3, v_c33);

		    v_a = _mm256_broadcast_sd(&a[ii3n+kk+2]);
		    v_c41 = _mm256_fmadd_pd(v_a, v_b1, v_c41);
		    v_c42 = _mm256_fmadd_pd(v_a, v_b2, v_c42);
		    v_c43 = _mm256_fmadd_pd(v_a, v_b3, v_c43);


		    v_a = _mm256_broadcast_sd(&a[iin+kk+3]);
		    v_b1 = _mm256_load_pd(&b[kk3n+jj]);
		    v_c11 = _mm256_fmadd_pd(v_a, v_b1, v_c11);
		    v_b2 = _mm256_load_pd(&b[kk3n+jj+4]);
		    v_c12 = _mm256_fmadd_pd(v_a, v_b2, v_c12);
		    v_b3 = _mm256_load_pd(&b[kk3n+jj+8]);
		    v_c13 = _mm256_fmadd_pd(v_a, v_b3, v_c13);

		    v_a = _mm256_broadcast_sd(&a[ii1n+kk+3]);
		    v_c21 = _mm256_fmadd_pd(v_a, v_b1, v_c21);
		    v_c22 = _mm256_fmadd_pd(v_a, v_b2, v_c22);
		    v_c23 = _mm256_fmadd_pd(v_a, v_b3, v_c23);

		    v_a = _mm256_broadcast_sd(&a[ii2n+kk+3]);
		    v_c31 = _mm256_fmadd_pd(v_a, v_b1, v_c31);
		    v_c32 = _mm256_fmadd_pd(v_a, v_b2, v_c32);
		    v_c33 = _mm256_fmadd_pd(v_a, v_b3, v_c33);

		    v_a = _mm256_broadcast_sd(&a[ii3n+kk+3]);
		    v_c41 = _mm256_fmadd_pd(v_a, v_b1, v_c41);
		    v_c42 = _mm256_fmadd_pd(v_a, v_b2, v_c42);
		    v_c43 = _mm256_fmadd_pd(v_a, v_b3, v_c43);


		    _mm256_store_pd(&c[iin+jj], v_c11);
		    _mm256_store_pd(&c[ii1n+jj], v_c21);
		    _mm256_store_pd(&c[ii2n+jj], v_c31);
		    _mm256_store_pd(&c[ii3n+jj], v_c41);
		  
		    _mm256_store_pd(&c[iin+jj+4], v_c12);
		    _mm256_store_pd(&c[ii1n+jj+4], v_c22);
		    _mm256_store_pd(&c[ii2n+jj+4], v_c32);
		    _mm256_store_pd(&c[ii3n+jj+4], v_c42);
		  
		    _mm256_store_pd(&c[iin+jj+8], v_c13);
		    _mm256_store_pd(&c[ii1n+jj+8], v_c23);
		    _mm256_store_pd(&c[ii2n+jj+8], v_c33);
		    _mm256_store_pd(&c[ii3n+jj+8], v_c43);
		    
		    
		  }
		}
	      }
	      
  	    }
  	  }
  	}
	
      }
    }
  }
  

#endif

    
#ifdef PAPI_TEST
    if(thread_id>=0){
      papi_driver_mth_stop_events(thread_id);
//#pragma omp critical(print_1)
      {
	printf("thread %d: RESULTS\n", thread_id);
	papi_driver_mth_print_events(thread_id);
      }
    }
    
    PAPI_unregister_thread();
#endif
   
  }
  
  return;
}


