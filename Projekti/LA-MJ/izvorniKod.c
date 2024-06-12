#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct stablo{
  struct stablo* levi;
  struct stablo* desni;
  union{
    struct{
      int freq;
      int ponavljanja;
    }podaci;
  };
}Stablo;

typedef struct pipe{
  uint8_t podatak;
  struct pipe* sledeci;
}Pipe;

typedef struct stack{
  struct stablo* sacuvan;
  struct stack* sledeci;
  int pozicija;
  char str[128];
}Stack;

typedef struct list{
  char str[128];
  int ponavljanja;
  struct list* sledeci;
}List;

Stack* make(Stablo* cvor){
  Stack* vrh=(Stack*)malloc(sizeof(Stack));
  vrh->sacuvan=cvor;
  vrh->str[0] = '\0';
  vrh->str[0] |= 1;
  vrh->pozicija=1;
  vrh->sledeci=NULL;
  return vrh;
}

Stack* push(Stack* vrh, Stablo* cvor, char niz[128], int pozicija){
  Stack* novi=(Stack*)malloc(sizeof(Stack));
  novi->sacuvan=cvor;
  memcpy(novi->str, niz, pozicija/7);
  novi->str[pozicija/7]=novi->str[pozicija / 7] |= (1 << (6 - (pozicija % 7)));
  vrh->pozicija=pozicija;
  novi->sledeci=vrh;
  return novi;
}

void pop(Stack** vrh, Stablo** stablo, char niz[128], int* pozicija){
  (*stablo)=(*vrh)->sacuvan;
  memcpy(niz, (*vrh)->str, (*vrh)->pozicija /7);
  *pozicija=(*vrh)->pozicija;
  Stack* brisi=(*vrh);
  (*vrh)=(*vrh)->sledeci;
  free(brisi);
}

void genStablo(Stablo** koren, char *str, int n){
  (*koren)=(Stablo*)calloc(1, sizeof(Stablo));
  for(int i=0;i<n;++i){//sa ovim prolazimo kroz string
    Stablo* stablo=(*koren);
    for(int j=0;j<7;++j){//posto ascii kod koristi 128 stanja, mozemo da zabelezimo to kroz 8 bitova
      if(str[i] & (1 << j)){
        if(stablo->desni==NULL){
          stablo->desni=(Stablo*)calloc(1, sizeof(Stablo));
          stablo=stablo->desni;    
        }
      }else{
        if(stablo->levi==NULL)
          stablo->levi=(Stablo*)calloc(1, sizeof(Stablo));
        stablo=stablo->levi;
      }
    }
    stablo->podaci.freq++;
    if(str[i+1]==' '){
      stablo->podaci.ponavljanja++;
      while(str[i+1]==' ')++i;
    }
  }
}

void readStablo(List** lista, Stablo* stablo){
  int pozicija;
  char str[128];
  (*lista)=(List*)calloc(1, sizeof(List));
  Stack* stack=make(stablo->desni);
  while(1){
    for(pozicija=0;(pozicija%7)<6;++pozicija){//moguca greska u uslovu
      if(stablo->levi!=NULL){
        if(stablo->desni!=NULL)stack=push(stack, stablo->desni, str, pozicija);
        str[pozicija / 7] &= ~(1 << (6 - (pozicija % 7)));
        stablo=stablo->levi;
      }else{
        str[pozicija / 7] |= (1 << (6 - (pozicija % 7)));
        stablo=stablo->desni; //ako je levo NULL onda sigurno desno nije jer imamo barem po 7 bitova
      }
    }
    if(stablo->podaci.ponavljanja){
      List* novi=(List*)malloc(sizeof(List));
      memcpy(novi->str, str, pozicija/7);
      novi->str[(pozicija/7) +1]='\0';
      novi->ponavljanja=stablo->podaci.ponavljanja;
      novi->sledeci=(*lista)->sledeci;
      (*lista)->sledeci=novi;
    }
    if(stablo->levi!=NULL){
      if(stablo->desni!=NULL)stack=push(stack, stablo->desni, str, pozicija);
      str[pozicija / 7] &= ~(1 << (6 - (pozicija % 7)));
      stablo=stablo->levi;
    }else{
      if(stablo->desni==NULL){
        if(stack==NULL) return; //izlaz iz "rekurzije"
        pop(&stack, &stablo, str, &pozicija); //dok ima u stacku uzimamo sa stacka
      }else{
        str[pozicija / 7] |= (1 << (6 - (pozicija % 7)));
        stablo=stablo->desni;
      }
    }
  }
}


