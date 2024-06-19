#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct f1
{
    char ime[31];
    int krugovi;
    int starost;
    int duzina;
}F1;


int citaj(F1 *pom, int ponavljanje)
{
    printf("\nUnesite ime staze ili 0 za izlazak, broj krugova, starost staze i duzinu staze\n");
    //while (getchar()!='\n');
    if(ponavljanje)getchar();
    fgets(pom->ime, 30, stdin);
    pom->ime[strcspn(pom->ime, "\n")]='\0';
    if (strcmp(pom->ime, "0") == 0) return 0;
    else scanf("%i%i%i", &pom->krugovi, &pom->starost, &pom->duzina);
    return 1;
}

void pisi(F1 niz[], int n)
{
    int i;
    for (i=0;i<n;i++)
    printf("%s %i %i %i\n", niz[i].ime, niz[i].krugovi, niz[i].starost, niz[i].duzina);
}

//void sortAbecedno(F1 niz[], int n)
//{
//    int i,j;
//    F1 pom;
//    for (i=0;i<n-1;i++)
//        for (j=i+1;j<n;j++)
//        {
//            if ((niz[i].ime)[0]>(niz[j].ime)[0])
//            {
//                pom=niz[i];
//                niz[i]=niz[j];
//                niz[j]=pom;
//           }
//        }
//}

void sortAlp(F1 niz[], int n){
  int i,j;
  F1 pom;
  
  char prvi, drugi;
  int minlen;

  for(i=0;i<n-1;i++){
    for(j=i+1;j<n;j++){

      minlen=(strlen(niz[i].ime)<strlen(niz[j].ime))?strlen(niz[i].ime):strlen(niz[j].ime);
      for(int z=0;z<minlen;z++){
        prvi=(niz[i].ime[z]<91 && niz[i].ime[z]>64)?niz[i].ime[z] + 32:niz[i].ime[z];
        drugi=(niz[j].ime[z]<91 && niz[j].ime[z]>64)?niz[j].ime[z] + 32:niz[j].ime[z];

        if(prvi<123 && prvi>96 && drugi<123 &&drugi>96){
          if(prvi>drugi){
            pom=niz[i];
            niz[i]=niz[j];
            niz[j]=pom;
            break;
          }else if(prvi!=drugi){
            break;
          }
        }
      }
    }
  }
}

void sortStarost(F1 niz[], int n)
{
    int i,j;
    F1 pom;
    for (i=0;i<n-1;i++)
        for (j=i+1;j<n;j++)
        {
            if ((niz[i].starost)<(niz[j].starost))
            {
                pom=niz[i];
                niz[i]=niz[j];
                niz[j]=pom;
            }
        }
}

void sortKrugovi(F1 niz[], int n)
{
    int i,j;
    F1 pom;
    for (i=0;i<n-1;i++)
        for (j=i+1;j<n;j++)
        {
            if ((niz[i].krugovi)<(niz[j].krugovi))
            {
                pom=niz[i];
                niz[i]=niz[j];
                niz[j]=pom;
            }
        }
}

void sortDuzina(F1 niz[], int n)
{
    int i,j;
    F1 pom;
    for (i=0;i<n-1;i++)
        for (j=i+1;j<n;j++)
        {
            if ((niz[i].duzina)<(niz[j].duzina))
            {
                pom=niz[i];
                niz[i]=niz[j];
                niz[j]=pom;
            }
        }
}

void promenaKrugova(F1 niz[], int n)
{
    char staza[31];
    int i, izbor, vrednost;
    printf("Unesite enter da bi ste nastavili.");
    while (getchar()!='\n');
    printf("\nUnesite ime staze: ");
    fgets(staza, 30, stdin);
    staza[strcspn(staza, "\n")]='\0';
    int nalaziSe=0;
    for (i=0;i<n;i++)
    {
        if (strcmp(niz[i].ime, staza)==0 )
        {
            nalaziSe=1;
            printf("\nUnesite 1 za dodavanje,a 2 za oduzimanje broja krugova i broj krugova: ");
            scanf("%i%i", &izbor, &vrednost);
            switch(izbor)
            {
                case 1: niz[i].krugovi+=vrednost;
                        break;
                case 2: niz[i].krugovi-=vrednost;
                        break;
                default:printf("Pogresan unos");
                        break;
            }
        }
    }
    if (nalaziSe==0) printf("\nTa staza ne postoji.\n");
    pisi(niz,n);
}

int main()
{
    int n=0, x, provera=1;
    F1 k[30];
    while(provera){ 
        provera=citaj(&k[n], n);
        n++;
    }
    n--;
    FILE *dat=fopen("f1.txt", "w+");
    pisi(k,n);
    printf("\n");
    printf("SORTIRAJ PO :\n1)ABECEDNOM REDU\t2)BROJU KRUGOVA\n3)STAROSTI STAZE\t4)DUZINI STAZE\n");
    scanf("%i",&x);
    switch(x)
    {
        case 1: sortAlp(k,n);
                pisi(k,n);
                printf("\n");
                break;
        case 2: sortKrugovi(k,n);
                pisi(k,n);
                printf("\n");
                break;
        case 3: sortStarost(k,n);
                pisi(k,n);
                printf("\n");
                break;
        case 4: sortDuzina(k,n);
                pisi(k,n);
                printf("\n");
                break;
        default:
        {
            printf("Pogresan unos!");
            break;
        }
    }
    for (int i=0;i<n;i++)
        fprintf(dat, "%s %i %i %i\n", k[i].ime, k[i].krugovi, k[i].starost, k[i].duzina);
    promenaKrugova(k,n);
    sortStarost(k,n);
    printf("\nNajstarija staza je %s\n", k[n-1].ime);
    printf("\nNajmladja je %s\n", k[0].ime);
    fclose(dat);
    return 0;
}
