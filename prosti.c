#include <stdio.h>
#include <Stdio.h>
#include <math.h>

int prost1(int n){
    int i=2;
    while(i<=n-1){
        if(n%i==0) return 0;
        i++;
    }
    return 1;
}

int prost2(int n){
    int i=2;
    while(i<=n/2){
        if(n%i==0) return 0;
        i++;
    }
    return 1;
}

int prost3(int n){
    int i=2;
    while(i<=sqrt(n)){
        if(n%i==0) return 0;
        i++;
    }
    return 1;
}

int main(){
    (prost1(13))?printf("Prost.\n"):printf("Nije prost.\n");
    (prost2(13))?printf("Prost.\n"):printf("Nije prost.\n");
    (prost3(13))?printf("Prost.\n"):printf("Nije prost.\n");
    return 0;
}
