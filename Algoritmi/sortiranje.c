#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

void zamena(int* i,int* j){
  int pom=*i;
  *i=*j;
  *j=pom;
}

void SelectionSort(int arr[],int n){
  for(register int i = 0; i < n; i++){
    for(register int j = i + 1; j < n; j++){
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

void Merge(int arr[], int donja1, int gornja1, int donja2, int gornja2){
  register int p,q,i,j;
  int pom[gornja2-donja1];

  p = donja1;
  q = donja2;
  i = 0; 

  //Dodajemo veci od 2 niza, a ta dva su dobijena preko deljenja niza na pola
  while((p<=gornja1)&&(q<=gornja2)){
    pom[i++]=((arr[p] < arr[q])?arr[p++]:arr[q++]);
  }
  //TODO: ovo moze jos da se optimizuje sa ogromnu if else granu
  
  //ostatak 1. niza
  if(p<=gornja1){ 
    do{
      pom[i++]=arr[p++];
    }while(p<=gornja1);
    goto skip;
  }
  //ostatak 2. niza
  while(q<=gornja2){
    pom[i++]=arr[q++];
  } 

skip:

  //restartujemo brojac za pom, i vracamo nazad u originalan niz
  for(i=0, p=donja1; p<=gornja2; p++, i++){
    arr[p]=pom[i];
  }
}

void MergeSort(int arr[], int donja, int gornja){
  void Merge (int arr[], int donja1, int gornja1, int donja2, int gornja2);
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
  int Partition(int arr[], int donja, int gornja);
  if (gornja > donja){
    int pivot = Partition(arr, donja, gornja);
    QuickSort(arr, donja, pivot - 1);
    QuickSort(arr, pivot + 1, gornja);
  }
}

int DualPartition(int arr[], int donja, int gornja, int* right){
  if(arr[donja] > arr[gornja])
    zamena(&arr[donja], &arr[gornja]);

  int l=donja+1, r=gornja-1, i=donja+1;

  while(i<=r){
    if(arr[i] < arr[donja]){
      zamena(&arr[i], &arr[l]);
      l++;
    }else if(arr[i] > arr[gornja]){
      zamena(&arr[i], &arr[r]);
      r--;
      i--;
    }
    i++;
  }

  zamena(&arr[donja], &arr[--l]);
  zamena(&arr[gornja], &arr[++r]);
  *right=r;
  return l;
}

void DualPivotSort(int arr[], int donja, int gornja){
  int DualPartition(int arr[], int donja, int gornja, int* right);
  if (gornja > donja){
    int right;
    int left=DualPartition(arr, donja, gornja, &right);
    DualPivotSort(arr, donja, left-1);
    DualPivotSort(arr, left+1, right-1);
    DualPivotSort(arr, right+1, gornja);
  }
}

void Ternary(int arr[], int donja, int trecina1, int trecina2, int gornja, int pom[]) { 
  int x = donja, y = trecina1, z = trecina2, l = donja; 

  //TODO: ovo takodje moze da se optimizuje sa veliku if else granu
  while((x<trecina1)&&(y<trecina2)&&(z<gornja)){
    if(arr[x]<arr[y]){
      if(arr[x]<arr[z])
        pom[l++]=arr[x++];
      else
        pom[l++]=arr[z++];
    }
    else{
      if(arr[y]<arr[z])
        pom[l++]=arr[y++];
      else
        pom[l++]=arr[z++];
    }
  }

  while((x<trecina1)&&(y<trecina2)){
    if(arr[x]<arr[y])
      pom[l++]=arr[x++];
    else
      pom[l++]=arr[y++];
  }

  while((y<trecina2)&&(z<gornja)){
    if(arr[y]<arr[z])
      pom[l++]=arr[y++];
    else
      pom[l++]=arr[z++];
  }

  while((x<trecina1)&&(z<gornja)){
    if(arr[x]<arr[z])
      pom[l++]=arr[x++];
    else
      pom[l++]=arr[z++];
  }

  while(x<trecina1)
    pom[l++]=arr[x++];

  while(y<trecina2)
    pom[l++]=arr[y++];

  while(z<gornja)
    pom[l++]=arr[z++];
}
 

void TernarySortUnwrapped(int arr[], int donja, int gornja, int pom[]) { 
  void Ternary(int arr[], int donja, int trecina1, int trecina2, int gornja, int pom[]);
  if(gornja-donja<2) 
    return; 

  int trecina1=donja + ((gornja - donja)/3); 
  int trecina2=donja + 2*((gornja - donja)/3) + 1; 

  TernarySortUnwrapped(pom,donja,trecina1,arr); 
  TernarySortUnwrapped(pom,trecina1,trecina2,arr); 
  TernarySortUnwrapped(pom,trecina2,gornja,arr); 

  Ternary(pom,donja,trecina1,trecina2,gornja,arr); 
}

void TernarySort(int arr[], int n){ 
  void TernarySortUnwrapped(int arr[], int donja, int gornja, int pom[]);
  if(n==0)
    return; 

  int pom[n]; 

  int i=0;
  for(;i<n;i++) 
    pom[i]=arr[i]; 

  TernarySortUnwrapped(pom,0,n,arr); 

  for(i=0;i<n;i++) 
    arr[i]=pom[i]; 
}

void MergeME(int arr[], int donja1, int gornja1, int donja2, int gornja2, int pom[]){
  register int p,q,i,j;

  p = donja1;
  q = donja2;
  i = donja1; 

  //Dodajemo veci od 2 niza, a ta dva su dobijena preko deljenja niza na pola
  while((p<=gornja1)&&(q<=gornja2)){
    pom[i++]=((arr[p] < arr[q])?arr[p++]:arr[q++]);
  }
  //TODO: ovo moze jos da se optimizuje sa ogromnu if else granu
  
  //ostatak 1. niza
  if(p<=gornja1){ 
    do{
      pom[i++]=arr[p++];
    }while(p<=gornja1);
    return;
  }
  //ostatak 2. niza
  while(q<=gornja2){
    pom[i++]=arr[q++];
  } 

}

void MergeSortUnwrappedME(int arr[], int donja, int gornja, int pom[]){
  void Merge (int arr[], int donja1, int gornja1, int donja2, int gornja2);
  if (gornja > donja){
    int sredina = (donja + gornja) / 2; 
    MergeSortUnwrappedME(pom, donja, sredina, arr); 
    MergeSortUnwrappedME(pom, sredina + 1, gornja, arr); 
  MergeME(pom, donja, sredina, sredina + 1, gornja, arr);
  }
}

void MergeSortME(int arr[], int n){ 
  if(n==0)
    return; 

  int pom[n]; 

  int i=0;
  for(;i<n;i++) 
    pom[i]=arr[i]; 

  MergeSortUnwrappedME(pom,0,n-1,arr); 

  for(i=0;i<n;i++) 
    arr[i]=pom[i]; 
}

void MultiSortUnwrapped(int arr[],int donja,int gornja,int pom[]){
  void MergeME(int arr[], int donja1, int gornja1, int donja2, int gornja2, int pom[]);
  void Ternary(int arr[], int donja, int trecina1, int trecina2, int gornja, int pom[]);
  if(gornja-donja<2){ 
  //if(donja<gornja){
  //   int n=gornja-donja;
  //   MultiSortUnwrapped(pom, donja, n/2, arr);
  //   MultiSortUnwrapped(pom, n/2 +1, gornja, arr);
  //   MergeME(pom, donja, n/2, n/2 +1, gornja, arr);
  //}
    return;
  }
  
  if((gornja-donja) & 1){
    int n=(gornja-donja)/3;
    MultiSortUnwrapped(pom,donja,donja+n,arr); 
    MultiSortUnwrapped(pom,donja+n,donja+n*2+1,arr); 
    MultiSortUnwrapped(pom,donja+n*2+1,gornja,arr); 
    Ternary(pom,donja,donja+n,donja+n*2+1,gornja,arr);
  }else{
    int n=donja+(gornja-donja)/2;
    MultiSortUnwrapped(pom,donja,n,arr);
    MultiSortUnwrapped(pom,n+1,gornja,arr);
    MergeME(pom,donja,n,n+1, gornja,arr);
  }
}

void MultiSort(int arr[], int n){
  if(n==0)
    return;

  int pom[n];

  int i=0;
  for(;i<n;i++)
    pom[i]=arr[i];

  MultiSortUnwrapped(pom, 0, n, arr);

  for(i=0;i<n;i++)
    arr[i]=pom[i];
}

int main(){
  unsigned int n;

  printf("Unesite velicinu niza: ");
  scanf("%u", &n);

  int arr[n];
  {  
  auto int i=0;
  for(;i<n;i++){
      printf("Unesite niz[%i]: ", i);
      scanf("%i",&arr[i]);
  }
  printf("\nArray: ");
  for(--i;i!=-1;--i)printf("%i\t", arr[i]);
  }

  printf("\nIzaberite metodu za sortiranje, \n1. Selection\t2. Bubble\n3. Merge\t4. Quick\n5. Merge (Memory Efficent)\n6. Dual Pivot Quicksort\n7. Ternary Mergesort\n8. Hybrid Mergesort\nUnos: ");
  uint8_t odluka;
neuspesno:
  scanf("%hhu", &odluka);
  if(odluka>8 || odluka==0){
    printf("Unesite broj od 1 od 8.");
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
      MergeSort(arr, 0, n-1);
      break;
    case 4:
      QuickSort(arr, 0, n-1);
      break;
    case 5:
      MergeSortME(arr, n);
      break;
    case 6:
      DualPivotSort(arr, 0, n-1);
      break;
    case 7:
      TernarySort(arr, n);
      break;
    case 8:
      MultiSort(arr, n);
      break;
  }

  printf("\n");
  for(n--;n!=-1;n--){
    printf("%i", arr[n]);
  }
  return 0;
}