void SelectionSortAndSize(List* lista, int* n){
  List* i=lista;

  while(i!=NULL){
    List* j=i->sledeci;
    List* min=i;
    while(j!=NULL){
      if(j->ponavljanja>min->ponavljanja){
        min=j;
      }
      j=j->sledeci;
    }
    char str[32];
    strcpy(str, min->str);
    strcpy(min->str, i->str);
    strcpy(i->str, str);
    int pom=min->ponavljanja;
    min->ponavljanja=i->ponavljanja;
    i->ponavljanja=pom;
    i=i->sledeci;
    *n=*n + 1;
  }
}


void stampaj(List* lista){
  while(lista!=NULL){
    printf("%s:%i\n", lista->str, lista->ponavljanja);
    lista=lista->sledeci;
  }
}


void kmp(char* str, int m, int* niz){
  int j=0;
  int i=1;
  niz[0]=0;
  while(i<m){
    if(str[i]==str[j]){
      niz[i]=j+1;
      i++;
      j++;
    }else{
      if(j!=0)j=niz[j-1];
      else{
        niz[i]=0;
        i++;
      }
    }
  }
}

int main(){
  FILE* dat;

  char odluka[128];
  printf("Unesite put do datoteke, ili stdin za unos iz programa: ");
  fgets(odluka, 127, stdin);
  odluka[strcspn(odluka,"\n")]='\0';

  char ch;
  char* input=NULL;
  int maxlen=64;
  int len=0;

  if(strcmp(odluka, "stdin")==0){ 
    while((ch = getchar()) != EOF){
        if(len >= maxlen){
            maxlen += 8; 
            char* temp=realloc(input, maxlen);
            if(temp==NULL){
                fprintf(stderr, "Greska pri alokaciji!\n");
                free(input);
                return 1;
            }
            input=temp;
        }
        input[len++]=(char)ch;
    }
  }else{
    dat=fopen(odluka, "r");
    if(!dat){
      fprintf(stderr, "Greska pri otvaranju %s\n", odluka);
      exit(1);
    }
    while(fscanf(dat, "%c", &input[len])==1){ //ucitavanje iz datoteke dok ima karaktera
      len++;
    }
    fclose(dat);
  }
  input[len]='\0';

  Stablo* koren=NULL;
  List* lista=NULL;
  int listlen=0;

  genStablo(&koren, &input[0], len);
  SelectionSortAndSize(lista, &listlen);

  printf("Unikatne reci: %i\nREC:FREKVENCIJA\n", listlen);
  stampaj(lista);

  char str[1023];
  char replace[1022];

  while (getchar()!='\n');
  printf("\n\nUnesite rec koju zelite da zamenite: ");
  fgets(str, 1022, stdin);
  printf("Unesite rec sa kojom zelite da prethodnu zamenite: ");
  fgets(replace, 1021, stdin);

  str[strcspn(str, "\n")]='\0';
  replace[strcspn(replace, "\n")]='\0';
  int slen=strlen(str);
  int rlen=strlen(replace);

  int kmptable[slen];
  kmp(str, slen, kmptable);

  int j=0;
  int i=0;
  while(i<len){
    if(str[j]==input[i]){
      i++;
      j++;
    }else{
      if(j!=0) j=kmptable[j-1];
      else i++;
    }
    if(j==slen){
      if((input[i-j-1]!=' ' && i-j!=0) || (input[i]!=' ' && i!=len))goto skip;
      //printf("\nNadjen na %i\n", i-j);
      int start = i - j;
      int end = start + rlen;
      if (rlen > slen) {
        memmove(&input[start + rlen], &input[start + slen], len - start - slen + 1);
      } else if (rlen < slen) {
        memmove(&input[end], &input[start + slen], len - start - slen + 1);
      }

      strncpy(&input[start], replace, rlen);

      len = strlen(input);
    skip:
      j=kmptable[j-1];
    }
  }
  puts(input);

  if(strcmp(odluka,"stdin")==0){
    getchar();
    printf("Unesite ime datoteke: ");
    fgets(odluka, 127, stdin);
    odluka[strcspn(odluka, "\n")] = '\0';
  }
  dat=fopen(odluka,"w");
  if (!dat) {
      fprintf(stderr, "Greska pri otvaranju %s\n", odluka);
      exit(1);
  }
  fprintf(dat, "%s", input);
  fclose(dat);
  return 0;
  }
