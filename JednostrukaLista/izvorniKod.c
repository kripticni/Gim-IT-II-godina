#include <stdio.h>
#include <stdlib.h>

//STRUKTURA
typedef struct element{
	int podatak;
	struct element *sledeci;
}Element;

//==================|
//KLASICNE OPERACIJE|
//==================|

void obrisiListu(Element *lista){
    Element *brisac = lista;
    while(lista!=NULL){
        lista=lista->sledeci;
        free(brisac);
        brisac=lista;
    }
    return;
}


void stampaj(Element *lista){
	while(lista!=NULL){
		printf("%i", lista->podatak);
		lista=lista->sledeci;
	}
	return;
}

Element *dodajNaKraj(Element *lista, int x){
    Element *glava=lista;
    Element *novi=(Element*)malloc(sizeof(Element));
    novi->podatak=x;
    if(lista==NULL)return novi;
    while(lista->sledeci!=NULL){
        lista=lista->sledeci;
    }
    lista->sledeci=novi;
    return glava;
}

Element *dodajNaPocetak(Element *lista, int x){
	Element *novi=(Element*)malloc(sizeof(Element));
	novi -> sledeci = lista;
	novi -> podatak = x;
	lista=novi;
	return lista;
}

//==================|
//NAPREDNE OPERACIJE|
//==================|

Element *dodajNaX(Element *lista, int X, int x){
    Element *glava=lista;
    X--;
    Element *novi = (Element*)malloc(sizeof(Element));
    novi -> podatak = x;
    while(X>0&&lista->sledeci!=NULL){
        lista = lista -> sledeci;
        X--;
    }
    novi->sledeci=lista->sledeci;
    lista->sledeci=novi;
    return glava;
}

Element *obrniListu(Element *lista){
    Element *obrnuta=NULL;
    while(lista!=NULL){
        obrnuta = dodajNaPocetak(obrnuta, lista->podatak);
        lista=lista->sledeci;
    }
    return obrnuta;
}



Element *obrisiE(Element *lista, int e){
    Element *brisi;
    Element *tekuci=lista;

    while(tekuci->podatak==e){
        brisi=tekuci;
        tekuci=tekuci->sledeci;
        free(brisi);
    }

    Element *glava=tekuci;
    Element *cekaj=tekuci;
    while(tekuci!=NULL){

        if(tekuci->podatak==e){
            while(tekuci->podatak==e){
                if(tekuci->sledeci==NULL){
                    cekaj->sledeci=NULL;
                    free(tekuci);
                    return glava;
                }
                brisi=tekuci;
                tekuci=tekuci->sledeci;
                free(brisi);
            }
            cekaj->sledeci=tekuci;
            cekaj=tekuci;
        }else{
            cekaj=tekuci;
        }
        tekuci=tekuci->sledeci;
    }
    return glava;
}


Element *duplirajE(Element *lista, int e) {
    Element *tekuci = lista;

    while (tekuci != NULL) {
        if (tekuci->podatak == e) {
	    Element *novi = (Element *)malloc(sizeof(Element));
            novi->podatak = e;
            novi->sledeci = tekuci->sledeci;
            tekuci->sledeci = novi;
            tekuci = novi->sledeci;
        } else {
            tekuci = tekuci->sledeci;
        }
    }

    return lista;
}

//================|
//PROVERE ZA LISTE|
//================|

int prIste(Element *lista1, Element *lista2){
    while(lista1!=NULL&&lista1->podatak==lista2->podatak){
            lista1=lista1->sledeci;
            lista2=lista2->sledeci;
    }
    if(lista1==NULL&&lista2==NULL){
        return 1;
    }
    return 0;
}

int prRastuci(Element *lista){
    while(lista->sledeci->podatak > lista->podatak){
        lista=lista->sledeci;
        if(lista->sledeci==NULL)return 1;
    }
    return 0;
}



//MAIN//

int main(){
	Element *lista;
	int i, x, e;
	for(i=0;i<5;i++){
		printf("Unesi X");
		scanf("%i", &x);
		lista=dodajNaKraj(lista, x);

	}
	stampaj(lista);
	lista=obrniListu(lista);
    stampaj(lista);
	return 0;


}



