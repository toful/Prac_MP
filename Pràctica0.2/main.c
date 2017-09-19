#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#define NELEM 20
int elem = 0;
int v[NELEM];

void afegir(){
    int num=-1, i=0, j;

    printf("\nQuin numero vols afegir?");
    scanf("%i", &num);
    if (elem != 0){
        while(num>v[i] && i < elem){ /*el nombre es mes gran que la pos on estem*/
            i++;
        } /*quan sorti, la pos sera la seguent*/
        for (j=elem; j>=i; j--){
            v[j+1]=v[j]; /*desplacem cap a la dreta fins a la posició on hem d'afegir*/
        }
    }
    v[i]=num;
    elem++;

}
 void eliminar(){
    int pos=NELEM+1, j;
    while(pos>=elem){
        printf("\nQuina posicio vols eliminar?");
        scanf("%i", &pos);
        if (pos>=elem) printf("la posicio no existeix");
    }
    for (j=pos; j<elem; j++){
    v[j]=v[j+1]; /*desplacem cap a l'esquerra fins a la posició on hem d'eliminar*/
    }
    elem--;
}
 void imprimir(){
    int i;
    printf("Array: \n"); /*imprimir per pantalla l'array*/
        for (i=0; i<elem; i++){
            printf("%i, ", v[i]);
        }
 }
int main()
{
    char comanda;
    while (1){
        imprimir();
        comanda = ' ';
    while (comanda!=101 && comanda!=97){
        printf("\nQuina accio vols fer?");
        if (elem < NELEM) printf ("\n\ta=afegir");
        else printf ("El vector esta ple!");
        printf ("\n\te=eliminar\n");
        comanda = getche();
        if (comanda==97 && elem<NELEM) afegir();
        else if (comanda==101) eliminar();
        else return 0;
    }
    }
    return 0;
}

