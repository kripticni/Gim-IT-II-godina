#include <stdio.h>
#include <stdlib.h>

int main(){
  int l = 0, m, n;

  printf("Unesi N: ");
  scanf("%i", &n);

  int niz[n];

  printf("Unesite niz sortiran tako da prvo idu elementi koji nisu deljivi sa 3, pa zatim oni koji jesu: \n");
  for(;l<n;l++){
    scanf("%i", &m);
    niz[l] = m;
  }

  l = 0;
  int h = n-1, x;

  printf("Unesite element koji trazite: ");
  scanf("%i", &x);
  
  while(l<=h){
    m = l + (l+h)/2;
    if(niz[m]%3==0){
      h = m-1;
    }else{
      l = m+1;
    }
  }

  printf("Koji nisu deljivi sa 3: %i\nKoji jesu deljivi sa 3: %i", m, n-m);
  return 0;
}
