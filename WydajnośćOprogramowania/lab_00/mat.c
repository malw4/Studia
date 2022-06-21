#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
 

const int liczba = 10;

int main(){
  double a, b, *c,p=0.1;
  int i,j,k,wyn,d=3;//d-szerokoœæ pasma, p=procent tu 10%
  c=(double*)malloc(liczba*liczba * sizeof(double));

  srand(time(NULL));

  printf("\nPodaj dwie liczby rzeczywiste\n");
  scanf("%lf %lf", &a, &b);
  printf("Losowe liczby rzeczywiste z zakresu : %lf - %lf:\n", a, b);

  for(i=0;i<liczba;i++){
		for(j=0;j<liczba;j++){
			//wyn= rand() % (2); //gdy wyn=1 tworzona jest liczba
			if(abs(i-j)<=d){	
				     c[i*liczba+j]= a+ ( (double)(b-a)*rand()/(RAND_MAX)); 

			}
		
			#ifdef DEBUG
					if(c<a || c>b) {
						printf("Blad generacji %lf\n", c); exit(0);
					}
			#endif
			printf("c[%ld]=%lf ",i*liczba+j,c[i*liczba+j]);
		}
  }
}
