#include <stdio.h>
#include <stdlib.h>

typedef struct delement{
  int podatak;
  struct delement* desni;
  struct delement* levi;
}Delement;

typedef struct cvor{
  int podatak;
  struct cvor* desni;
  struct cvor* levi;
}Cvor;

void insert(Delement** pocetak, Delement** kraj, int x){
  Delement* novi=(Delement*)malloc(sizeof(Delement));
  novi->levi=(*kraj);
  novi->desni=NULL;
  novi->podatak=x;
  if((*pocetak)==NULL){
    (*pocetak)=novi;
    (*kraj)=novi;
    return;
  }
  (*kraj)->desni=novi;
  (*kraj)=novi;
  return;
}

void upisi(Delement* pocetak, int arr[]){
  int i=0;
  while(pocetak!=NULL){
    arr[i]=pocetak->podatak;
    i++;
    pocetak=pocetak->desni;
  }
}

void stampaj(Delement* pocetak){
  for(;pocetak!=NULL;pocetak=pocetak->desni){
    printf("%i\t", pocetak->podatak);
  }
}

Cvor* inic(int arr[], int n){ //ovo je inic funkcija ali za deljivi sa 2 samo
  Cvor* koren=(Cvor*)malloc(sizeof(Cvor));
  int i=0;
  while(arr[i]%2==1)i++;
  koren->podatak=arr[i];
  koren->desni=NULL;
  koren->levi=NULL;

  Cvor* stablo;
  while(i<n){ 
  i++;
  if(arr[i]%2==0){ 
    stablo=koren;
    while(1){
        if(arr[i]<stablo->podatak){
          if(stablo->levi!=NULL){
            stablo=stablo->levi;
          }else{
            stablo->levi=(Cvor*)malloc(sizeof(Cvor));
            stablo->levi->podatak=arr[i];
            break;
          }
        }else{
          if(stablo->desni!=NULL){
            stablo=stablo->desni;
          }else{
            stablo->desni=(Cvor*)malloc(sizeof(Cvor));
            stablo->desni->podatak=arr[i];
            break;
          }
        }
    }
  }
  }
  return koren;
}

void listovi(Cvor* koren){
  if(koren->desni==NULL && koren->levi==NULL){
    printf("%i\t", koren->podatak);
    return;
  }
  if(koren->desni!=NULL)listovi(koren->desni);
  if(koren->levi!=NULL)listovi(koren->levi);
}

int main(){
  Delement* kraj=NULL;
  Delement* pocetak=NULL;
  Cvor* koren=NULL;

  int n;
  printf("Unesi n: ");
  scanf("%i", &n);

  int x;
  for(int i=0;i<n;i++){
    printf("Unesi podatak: ");
    scanf("%i", &x);
    insert(&pocetak, &kraj, x);
  }

  printf("Lista: ");
  stampaj(pocetak);

  int niz[n];
  upisi(pocetak, &niz[0]);

  koren=inic(niz, sizeof(niz)/sizeof(niz[0]));
  printf("\nListovi: ");
  listovi(koren);
  return 0;
}
