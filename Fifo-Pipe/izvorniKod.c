#include <stdio.h>
#include <stdlib.h>

typedef struct element{
	int podatak;
	struct element *sledeci;
}Element;

void func(int* y){ //int* y=&x;
  *y=*y+1;
}
//int x;
//func(&x);

void insert(Element **pocetak, Element **kraj, int x){
	Element* novi=(Element*)malloc(sizeof(Element));
	if(novi==NULL){
		printf("Greska pri alokaciji");
		exit(1);
	}
	novi->podatak=x;
	novi->sledeci=NULL;
	if((*pocetak)==NULL){
		(*pocetak)=novi;
		(*kraj)=novi; //zato sto smo koristili dva pokazivaca, vratili smo i pocetak i kraj u glavni program (iako je void funkcija)
		return;
	}
	(*kraj)->sledeci=novi;
	(*kraj)=novi;
}	


void delete(Element **pocetak, Element **kraj, int *x){
	Element* novi=(*pocetak);
	if((*pocetak)==NULL){
		printf("Fifo je prazan.");
		exit(1);
	}	
	*x=(*pocetak)->podatak;
	(*pocetak)=(*pocetak)->sledeci;
	if((*kraj)==novi) (*kraj)=(*kraj)->sledeci;
	free(novi); //malo hacky resenje
}

void stampaj(Element *lista){
	while(lista!=NULL){
		printf("%i\t", lista->podatak);	
		lista=lista->sledeci;
	}
}

Element* napraviNovu(Element* lista){ //ovo pravi novu listu koja na pocetku ima negativne elemente a na kraju pozitivne
  Element* novi=(Element*)malloc(sizeof(Element));
  novi->podatak=lista->podatak;
  Element* pocetak=novi;
  Element* kraj=novi; 
  lista=lista->sledeci;
  while(lista!=NULL){ //ponavalja se dok je lista razlicito od null, da bi napravio novu listu
    novi=(Element*)malloc(sizeof(Element));
    novi->podatak=lista->podatak;
    if(lista->podatak>-1){ //da li je pozitivan broj
      novi->sledeci=pocetak; //ako je pozitivan
      pocetak=novi;
    }else{
      kraj->sledeci=novi; //ako je negativan
      kraj=novi;
    }
    lista=lista->sledeci;
  }
  kraj->sledeci=NULL;
  return pocetak; //vraca pokazivac na novu listu
} 

int main(){
	Element *pocetak=NULL;
	Element *kraj=NULL;
	int i, x;
	for(i=0;i<5;i++){
		printf("Unesi element");
		scanf("%i", &x);
		insert(&pocetak, &kraj, x);
	}
	stampaj(pocetak);
	printf("\nIspisivanje...\n");
  
  Element *lista=napraviNovu(pocetak);
  stampaj(lista);
	return 0;
}
