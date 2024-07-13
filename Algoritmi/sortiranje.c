#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

void zamena(int* i,int* j){
  int pom=*i;
  *i=*j;
  *j=pom;
}

void SelectionSort(int arr[],int n){
  for(register int i = 0; i < n; i++){
    for(register int j = i + 1; j < (n - 1); j++){
      if(arr[i]<arr[j]){
        zamena(&arr[i], &arr[j]);
      }
    }
  }
}

void BubbleSort(int arr[],int n){
  for(register int i=0;i<n-1; i++){
    for(register int j=0;j<n-i-1;j++){
      if(arr[j]>arr[j+1]){
        zamena(&arr[j],&arr[j+1]);
      }
    }
  }
}

void Merge (int arr[], int donja1, int gornja1, int donja2, int gornja2){
  register int p,q,i,j;
  int pom[100];

  p = donja1;
  q = donja2;
  i = 0; 

  //Dodajemo veci od 2 niza, a ta dva su dobijena preko deljenja niza na pola
  while((p<=gornja1)&&(q<=gornja2)){
    pom[i++]=((arr[p] < arr[q])?arr[p++]:arr[q++]);
  }
  
  //ostatak 1. niza
  while(p<=gornja1){
    pom[i++]=arr[p++];
  }
  
  //ostatak 2. niza
  while(q<=gornja2){
    pom[i++]=arr[q++];
  } 

  //restartujemo brojac za pom, i vracamo nazad u originalan niz
  i=0;
  for(p=donja1;p<=gornja1;p++,i++){
    arr[p]=pom[i]; 
  }
  
  for (q = donja2,j = i; q <= gornja2; q++, j++){
    arr[q] = pom[j];
  }
}

void MergeSort(int arr[], int donja, int gornja){
  if (gornja > donja){
    int sredina = (donja + gornja) / 2; 
    MergeSort(arr, donja, sredina); 
    MergeSort(arr, sredina + 1, gornja); 
  Merge(arr, donja, sredina, sredina + 1, gornja);
  }
}

int Partition(int arr[], int donja, int gornja){
  int pivot=arr[gornja];  
  register int i=(donja-1);
  for (register int j=donja;j<=(gornja-1);j++) {
    if (arr[j] <= pivot){
      i++;
      zamena(&arr[i], &arr[j]);
    }
  }
  zamena(&arr[i+1],&arr[gornja]);
  return (i+1);
}

void QuickSort(int arr[], int donja, int gornja){
  if (gornja > donja){
    int pivot = Partition(arr, donja, gornja);
    QuickSort(arr, donja, pivot - 1);
    QuickSort(arr, pivot + 1, gornja);
  }
}

int main(){
  unsigned int n;

  printf("Unesite velicinu niza: ");
  scanf("%u", &n);

  int arr[n];
  {  
  for(auto int i=0;i<n;i++){
      printf("Unesite niz[%i]", i);
      scanf("%i",&arr[i]);
  }
  }

  printf("Izaberite metodu za sortiranje, \n1. Selection\t2.Bubble\n3.Merge\t4.Quick\nUnos: ");
  uint8_t odluka;
neuspesno:
  scanf("%c", &odluka);
  if(odluka>4 || odluka==0){
    printf("Unesite broj od 1 od 4.");
    goto neuspesno;
  }

  switch(odluka){
    case 1:
      SelectionSort(arr, n);
      break;
    case 2:
      BubbleSort(arr, n);
      break;
    case 3:
      MergeSort(arr, 0, n);
      break;
    case 4:
      QuickSort(arr, 0, n);
      break;
  }

  printf("\n");
  for(;n>0;n--){
    printf("%i", arr[n]);
  }
  return 0;
}
