#include <stdio.h>
#include <stdlib.h>

typedef struct element{
	int podatak;
	struct element *sledeci;
}Element;

void insert(Element **pocetak, Element **kraj, int x){
	Element *novi=(Element*)malloc(sizeof(Element));
	if(novi==NULL){
		printf("Greska pri alokaciji.");
		exit(1);
	}
	novi->podatak=x;
	if((*pocetak)==NULL){
		(*pocetak)=novi;
		(*kraj)=novi;
		return;
	}
	novi->sledeci=(*pocetak);
	(*pocetak)=novi;
}	

void delete(Element **pocetak, Element **kraj, int *x){
	if((*kraj)==NULL){
		printf("Red je prazan");
		return;
	}
	*x=(*kraj)->podatak;
	Element* fifo=(*pocetak);
	if((*pocetak)==(*kraj)){
		free(fifo);
		(*pocetak)=NULL;
		(*kraj)=NULL;
		return;
	}
	while(fifo->sledeci!=(*kraj)){
		fifo=fifo->sledeci;
	}
	(*kraj)=fifo;
	fifo=fifo->sledeci;
	(*kraj)->sledeci=NULL;
	free(fifo);
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
	for(i=0;i<5;i++){
		delete(&pocetak, &kraj, &x);
		printf("%i", x);
	}
	return 0;
}
