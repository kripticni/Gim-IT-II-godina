#include <stdio.h>
#include <stdlib.h>

int main(){
  int l = 0, m, n;

  printf("Unesi N: ");
  scanf("%i", &n);

  int niz[n];

  for(;l<n;l++){
    scanf("%i", &m);
    niz[l] = m;
  }

  l = 0;
  int h = n-1, x;

  printf("Unesite element koji trazite: ");
  scanf("%i", &x);
  
  while(l<=h){
    m = l + (h-l)/2;
    if(x>niz[m]){
      l = m+1;
    }else{
      if(x<niz[m]){
        h = m-1;
      }else{
        printf("Nadjen na %i.", m);
        return 1; //tacno
      }
    }
  }

  return 0; //exit kodovi kazu da je 0 sucessful, a 1 nije, ali u ovaj slucaj za funkciju
  //mozemo da kazemo obrnuto
}
