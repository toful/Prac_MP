#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define N 20



void inicialitza(unsigned int v[], int lenght)
{
    int i;
    srand(time(NULL));
    for (i = 0; i < lenght; i++) v[i] = rand()%(lenght*100);
}

void visualitza(unsigned int v[], int l)
{
    int i;
    printf ("Vector amb %i elements\n", l);
    for (i = 0; i < l; i++)
    {
        printf("%d, ", v[i]);
    }
}

void swap(unsigned int v[], int i, int j){
    int a=v[i];
    v[i]=v[j];
    v[j]=a;
}

void selection_sort(unsigned int v[], int length){
    int j, i;

    for (j = 0; j < length-1; j++){
        int iMin = j;
        for (i = j+1; i < length; i++) {
            if (v[i] < v[iMin]) {
                iMin = i;
            }
        }
        if(iMin != j){
            swap(v, j, iMin);
        }
    }

}

bool dicotomic_search(unsigned int v[], int lenght, int var){
    int inf=0;
    int sup=lenght-1;
    int cent;
    bool trobat=false;

    while(inf<=sup && !trobat){
        cent=(sup-inf)/2;
        if(v[cent]==var){
            trobat=true;
        }
        else{
            if(v[cent]>var){
                sup=cent;
            }
            else inf = cent;
        }
    }
    return trobat;
}

int main()
{
    unsigned int v[N];
    inicialitza(v, N);
    visualitza(v, N);
    selection_sort(v, N);

    printf("\nAfter selection sort:\n");
    visualitza(v, N);

    return(0);
}
