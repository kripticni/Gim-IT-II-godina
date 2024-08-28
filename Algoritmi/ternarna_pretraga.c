#include <stdio.h>
#include <stdlib.h>

int main(){
  int l=0, h, n, x;

  printf("Unesite N: ");
  scanf("%i", &n);

  int niz[n];
  printf("Unesite elemente: \n");
  for(;l<n;l++){
    scanf("%i", &niz[l]);
  }

  h=n-1;
  l=0;

  printf("Unesite element koji trazite: ");
  scanf("%i", &x);
  
  while(1){
    int left = l + (h-l)/3;
    int right = h - (h-l)/3;

    if(niz[left]==x){
      printf("Nadjeno na %i", left);
      return 1;
    }
    if(niz[right]==x){
      printf("Nadjeno na %i", right);
      return 1;
    }

    if(x<niz[left]){
      h = left-1;
      if(l<=h) continue;
      else return 0; //ili break
    }
    if(x>niz[right]){
      l = right+1;
      if(l<=h) continue;
      else return 0; //ili break
    }
    l = left+1;
    h = right-1;
    //if(l>h) return 0;
  }

  return 0;
}
