#include <stdio.h>
#include <stdlib.h>
typedef struct delement
{
    int podatak;
    struct delement *levi,*desni;
}Delement;

Delement *dodajNaKrajDvostruke(Delement *glava, Delement **kraj, int n){
	Delement *novi=(Delement*)malloc(sizeof(Delement));
	if(novi==NULL){
		printf("Greska.");
		exit(1);
	}
	novi->podatak=n;
	novi->desni=NULL;
	if(glava==NULL){
		novi->levi=NULL;
		(*kraj)=novi;
		return novi;
	}
	novi->levi=*kraj;
	(*kraj)->desni=novi;
	(*kraj)=novi;
	return glava;
}

Delement *dodajNaPocetakDvostruke(Delement *glava, int n){
	Delement *novi=(Delement*)malloc(sizeof(Delement));
	if(novi==NULL){
		printf("Greska.");
		exit(1);
	}
	novi->podatak=n;
	novi->levi=NULL;
	if(glava==NULL){
		novi->desni=NULL;
		return novi;
	}
	novi->desni=glava;
	glava->levi=novi;
	return novi;
}



Delement *dodajnapocetak(Delement *p,Delement **q,int n)//dodaj na kraj(pogresan naziv)
{
    Delement *pom=(Delement*)malloc(sizeof(Delement));
    if(pom==NULL)
    {
        printf("Greska");
        exit(0);
    }
    if(p==NULL)
    {
        pom->podatak=n;
        pom->levi=NULL;
        pom->desni=NULL;
        p=pom;
        *q=pom;
    }
    else

    {
        pom->podatak=n;
        pom->levi=*q;
        pom->desni=NULL;
        (*q)->desni=pom;
        *q=pom;
    }
    return p;
}
void stampajdesno(Delement *p)
{
    while(p!=NULL)
    {
        printf("%i\t",p->podatak);
        p=p->desni;}

}
void stampajdlevo(Delement *p)
{
    while(p!=NULL)
    {
        printf("%i\t",p->podatak);
        p=p->levi;}

}
int brelm(Delement *p)
{
    int b=0;
    while(p!=NULL)
    {
        b++;
        p=p->desni;
    }
    return b;
}

void SortirajD(Delement *pocetak)
{
    Delement *pi,*pj;
    int i,j,n,pom;
    n=brelm(pocetak);
    pi=pocetak;
    for(i=0;i<n-1;i++)
    {
        pj=pi->desni;
        for(j=i+1;j<n;j++)
        {
            if(pi->podatak>pj->podatak)
            {
                pom=pi->podatak;
                pi->podatak=pj->podatak;
                pj->podatak=pom;
            }
            pj=pj->desni;
        }
        pi=pi->desni;
    }
}

//i=0;i<n-1;i++
//j=0;j<n-i-1;j++
//if a[j] < a[min] then min = j
//swap i, min
Delement* SelectionSort(Delement *glava){
    Delement *i=glava;
    Delement *j;
    Delement *min;
    int pom;
    while(i!=NULL){
        min=i;
        j=i->desni;
        while(j!=NULL){
            if(j->podatak < min->podatak)min=j; // < za rastuci, > za opadajuci
            j=j->desni;
        }
        pom=min->podatak;
        min->podatak=i->podatak;
        i->podatak=pom;
        i=i->desni;
    }
    return glava;
}

Delement *obrisiIndex(Delement *glava, Delement **kraj, int x){
	Delement* lista=glava;
	x--;
	if(x<=0){
		glava=glava->desni;
		glava->levi=NULL;
		free(lista);
		return glava;
	}
	lista=lista->desni;
	x--;
	while(x!=0){
		if(lista->desni==NULL){
			printf("Pogresan unos, X ne moze biti veci od velicine liste, nijedan element nije izbrisan");
			return glava;
		}
		x--;
		lista=lista->desni;	
	}
	if(lista==(*kraj)){
		(*kraj)=(*kraj)->levi;
		(*kraj)->desni=NULL;
		free(lista);
		return glava;
	}
	lista->levi->desni=lista->desni;
	lista->desni->levi=lista->levi;
	free(lista);
	return glava;
}

int main()
{
    int i,m,x;
    Delement *pocetak,*kraj;
    printf("\nUnesi broj elemenata liste: ");
    scanf("%d",&m);
    pocetak=NULL;
    kraj=NULL;
    for(i=0;i<m;i++)
    {
        printf("\nUnesite x: ");
        scanf("%i",&x);
        pocetak=dodajnapocetak(pocetak,&kraj,x);
    }
    printf("\n_________________________________\n\n");
    stampajdesno(pocetak);
    printf("\n_________________________________\n\n");
    printf("Izaberi element za brisanje: ");
    scanf("%i",&x);
    pocetak=obrisiIndex(pocetak,&kraj,x);
    stampajdesno(pocetak);	
    return 0;
}
