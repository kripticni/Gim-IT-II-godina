#include <stdio.h>
#include <stdlib.h>

typedef struct element{
	int podatak;
	struct element *sledeci;
}Element;

void push(Element **vrh, int x){
	Element *novi=(Element*)malloc(sizeof(Element));
	novi->podatak=x;
	novi->sledeci=(*vrh);
	(*vrh)=novi;
}

void pop(Element **vrh, int *x){
	Element *novi=(*vrh);
	(*vrh)=(*vrh)->sledeci;
	*x=(novi)->podatak;
	free(novi);
}

void stampaj(Element* vrh){
	while(vrh!=NULL){
		printf("%i", vrh->podatak);
		vrh=vrh->sledeci;
	}
}

int main(){
	Element *stack=NULL;
	int i, x;
	for(i=0;i<5;i++){
		printf("Dodaj X na stack: ");
		scanf("%i", &x);
		push(&stack, x);
	}
	printf("_____________________\n");
	stampaj(stack);
	printf("\n_____________________\n");
	pop(&stack, &x);
	printf("%i", x);
	return 0;
}
