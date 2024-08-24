#include <stdio.h>
#include <stdlib.h>

int main(){
  int l = 0, m, n;

  printf("Unesi N: ");
  scanf("%i", &n);

  int niz[n];

  printf("Unesi niz tako da prvo idu elementi deljivim sa najvecim mogucim deliocem, pa onda brojeve sa manjim: \n");
  for(;l<n;l++){
    scanf("%i", &m);
    niz[l] = m;
  }

  l = 0;
  int h = n-1, x;

  printf("Delioc za koji zelite da nadjete broj elemenata koji su deljivi: ");
  scanf("%i", &x);
  
  while(l<=h){
    m = l + (l+h)/2;
    if(niz[m]%x!=0){
      h = m-1;
    }else{
      l = m+1;
    }
  }

  printf("Deljivi sa brojem %i, su %i", x, l);
  return 0;
}
