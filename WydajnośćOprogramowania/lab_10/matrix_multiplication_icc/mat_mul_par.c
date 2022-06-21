#include <stdlib.h>
#include <stdio.h>
#include <immintrin.h>
#include <emmintrin.h>



// definitions of: SCALAR, BLOCK_SIZE_S, BLOCK_SIZE_L and ALIGNMENT
#include "sizes.h"

void mat_mul_par(SCALAR *a, SCALAR *b, SCALAR* c, int n)
{
  int i,j,k,ii,jj,kk;
//bls bock size
   
  // matrix c initialized in mat_mul_driver.c
/* #pragma omp parallel for default(none) shared(c,n) private(i,j) */
/*   for(i=0;i<n;i++){ */
/*     for(j=0;j<n;j++){ */
/*       c[i*n+j]=0.0; */
/*     } */
/*   } */

#pragma omp parallel for default(none) shared(a,b,c,n) private(i,j,k,ii,jj,kk)
  for(i=0;i<n;i+=BLOCK_SIZE_S){
    for(k=0;k<n;k+=BLOCK_SIZE_S){
      for(j=0;j<n;j+=BLOCK_SIZE_S){ 
				register int iin = ii*n;
				register int kkn = kk*n;
				for(ii=i;ii<i+BLOCK_SIZE_S;ii++){
					for(kk=k;kk<k+BLOCK_SIZE_S;kk++){
						for(jj=j;jj<j+BLOCK_SIZE_S;jj+=4){
							__m256d v_c11 = _mm256_load_pd(&c[iin+jj]);
							__m256d v_a11 = _mm256_broadcast_sd(&a[iin+kk]);
							__m256d v_b11 = _mm256_load_pd(&b[kkn+jj]);
							v_c11 = _mm256_fmadd_pd(v_a11, v_b11, v_c11);
							__mm256_store_pd(&c[iin+jj], v_c11);

				//c[ii*n+jj] += a[ii*n+kk]*b[kk*n+jj];
						}
					}
				}
      }
    }
  }

  return;
}
