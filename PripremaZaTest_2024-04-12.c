Predznanje:
-Iz (ovo je lokacija) JednostrukaLista/IzvorniKod.c, na test nece imamo sledece funkcije:
	-SelectionSort
	-vratiSredinu
	-srednjiCvor
	-dodajNaX (valjda ovo nema)
	-sporoObrniListu
	-ObrniListu
	-prPalindrom
	-rasturiKruznu

-Seg fault znaci segmentation fault odnosno program se terminise, ovo ne treba da se desi

-Svaka funkcija koja zahteva pomocnu promenjivu i definisana je Element*, koriste 
    "Element *glava" kao unos u funkciju, ovo je pocetak od listu,
     a nakon Element *lista=glava,
     pomera se samo "lista" i na kraj se vraca pocetak odnosno glava 

//===============
//OBAVEZNE OSNOVE
//===============
typedef struct element{
        int podatak;
        struct element *sledeci;
}Element;

^ Apsolutno mora da se zna

takodje u int main(){
	Element *lista=NULL; //uvek mora =NULL jer inace daje seg fault
	lista=dodajNaPocetak(lista, 1);
}
ovako se dodaje na listu, mora da bude lista=dodajNa.... jer ta funkcija vraca Element *



//=================
//POCETNE OPERACIJE
//=================

Od pocetak ima da stavljam funkcije i za jednostruku listu i za kruznu listu
razlika izmedju jednostruku i kruznu je to da

kraj od jednostruku pokazuje na NULL, pa se koristi while ciklus za lista!=NULL
kraj od kruznu pokazuje na POCETAK od kruznu, pa se koristi DO WHILE!!!!
					     do{
						//stvari idu ovde
						} while (lista!=glava); //obavezno ; na kraj
osim to, novi element se stvara sa

    Element *novi=(Element*)malloc(sizeof(Element));
    novi->podatak=x;
	(a novi->sledeci ce odredite na osnovu zadatak)


ovo nije isto kao promenjiva, nego je dodeljivanje memorijski prostor sa lokaciju
pa onda davanje tu lokaciju na pokazivac, zato se u neke funkcije moze koristi vise
puta isto ime "novi". (naprimer za duplirajE)


Ispod su jednostruke ||
		     \/

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

Elementi se brisu sa free, jer je svaki deo od listu dinamicki alociran
ovo je primer.

void obrisiListu(Element *lista){  //brise celu listu
    Element *brisac = lista;
    while(lista!=NULL){
        lista=lista->sledeci;
        free(brisac);
        brisac=lista;
    }
    return;
}



Okej, sad na osnove za kruznu listu.

void praviKruznu(Element *glava){
        Element *lista=glava;
        do{  
        lista=lista->sledeci;
        }while(lista->sledeci!=NULL);
        lista->sledeci=glava;  
}

Za ovu funkciju NE STAVLJATE lista=, jer void
i samo menja pokazivaci od vec postojecu listu


void stampajKruznu(Element *glava){
        Element *lista=glava;
        do{
        printf("%i", lista->podatak);
        lista=lista->sledeci;
        }while(lista!=glava);
}


Samo smo radili jednu od funkcije ...KrajKruzne i ...PocetakKruzne,
al ne secam se koju, svakako mislim da je najbolje da naucite obe
najverovatnije gu briga koju smo ucili od ove dve


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






//================================
//LAGANE FUNKCIJE/KLASICNE PROVERE
//================================

(i za jednostruke i za kruzne)
Ove funckije zahtevav 0 mozak da se razumev i ako ste znali da radite
sa nizovi, ce znate i ovo da uradite, necu nista ovde da objasnjavam



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

int brParnihKruzna(Element *glava){
        Element *lista=glava;
        int pr=0;
        do{
        if(lista->podatak%2==0)pr++;
        lista=lista->sledeci;
        }while(lista!=glava);
        return pr;
}

//=============
//PROVERE LISTE
//=============

Ove sledece dve funkcije su napisane najoptimizivanije moguce
ali mozete da ih uradite manje komplikovano ako vas boli briga
za memoriju i vreme, Biljanu gu briga za optimizaciju

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

Ali ovo je isto i mnogo krace (u duzinu od tekst) od bilokoji drugi nacin




//=====================
//DOSTA TEZA KATEGORIJA
//=====================

Ove dve funckije su brda zajebane, najv ce snimim video za ove dve
i ce posaljem na viber

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



//==========================
//FINALNA I NAJTEZA FUNKCIJA
//==========================

VERUJEM, da Biljana nece da ovo na test jer nije znala da ga uradi danas
medjutim... u slucaju da ga da ovo je ispravna funckija koja radi za svaki
slucaj, za ovu ce obavezno snimim video i posaljem na viber


Element* dodajNaSortiranu(Element *glava, int x){
        Element *novi=(Element*)malloc(sizeof(Element));
        novi->podatak=x;

        if(glava==NULL){
                novi->sledeci=NULL;
                return novi;
        }

        if(glava->podatak >= x){
                novi->sledeci=glava;
                return novi;
        }else if(glava->sledeci==NULL){ //iskljucivo za slucaj kad se unese x pa broj veci od x
            glava->sledeci=novi;        //jer bi lista->sledeci->sledeci dalo segmentation fault
            novi->sledeci=NULL;         //najverovatnije nece da trazi na test
            return glava;
        }

        Element *lista=glava;
        while(lista->sledeci->podatak <= x && lista->sledeci->sledeci != NULL){
                lista=lista->sledeci;
        }

        if(lista->sledeci->sledeci==NULL && lista->sledeci->podatak < x){
                lista=lista->sledeci;
                novi->sledeci=NULL;
                lista->sledeci=novi;
                return glava;
        } //u ovaj slucaj mora da ga umetne posle kraj

        novi->sledeci=lista->sledeci;
        lista->sledeci=novi;
        return glava; //a u ovaj izmedju kraj
}

