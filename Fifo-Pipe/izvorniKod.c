#include <stdio.h>
#include <stdlib.h>

typedef struct element{
	int podatak;
	struct element *sledeci;
}Element;

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
		(*kraj)=novi;
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
	free(novi);

}

void stampaj(Element *pocetak){
	while(pocetak!=NULL){
		printf("%i\t", pocetak->podatak);	
		pocetak=pocetak->sledeci;
	}
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
	for(i=0;i<6;i++){
		delete(&pocetak, &kraj, &x);
		printf("%i", x);
	}
	return 0;
}
