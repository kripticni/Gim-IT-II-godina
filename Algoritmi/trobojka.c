#include <stdio.h>
#include <stdlib.h>

int main(){
  //National dutch flag problem inace, i izumeo ga je Dajkstra
  int A=0, B, n, i=0, l=0;
  printf("Unesi duzinu niza: ");
  scanf("%i", &n);

  int niz[n];
  for(;A<n;A++){
    scanf("%i", &B);
    niz[A]=B;
  }

  printf("Unesi minimum pa maksimum: \n");
  scanf("%i%i", &A, &B);

  int d=n-1;

  while(i<d){
    if(niz[i]<A){
      int pom=niz[i];
      niz[i]=niz[d];
      niz[d]=pom;
      i++;
      l++;
    }else{
      if(niz[i]<=B) i++;
      else{
        int pom=niz[i];
        niz[i]=niz[d];
        niz[d]=pom;
        d--;
      }
    }
  }

  printf("Manji od %i: \n", A);
  for(i=0;i<l;i++)
    printf("%i\n", niz[i]);
  
  printf("Izmedju %i-%i: \n", A, B);
  for(;i<=d;i++)
    printf("%i\n", niz[i]);

  printf("Veci od %i: \n", B);
  for(;i<n;i++){
    printf("%i\n", niz[i]);
  }
  return 0;
}
