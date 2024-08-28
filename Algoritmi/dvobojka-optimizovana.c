#include <stdio.h>
#include <stdlib.h>

int main(){
  int i = 0, k=0, n;

  printf("Unesi N: ");
  scanf("%i", &n);

  int niz[n];

  for(;i<n;i++){
    scanf("%i", &k);
    niz[i] = k;
  }

  i = 0;

  //for(;k<n;k++)

  for(;i<n;i++){
    if(niz[i]%2==0){
      int pom = niz[i];
      niz[i] = niz[k];
      niz[k] = pom;
      k++;
    }
  }

  for(i=0;i<n;i++){
    printf("%i", niz[i]);
  }

  return 0;
}
