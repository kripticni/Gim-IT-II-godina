#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //za bitset

int prost1(int n){
    int i=2;
    while(i<=n-1){
        if(n%i==0) return 0;
        i++;
    }
    return 1;
}

int prost2(int n){
    int i=2;
    while(i<=n/2){
        if(n%i==0) return 0;
        i++;
    }
    return 1;
}

int prost3(int n){
    int i=2;
    while(i*i<=n){
        if(n%i==0) return 0;
        i++;
    }
    return 1;
}

int prost1for(int n){
    int i=2;
    for(;i<=n-1;i++){
        if(n%i==0) return 0;
    }
    return 1;
}

int prost2for(int n){
    int i=2;
    for(;i<=n/2;i++){
        if(n%i==0) return 0;
    }
    return 1;
}

int prost3for(int n){
    int i=2;
    for(;i*i<=n;i++){
        if(n%i==0) return 0;
    }
    return 1;
}

void EratostenovoSito(int n, bool* stanja){ //nalazi sve brojeve od 1 do N
  int i, p=2;
  for(;p*p<=n;p++){
    if(stanja[p] == false) {
      for (i =p*p; i<=n; i+=p)
        stanja[i] = true;
    }
  }
  for (p = 2; p <= n; p++)
    if(!stanja[p])
      printf("%d ",p);
}
    
//obican euklidov algoritam pronalazi samo nzd, a prosireni takodje nalazi brojeve x i y
//ax+by = nzd(a,b)
//uzajamno prosti brojevi su oni ciji je nzd 1
//nalazi dva cela broja x i y od kojih ce uglavnom jedan biti negativan, koji sluzi za bezuovu teoremu
void prosireniEuklidov(){
    
}

//nalazi uzajamno proste brojeve sa brojem N
void eulerova()

//rastavljanje broja na proste cinioce
int main(){
  int n;
  printf("Unesite broj: ");
  scanf("%i", &n);
  (prost1(n) && prost2(n) && prost3(n) && prost1for(n) && prost2for(n) && prost3for(n))?printf("Prost broj.\n"):printf("Nije prost broj.\n");
  printf("Unesi broj do koga se traze prosti: ");
  scanf("%i", &n);
  bool* prosti = (bool*)calloc(n, sizeof(bool));
  EratostenovoSito(n, prosti);
  return 0;
}
