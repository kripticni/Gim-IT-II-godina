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

Element *dodajNaKraj(Element *glava, int x){
    Element *lista=glava;
    Element *novi=(Element*)malloc(sizeof(Element));
    novi->podatak=x;
    novi->sledeci=NULL;
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

int vratiSredinu(Element *spori){
	Element *brzi=spori;
	while(brzi->sledeci!=NULL){
	brzi=brzi->sledeci;
	if (brzi->sledeci == NULL)
    		return spori->podatak;
	else
        	brzi = brzi->sledeci;
	spori=spori->sledeci;
	}
	return spori->podatak;
}

Element* srednjiCvor(Element *spori){
        Element *brzi=spori;
        while(brzi->sledeci!=NULL){
        brzi=brzi->sledeci;
        if (brzi->sledeci == NULL)
                return spori;
        else
                brzi = brzi->sledeci;
        spori=spori->sledeci;
        }
        return spori;
}


Element *dodajNaX(Element *glava, int X, int x){
    Element *lista=glava;
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

Element *sporoObrniListu(Element *lista){
    Element *obrnuta=NULL;
    while(lista!=NULL){
        obrnuta = dodajNaPocetak(obrnuta, lista->podatak);
        lista=lista->sledeci;
    }
    return obrnuta;
}

Element *obrniListu(Element *tekuci){
	Element *prosli=NULL;
	Element *buduci=tekuci->sledeci;
	while(buduci!=NULL){
		tekuci->sledeci=prosli;
		prosli=tekuci;
		tekuci=buduci;
		buduci=buduci->sledeci;
	}
	tekuci->sledeci=prosli;
	return tekuci;
}



Element *obrisiE(Element *glava, int e){
    Element *brisi;
    Element *tekuci=glava;

    while(tekuci->podatak==e){
        brisi=tekuci;
        tekuci=tekuci->sledeci;
        free(brisi);
    }
    glava=tekuci;
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


Element *duplirajE(Element *glava, int e) {
    Element *tekuci = glava;

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

    return glava;
}

//================|
//PROVERE ZA LISTE|
//================|

int prPalindrom(Element *glava){
	Element *prva=glava;
	Element *druga=obrniListu(srednjiCvor(glava));
	//printf("\n");
	//stampaj(prva);
	//stampaj(druga);
	while(prva!=NULL){
	if(prva->podatak!=druga->podatak)return 0;
	prva=prva->sledeci;
	druga=druga->sledeci;
	}
	return 1;
}


int prIste(Element *lista1, Element *lista2){
    while(lista1!=NULL&&lista1->podatak==lista2->podatak){
            lista1=lista1->sledeci;
            lista2=lista2->sledeci;
    }
    return(lista1==NULL && lista2==NULL);
}

int prRastuci(Element *lista){
    while(lista->sledeci->podatak > lista->podatak){
        lista=lista->sledeci;
        if(lista->sledeci==NULL)return 1;
    }
    return 0;
}

//======================|
//OPERACIJE KRUZNE LISTE|
//======================|

void praviKruznu(Element *glava){
	Element *lista=glava;
	do{
	lista=lista->sledeci;
	}while(lista->sledeci!=NULL);
	lista->sledeci=glava;
}


void rasturiKruznu(Element *glava){
	Element *lista=glava;
	do{
	lista=lista->sledeci;
	}while(lista->sledeci!=glava);
	lista->sledeci=NULL;
}

void stampajKruznu(Element *glava){
	Element *lista=glava;
	do{
	printf("%i", lista->podatak);
	lista=lista->sledeci;
	}while(lista!=glava);
}

Element* dodajNaKrajKruzne(Element *glava, int x){
	Element *lista=glava;
	Element *novi=(Element*)malloc(sizeof(Element));
	novi->podatak=x;
	if(lista==NULL){
		return novi;
	}
	novi->sledeci=glava;
	do{
	lista=lista->sledeci;
	}while(lista->sledeci!=glava);
	lista->sledeci=novi;
	return glava;
}

Element* dodajNaPocetakKruzne(Element *glava, int x){
	Element *novi=(Element*)malloc(sizeof(Element));
	novi->podatak=x;
	if(glava==NULL){
		return novi;
	}
	novi->sledeci=glava;
	Element *lista=novi;
	do{
	lista=lista->sledeci;
	}while(lista->sledeci!=glava);
	lista->sledeci=novi;
	return novi;
}

//====================|
//PROVERE KRUZNA LISTA|
//====================|

int brParnihKruzna(Element *glava){
	Element *lista=glava;
	int pr=0;
	do{
	if(lista->podatak%2==0)pr++;
	lista=lista->sledeci;
	}while(lista!=glava);
	return pr;
}

int zbirKruzna(Element *glava){
	Element *lista=glava;
	int zbir=0;
	do{
	zbir += lista->podatak;
	lista=lista->sledeci;
	}while(lista!=glava);
	return zbir;
}

int proizvodKruzna(Element *glava){
	Element *lista=glava;
	int p=1;
	do{
	if(lista->podatak <100)p=p* lista->podatak;
	lista=lista->sledeci;
	}while(lista!=glava);
	return p;
}

float prosekKruzne(Element *glava){
	Element *lista=glava;
	int n=0, s=0;
	do{
	n++;
	s=s+lista->podatak;
	lista=lista->sledeci;
	}while(lista!=glava);
	return s*1.0 / n;
}

int minimumKruzna(Element *glava){
	Element *lista=glava;
	int min=lista->podatak;
	do{
	if(lista->podatak<min)min=lista->podatak;
	lista=lista->sledeci;
	}while(lista!=glava);
	return min;
}

int maksimumKruzna(Element *glava){
        Element *lista=glava;
        int max=lista->podatak;
        do{
        if(lista->podatak>max)max=lista->podatak;
        lista=lista->sledeci;
        }while(lista!=glava);
        return max;
}


//MAIN//

int main(){
	Element *lista=NULL;
	int i, x, e;
	for(i=0;i<5;i++){
		printf("Unesi X");
		scanf("%i", &x);
		lista=dodajNaPocetak(lista, x);
	}
	printf("\n");
        stampaj(lista);

	(prPalindrom(lista))?printf("Palindrom je"):printf("Nije palindrom");
	return 0;


}



