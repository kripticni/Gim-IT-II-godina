#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct f1{
  char ime[31];
  int krugovi;
  int starost;
  int duzina;
}F1;

void sortAlp(F1 niz[], int n){
  int i,j;
  F1 pom;
  
  int minlen;
  char prvi, drugi;
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
