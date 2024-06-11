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

Cvor* dodajeRekurzivno(Cvor* koren, int x){
  if(koren==NULL){
    Cvor* novi=(Cvor*)malloc(sizeof(Cvor));
    novi->podatak=x;
    novi->levi=NULL;
    novi->desni=NULL;
    return novi;
  }
  if(x<koren->podatak){
    Cvor* novi=dodajeRekurzivno(koren->levi,x);
    if(novi != NULL){
      koren->levi=novi; 
    }
    return NULL;
  }else{
    Cvor* novi=dodajeRekurzivno(koren->desni,x);
    if(novi!=NULL){
      koren->desni=novi;
    }
    return NULL;
  }
}

Cvor* dodajeR(Cvor* koren, int x){
  if(koren==NULL)return dodajeRekurzivno(koren,x);
  dodajeRekurzivno(koren,x);
  return koren;
}//NIJE POTREBNO OVO

void stampajInOrder(Cvor* koren){
 if(koren!=NULL){
    stampajInOrder(koren->levi);
    printf("%i\t", koren->podatak);
    stampajInOrder(koren->desni);
 }
}

void stampajPostOrder(Cvor* koren){
 if(koren!=NULL){
    stampajPostOrder(koren->levi);
    stampajPostOrder(koren->desni);
    printf("%i\t", koren->podatak);
 }
}

void stampajPreOrder(Cvor* koren){
 if(koren!=NULL){
    printf("%i\t", koren->podatak);
    stampajPreOrder(koren->levi);
    stampajPreOrder(koren->desni);
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
  return suma(stablo->levi) + stablo->podatak + suma(stablo->desni);
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

void listoviBiljana(Cvor* stablo){
  if(stablo->desni==NULL && stablo->levi==NULL){
    printf("%i\t", stablo->podatak);
    return;
  }
  if(stablo->desni!=NULL)listoviBiljana(stablo->desni);
  if(stablo->levi!=NULL)listoviBiljana(stablo->levi);
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

Cvor* maksCvor(Cvor* stablo){
  while(stablo->desni!=NULL){
    stablo=stablo->desni;
  }
  return stablo;
}

Cvor* minCvorR(Cvor* stablo){
  if(stablo->desni==NULL)return stablo;
  return minCvorR(stablo->desni);
}

Cvor* minCvor(Cvor* stablo){
  while(stablo->levi!=NULL){
    stablo=stablo->levi;
  }
  return stablo;
}

Cvor* inic(int* niz, int n){
  Cvor* novi=(Cvor*)malloc(sizeof(Cvor));
  novi->podatak=*(niz); //ovde je iskoriscen niz[0] 
  novi->levi=NULL;
  novi->desni=NULL;
  Cvor* koren=novi; //ovaj novi ->
  for(int i=1;i<n;i++){ //zato se krece sa i=1
    Cvor* novi=(Cvor*)malloc(sizeof(Cvor)); //nije isti kao ovaj novi
    novi->podatak=*(niz+i);
    novi->levi=NULL;
    novi->desni=NULL;
    Cvor* stablo=koren;
    while(1){ //beskonacni ciklus
      if(novi->podatak < stablo->podatak){
        if(stablo->levi!=NULL){
          stablo=stablo->levi;
        }else{
          stablo->levi=novi;
          break; //ovo je izlaz iz ciklus
        }
      }else{
        if(stablo->desni!=NULL){
          stablo=stablo->desni;
        }else{
          stablo->desni=novi;
          break; //ovo je izlaz drugi iz ciklus
        }
      }
    }
  }
  return koren;
}

int suma_listova(Cvor* koren){
  if(koren->levi!=NULL){
    if(koren->desni!=NULL){
      return suma_listova(koren->desni)+suma_listova(koren->levi);
    }
    return suma_listova(koren->levi);
  }
  if(koren->desni!=NULL)return suma_listova(koren->desni);
  return koren->podatak;
}

void zamena(Cvor* koren){
  Cvor* pom=koren->levi;
  koren->levi=koren->desni;
  koren->desni=pom;
  if(koren->levi!=NULL)zamena(koren->levi);
  if(koren->desni!=NULL)zamena(koren->desni);
}

int main(){
  Cvor* stablo=NULL;
  int i, x, temp, e;
  int niz[]={50,30,20,40,70,60,80};
  int n=sizeof(niz)/sizeof(*(niz));
  stablo=inic(niz, n);
  stampajInOrder(stablo);
  printf("\n");
  listovi(stablo);

  Cvor* trazi=nadji(stablo,40);
  if(trazi==NULL)printf("\n40 nije pronadjen.\n");
  else printf("\n40 je pronadjen.\n");

  trazi=nadjiR(stablo,15);
  if(trazi==NULL)printf("15 nije pronadjen.\n");
  else printf("15 je pronadjen.\n");
  return 0;
}
