#include <stdio.h>
#include <stdlib.h>

typedef struct Element{
    int podatak;
    struct Element *sledeci;
}Element;

void stampaj(Element *vrh){
    while(vrh!=NULL){
        printf("%i", vrh->podatak);
        vrh=vrh->sledeci;
    }
}

Element* push(Element* vrh,int x){
  Element *novi=(Element*)malloc(sizeof(Element));
  if(novi==NULL){
    printf("Greska.");
    exit(1);
  }
  novi->podatak=x;
  novi->sledeci=vrh;
  vrh=novi;
  return vrh;
}


void pop(Element **vrh,int *x){
    Element* novi=*vrh;
    *x=(*vrh)->podatak;
    (*vrh)=(*vrh)->sledeci;
    free(novi);
}

Element* popPovratni(Element* vrh, int *x){
    Element* novi=vrh;
    *x=vrh->podatak;
    vrh=vrh->sledeci;
    free(novi);
    return vrh;
  }

int max(Element *vrh){
    int max=vrh->podatak;
    while(vrh!=NULL)
    {
        if(vrh->podatak > max){
            max=vrh->podatak;
        }
    vrh=vrh->sledeci;
    }
    return max;
}

int main()
{
    Element *vrh=NULL;
    int n, x;
    printf("Unesite koliko elemenata zelite: ");
    scanf("%i",&n);
    for(int i=0;i<n;i++){
        printf("Unesite podatak za cvor: ");
        scanf("%i", &x);
        vrh=push(vrh, x);
    }

    int max1=max(vrh);
    int a;
    printf("\nMaximum na stackuje %d\n", max1);
    while(vrh->podatak!=max1){
        vrh=popPovratni(vrh, &a);
        printf("%i\t",a);
    }
    return 0;
}
