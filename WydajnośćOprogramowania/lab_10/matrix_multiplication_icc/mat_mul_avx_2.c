#include <stdlib.h>
#include <stdio.h>

#include <immintrin.h>
#include <emmintrin.h>

// definitions of: SCALAR, BLOCK_SIZE_S, BLOCK_SIZE_L and ALIGNMENT
#include "sizes.h"

void mat_mul_avx_2(SCALAR *a, SCALAR *b, SCALAR* c, int n)
{

  //  __assume_aligned(a, ALIGNMENT);
  //  __assume_aligned(b, ALIGNMENT);
  //  __assume_aligned(c, ALIGNMENT);
    
  int i,j,k;
  
  const int bbl=BLOCK_SIZE_L;  // to be used for two level blocking
  //const int bbl=BLOCK_SIZE_S; // to begin with a single cache blocking
#pragma omp parallel for default(none) firstprivate(a,b,c,n,bbl) private(i,j,k)
  for(i=0;i<n;i+=4){
    for(j=0;j<n;j+=3*4){
      for(k=0;k<n;k+=4){
	
  //for(i=0;i<n;i+=bbl){
    //for(j=0;j<n;j+=bbl){
      //for(k=0;k<n;k+=bbl){

	//const int bls=BLOCK_SIZE_S; // to be used only for two level blocking
	//register int kkk,jjj,iii;
	{
	  {
	    {

	      register int kk = k;
	      register int jj = j;
	      register int ii = i;
	      //register int kk,jj,ii; // for single level blocking
	      
	      {
		{
		  
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


		  {
		       
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
  
  

}
