#include <stdio.h>
#include <stdlib.h>

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
int main(){
  Cvor* stablo=NULL;
  int i;
  for(i=0;i<100;i++){
    stablo=dodaje(stablo, i);
  }
  stampajInOrder(stablo);
  return 0;
}
