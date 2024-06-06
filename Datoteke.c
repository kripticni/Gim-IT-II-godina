
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int sifra;
    char ime[31];
    int broj;
}Teniser;

void citaj(Teniser *pok){
    printf("\nUnesite sifru za Tenisera ili 0 za kraj unosa, ime i broj bodova\n");
    scanf("%d", &pok->sifra);
    while (getchar()!='\n');
    if (pok->sifra!=0)
    {gets(pok->ime);
        scanf("%d", &pok->broj);
    }
}

void pisi(Teniser x[], int n){
    int i;
    for (i=0;i<n;i++) printf("%d\t%s\t%d\n", x[i].sifra, x[i].ime, x[i].broj);
}

void sortiraj (Teniser x[], int n){
    int i, j;
    Teniser pom;
    for (i=0;i<n-1;i++)
    for (j=0;j<n-i-1;j++)
    if (x[j-1].broj < x[j].broj){
        pom=x[j-1];
        x[j-1]=x[j];
        x[j]=pom;
    }
}

int main(){
    FILE *dat;
    Teniser t, a[30];
    dat=fopen("Teniseri.txt","w+");
    int i=0, n;
    citaj(&t);
    while (t.sifra!=0){
        fprintf(dat, "%d\t%s\t%d\n", t.sifra, t.ime, t.broj);
        i++;
        //printf("\n Unesite za sledeceg\n");
        citaj(&t);
    }
    n=i;
    i=0;
    fseek(dat, 0, SEEK_SET);
    fscanf(dat, "%d\t%s\t%d", &a[i].sifra, a[i].ime, &a[i].broj);
    while (!feof(dat)){
        i++;
        fscanf(dat, "%d\t%s\t%d", &a[i].sifra, a[i].ime, &a[i].broj);
    }
    sortiraj(a,n);
    printf("\nSpisak Tenisera iz datoteke Teniseri.txt koji je uredjen u rastuci red je: \n");
    pisi(a,n);
    printf("\nMax poena = %d\n", a[0].broj);
    printf("\nMin poena = %d\n", a[n-1].broj);
    printf("\nRazlika max i min broja poena je = %d\n", a[0].broj-a[n-1].broj);
    fclose(dat);
    return 0;
}
