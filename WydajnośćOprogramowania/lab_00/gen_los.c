#include<stdlib.h>
#include<stdio.h>
#include<time.h>
 

const int liczba = 10;

int main(){
FILE *fp;
 
if ((fp=fopen("test.txt", "w"))==NULL) {
     printf ("Nie mogę otworzyć pliku test.txt do zapisu!\n");
     exit(1);
     }
  double a, b, c=0,srednia;
  int i,j,k,l=0;

  srand(time(NULL));

  printf("\nPodaj dwie liczby rzeczywiste\n");
  scanf("%lf %lf", &a, &b);
  printf("Losowe liczby rzeczywiste z zakresu : %lf - %lf:\n", a, b);

  for(i=0;i<liczba;i++){

    c= a+ ( (double)(b-a)*rand()/(RAND_MAX)); 
srednia+=c;
fprintf(fp,"%lf\n",c);
    // printf("%lf ",c);

#ifdef DEBUG
    if(c<a || c>b) {
      printf("Blad generacji %lf\n", c); exit(0);
    }
#endif

  }
srednia=srednia/liczba;
 printf("Srednia z liczb zmiennoprzecinkowych: %lf\n",srednia);
  printf("\nPodaj dwie liczby calkowite\n");
  scanf("%d %d", &j, &k);
srednia=0;
  printf("Losowe liczby calkowite z zakresu : %d - %d:\n", j, k);

  for(i=0;i<liczba;i++){

     l =j+(int) ( (double)(k-j+1.0)*rand()/(RAND_MAX+1.0)); 
srednia+=l;
fprintf(fp,"%d\n",l);
    // printf("%d ",l);

#ifdef DEBUG
    if(l<j || l>k) {
      printf("Blad generacji %d\n", l); exit(0);
    }
    if(l==j || l==k) printf("Na granicy: %d\n", l);
#endif

  }
srednia=srednia/liczba;
printf("Srednia liczb calkowitych: %lf\n",srednia);
   fclose (fp); 
}
