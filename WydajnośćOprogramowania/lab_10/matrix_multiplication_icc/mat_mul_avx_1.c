#include <immintrin.h>
#include <emmintrin.h>
#include <stdlib.h>
#include <stdio.h>

// definitions of: SCALAR, BLOCK_SIZE_S, BLOCK_SIZE_L and ALIGNMENT
#include "sizes.h"

void mat_mul_avx_1(SCALAR *a, SCALAR *b, SCALAR* c, int n)
{

  //  __assume_aligned(a, ALIGNMENT);
  //  __assume_aligned(b, ALIGNMENT);
  //  __assume_aligned(c, ALIGNMENT);
   
  int i,j,k;
  
  //const int bbl=BLOCK_SIZE_L;  // to be used only for two level blocking
  const int bbl=BLOCK_SIZE_S; // to begin with a single cache blocking
#pragma omp parallel for default(none) firstprivate(a,b,c,n,bbl) private(i,j,k)
  for(i=0;i<n;i+=4){
    for(j=0;j<n;j+=4){
      for(k=0;k<n;k+=4){
	
	register int kk = k;
	register int jj = j;
	register int ii = i;
  	//register int kk,jj,ii;
  	/* for(ii=;ii<;ii+=4){ */
  	/*   for(kk=;kk<;kk+=4){ */
  	/*     for(jj=;jj<;jj+=4){ */
	{
	  {
	    {
	      
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
	      //__m256d v_c15 = _mm256_load_pd(&c[iin+jj+4]);
	      //__m256d v_c25 = _mm256_load_pd(&c[ii1n+jj+4]);
	      //__m256d v_c35 = _mm256_load_pd(&c[ii2n+jj+4]);
	      //__m256d v_c45 = _mm256_load_pd(&c[ii3n+jj+4]);
	      
              __m256d v_a11 = _mm256_broadcast_sd(&a[iin+kk]);
              __m256d v_a21 = _mm256_broadcast_sd(&a[ii1n+kk]);
              __m256d v_a31 = _mm256_broadcast_sd(&a[ii2n+kk]);
              __m256d v_a41 = _mm256_broadcast_sd(&a[ii3n+kk]);
	      
	      __m256d v_b11 = _mm256_load_pd(&b[kkn+jj]);
	      //__m256d v_b15 = _mm256_load_pd(&b[kkn+jj+4]);
	      
	      v_c11 = _mm256_fmadd_pd(v_a11, v_b11, v_c11);
	      v_c21 = _mm256_fmadd_pd(v_a21, v_b11, v_c21);
	      v_c31 = _mm256_fmadd_pd(v_a31, v_b11, v_c31);
	      v_c41 = _mm256_fmadd_pd(v_a41, v_b11, v_c41);
	      //v_c15 = _mm256_fmadd_pd(v_a11, v_b15, v_c15);
	      //v_c25 = _mm256_fmadd_pd(v_a21, v_b15, v_c25);
	      //v_c35 = _mm256_fmadd_pd(v_a31, v_b15, v_c35);
	      //v_c45 = _mm256_fmadd_pd(v_a41, v_b15, v_c45);
	      
	      
              __m256d v_a12 = _mm256_broadcast_sd(&a[iin+(kk+1)]);
              __m256d v_a22 = _mm256_broadcast_sd(&a[ii1n+(kk+1)]);
              __m256d v_a32 = _mm256_broadcast_sd(&a[ii2n+(kk+1)]);
              __m256d v_a42 = _mm256_broadcast_sd(&a[ii3n+(kk+1)]);
	      
	      __m256d v_b21 = _mm256_load_pd(&b[kk1n+jj]);
	      //__m256d v_b25 = _mm256_load_pd(&b[kk1n+jj+4]);
	      
	      v_c11 = _mm256_fmadd_pd(v_a12, v_b21, v_c11);
	      v_c21 = _mm256_fmadd_pd(v_a22, v_b21, v_c21);
	      v_c31 = _mm256_fmadd_pd(v_a32, v_b21, v_c31);
	      v_c41 = _mm256_fmadd_pd(v_a42, v_b21, v_c41);
	      
	      
              __m256d v_a13 = _mm256_broadcast_sd(&a[iin+(kk+2)]);
              __m256d v_a23 = _mm256_broadcast_sd(&a[ii1n+(kk+2)]);
              __m256d v_a33 = _mm256_broadcast_sd(&a[ii2n+(kk+2)]);
              __m256d v_a43 = _mm256_broadcast_sd(&a[ii3n+(kk+2)]);
	      
	      __m256d v_b31 = _mm256_load_pd(&b[kk2n+jj]);
	      //__m256d v_b35 = _mm256_load_pd(&b[kk2n+jj+4]);
	      
	      v_c11 = _mm256_fmadd_pd(v_a13, v_b31, v_c11);
	      v_c21 = _mm256_fmadd_pd(v_a23, v_b31, v_c21);
	      v_c31 = _mm256_fmadd_pd(v_a33, v_b31, v_c31);
	      v_c41 = _mm256_fmadd_pd(v_a43, v_b31, v_c41);
	      
	      
              __m256d v_a14 = _mm256_broadcast_sd(&a[iin+(kk+3)]);
              __m256d v_a24 = _mm256_broadcast_sd(&a[ii1n+(kk+3)]);
              __m256d v_a34 = _mm256_broadcast_sd(&a[ii2n+(kk+3)]);
              __m256d v_a44 = _mm256_broadcast_sd(&a[ii3n+(kk+3)]);
	      
	      __m256d v_b41 = _mm256_load_pd(&b[kk3n+jj]);
	      //__m256d v_b45 = _mm256_load_pd(&b[kk3n+jj+4]);
	      
	      
	      v_c11 = _mm256_fmadd_pd(v_a14, v_b41, v_c11);
	      v_c21 = _mm256_fmadd_pd(v_a24, v_b41, v_c21);
	      v_c31 = _mm256_fmadd_pd(v_a34, v_b41, v_c31);
	      v_c41 = _mm256_fmadd_pd(v_a44, v_b41, v_c41);
	      
	      
	      _mm256_store_pd(&c[iin+jj], v_c11);
	      _mm256_store_pd(&c[ii1n+jj], v_c21);
	      _mm256_store_pd(&c[ii2n+jj], v_c31);
	      _mm256_store_pd(&c[ii3n+jj], v_c41);
	      //_mm256_store_pd(&c[iin+jj+4], v_c2);
	      
	      
            }
          }
        }
	
      }
    }
  }
  
  
  
}
