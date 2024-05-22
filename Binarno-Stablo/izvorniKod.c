#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct cvor{
  int podatak;
  struct cvor *desni, *levi;
}Cvor;

Cvor* dodaje(Cvor *koren, int x){
  Cvor* novi=(Cvor*)malloc(sizeof(Cvor));
  if(novi==NULL){
    printf("Greska pri alociranju.");
    return NULL;
  }
  novi->podatak=x;
  novi->levi=NULL;
  novi->desni=NULL;
  if(koren==NULL)return novi;

  Cvor* stablo=koren;
  while(1){ //ovo je beskrajan ciklus
    if(x<stablo->podatak){
      if(stablo->levi!=NULL){
        stablo=stablo->levi;
      }else{
        stablo->levi=novi;
        return koren;
      }
    }else{
      if(stablo->desni!=NULL){
        stablo=stablo->desni;
      }else{
        stablo->desni=novi;
        return koren;
      }
    }
  }
}

void stampajInOrder(Cvor* koren){
 if(koren!=NULL){
    stampajInOrder(koren->levi);
    printf("%i", koren->podatak);
    stampajInOrder(koren->desni);
  }
}

void stampajAps(Cvor* koren){
 if(koren!=NULL){
    if(koren->podatak<0)koren->podatak=-(koren->podatak);
    stampajAps(koren->levi);
    printf("%i", koren->podatak);
    stampajAps(koren->desni);
  }
}

int suma(Cvor* stablo){
  if(stablo==NULL)return 0;
  return stablo->podatak + suma(stablo->levi) + suma(stablo->desni);
}

int velicina(Cvor* stablo){
  if(stablo==NULL)return 0;
  return 1 + velicina(stablo->levi) + velicina(stablo->desni);
}

int proizvod(Cvor* stablo){
  if(stablo==NULL)return 1;
  return stablo->podatak * proizvod(stablo->levi) * proizvod(stablo->desni);
}

int proizvod_manjih(Cvor* stablo){
  if(stablo==NULL || stablo->podatak>10) return 1;
  return stablo->podatak * proizvod_manjih(stablo->levi) * proizvod_manjih(stablo->desni);
}

void listovi(Cvor* stablo){
  if(stablo->levi!=NULL){
    listovi(stablo->levi);
    if(stablo->desni!=NULL){
      listovi(stablo->desni);
    }
    return;
  }
  if(stablo->desni!=NULL){
    listovi(stablo->desni);
    return;
  }
  printf("%i\t", stablo->podatak);
}

int main(){
  Cvor* stablo=NULL;
  int i, x, n;
  printf("Unesi broj cvorova: ");
  scanf("%i", &n);
  for(i=0;i<n;i++){
    printf("Unesi x: ");
    scanf("%i", &x);
    stablo=dodaje(stablo, x);
  }
  stampajInOrder(stablo);
  printf("\n");
  stampajAps(stablo);
  printf("\nVelicina stabla je %i, proizvod cvorova je %i, suma cvorova je %i, proizvod manjih od 10 je %i\nListovi su:\n", velicina(stablo), proizvod(stablo), suma(stablo), proizvod_manjih(stablo));
  listovi(stablo);
  return 0;
}
