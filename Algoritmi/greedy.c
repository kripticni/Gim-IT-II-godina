#include <stdlib.h>
#include <stdio.h>

int main(){
  int n, uzeto, nosivost, vrednost=0, i=0, j=0;
  printf("Unesi broj proizvoda i nosivost: \n");
  scanf("%i%i", &n, &nosivost);

  int kolicina[n], cena[n], jedinicna_cena[n];
  for(;i<n;i++){
    printf("Unesi kolicinu pa cenu za %i prozivod: \n", i);
    scanf("%i%i", &kolicina[i], &cena[i]);
    jedinicna_cena[i] = cena[i] / kolicina[i];
  }

  for(i=n-2;i>0;i--){
    for(;j<=i;j++){
      if(jedinicna_cena[j]<jedinicna_cena[j+1]){
        int pom=jedinicna_cena[j];
        jedinicna_cena[j]=jedinicna_cena[j+1];
        jedinicna_cena[j+1]=pom;
        pom=kolicina[j];
        kolicina[j]=kolicina[j+1];
        kolicina[j+1]=pom;
        pom=cena[j];
        cena[j]=cena[j+1];
        cena[j+1]=pom;
      }
    }
  }

  for(i=0;i<n;i++){
    if(nosivost>kolicina[i]){
      uzeto = kolicina[i];
    }else{
      uzeto = nosivost;
    } //else se samo desava jednom i to na zadnjem ponavljanju
    //aritmetika ispod sluzi da izracuna vrednost i da smanjuje nosivost
    //sve dok nosivost ne bude manja od kolicine sledeceg proizvoda

    vrednost = vrednost + uzeto*jedinicna_cena[i];
    if(nosivost == uzeto) break; //optimizovano za jedno oduzimanje, jako glupo ali svakako ima da stavim
    nosivost = nosivost - uzeto;
    //if(nosivost == 0) break; je standardno
  }

  printf("Vrednost koju ste uzeli je %i", vrednost);
}
