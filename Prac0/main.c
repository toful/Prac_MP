#include <stdbool.h>
#define NUMELEM 20

void afegir(int elem, int v[], int *n){
    bool inserit = false;
    int i=0;
    int aux, aux2;
    /*printf("\n%d", elem);*/
    if(*n<NUMELEM){
        *n=*n+1;
        while(i<*n){
            if(elem < v[i]){
                aux=v[i];
                v[i]=elem;
                inserit= true;
                i++;
                while(i<*n){
                    aux2=v[i];
                    v[i]=aux;
                    aux=aux2;
                    i++;
                }
            }
            else i++;
        }
        if(inserit==true) v[i]=aux;
        else v[i]=elem;
    }
    else{
        printf("La llista ja està plena!!!\n");
    }

}

void eliminar(int pos, int v[], int *n){
    if(pos<*n && pos>=0 && *n>0){
        while(pos<*n){
            v[pos]=v[pos+1];
            pos++;
        }
        *n=*n-1;
    }
    else printf("\nHas indicat una posició fora dels límits de l'array!\n");

}

void printVector(int v[], int n){
    int i;
    for(i=0; i<n; i++){
        printf("%d\t",v[i]);
    }
}

int main (void){
    int v[NUMELEM];
    int n=0;

    afegir(34, v, &n);
    afegir(2, v, &n);
    afegir(21, v, &n);
    afegir(-5, v, &n);
    afegir(100, v, &n);
    afegir(32, v, &n);
    afegir(-70, v, &n);
    printVector(v, n);
    eliminar(2, v, &n);
    printf("\n");
    printVector(v, n);
    eliminar(25, v, &n);

    return 0;
}

