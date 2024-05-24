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
    printf("%i\t", koren->podatak);
    stampajInOrder(koren->desni);
  }
}

void stampajAps(Cvor* koren){
 if(koren!=NULL){
    if(koren->podatak<0)koren->podatak=-(koren->podatak);
    stampajAps(koren->levi);
    printf("%i\t", koren->podatak);
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
  if(stablo==NULL)return 1;
  if(stablo->podatak<10)return stablo->podatak*proizvod_manjih(stablo->desni)*proizvod_manjih(stablo->levi);
  return proizvod_manjih(stablo->levi)*proizvod_manjih(stablo->desni);
}

int brojE(Cvor *koren, int e){
    if(koren==NULL)return 0;
    if(koren->podatak>e) return 1+brojE(koren->levi,e)+brojE(koren->desni,e);
    return brojE(koren->levi,e)+brojE(koren->desni,e);
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

Cvor* nadjiR(Cvor* stablo, int x){
    if(stablo==NULL||stablo->podatak==x)return stablo;
    if(stablo->podatak>x)return nadjiR(stablo->levi, x);
    return nadjiR(stablo->desni, x);
}

Cvor* nadji(Cvor* koren, int x){
    while(koren!=NULL && koren->podatak!=x){
        if(x<koren->podatak)koren=koren->levi;
            else koren=koren->desni;
    }
    return koren;
}

Cvor* maksCvorR(Cvor* stablo){
    if(stablo->desni==NULL)return stablo;
    return maksCvorR(stablo->desni);
}

int main(){
  Cvor* stablo=NULL;
  int i, x, n, temp, e;
  printf("Unesi temp");
  scanf("%i",&temp);
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
  printf("\nUnesite E: ");
  scanf("%i", &e);
  printf("\nVelicina stabla je %i, proizvod cvorova je %i, suma cvorova je %i, proizvod manjih od 10 je %i\nBroj vecih od E je %i", velicina(stablo), proizvod(stablo), suma(stablo), proizvod_manjih(stablo), brojE(stablo, e));
  //listovi(stablo);
  Cvor* stablo2=nadji(stablo,e);
  if(stablo2!=NULL){
        printf("\nPostoji E.");
  }else printf("\nNepostoji E.");

  return 0;
}
