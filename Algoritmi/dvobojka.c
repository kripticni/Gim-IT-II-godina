#include <stdio.h>
#include <stdlib.h>

int main(){
  int i, n;
  printf("Unesi broj elemenata za niz: ");
  scanf("%i", &n);
  int niz[n]; //ovo je isto kao int int* niz = (int*)malloc(n * sizeof(int));
  //takodje je jedino podrzano sa compileri sa C99 iso standard ili kasnije

  int l = 0, r;

  for(;l<n;l++){
    scanf("%i", &r);
    niz[l] = r;
  }

  r = n-1;
  l = 0;

  while(l<r){
    if(niz[l]%2==0){ //najnoviji gcc compiler prevodi ovo kao !(niz[l]&1) svakako
      l++;
    }else{
      if(niz[r]%2!=0){
        r--;
      }else{
        int pom = niz[l];
        niz[l] = niz[r];
        niz[r] = pom;
        r--;
        l++; //idemo na sledece elemente
      }
    }
  }
  
  for(l=0;l<n;l++){
    printf("%i\t",niz[l]);
  }

  return 0;
}
