#include <stdio.h>

int zbir1doN(int n){
  if(n == 0) return 0;
  return n + zbir1doN(n-1);
}

int fibonaci(int n){
  if(n == 0 || n == 1) return 1;
  return (fibonaci(n-1) + fibonaci(n-2));
}

int proizvodneparnih_1doX(int x){
  if(x == 0 || x == 1) return 1;
  if(x % 2 == 0) return 1 * proizvodneparnih_1doX(x-1);
  else return x * proizvodneparnih_1doX(x-1);
}

int pn_cifrax(int x){
  if(x == 0) return 0;
  int cifra = x%10;
  if(cifra % 2 == 0) return 1 * pn_cifrax(x/10);
  else return x * pn_cifrax(x/10);
}

int zbirkvadrata_nizaodn(int a[], int n){
  if(n == -1) return 0;
  return a[n]*a[n] + zbirkvadrata_nizaodn(a,n-1);
}

int min_nizaodn(int a[], int n){
  if(n == 0) return 2000000000;
  int min = min_nizaodn(a,n-1);
  if(a[n] < min) return a[n];
  else return min;
}

void deljivisa3_manjiod10(int a[], int n, int* zbir, int* broj){
  if(n == -1) return;
  if(a[n]%3 == 0) *zbir = *zbir + a[n];
  if(a[n] < 10) *broj = *broj + 1;
  return deljivisa3_manjiod10(a,n-1,zbir,broj);
}

void sadrzix_brneparnih(int a[], int n, int x, int* sadrzi, int* broj){
  if(n == -1) return;
  if(a[n] == x) *sadrzi = 1;
  if(a[n]%2 != 0) *broj = *broj + 1;
  return sadrzix_brneparnih(a,n-1,x,sadrzi,broj);
}

int main(){
  int niz[] = {12,3,4,5,6,13,15};
  int n = sizeof(niz)/sizeof(int);

  int zbir = 0, broj = 0;
  deljivisa3_manjiod10(niz,n-1,&zbir,&broj);
  printf("%i %i\n", zbir, broj);

  int x = 5,  da_li_sadrzi = 0, neparni = 0; 
  sadrzix_brneparnih(niz,n-1,x,&da_li_sadrzi,&neparni);
  printf("%i\n", neparni);
  if(da_li_sadrzi == 1) printf("Sadrzi");
  else printf("Ne sadrzi");
  return 0;
}
