#include <stdio.h>
#include <stdlib.h>
typedef struct delement
{
    int podatak;
    struct delement *levi,*desni;
}Delement;
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
    stampajdlevo(kraj);
    SortirajD(pocetak);
    printf("\n_________________________________\n\n");
    stampajdesno(pocetak);
    printf("\nDuzina liste je %d",brelm(pocetak));
    return 0;
}
