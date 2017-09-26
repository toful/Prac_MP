#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define N 20

void inicialitza(int v[])
{
    int i;
    srand(time(NULL));
    for (i = 0; i < N; i++) v[i] = rand();
}

void visualitza()
{
    int i;
    printf ("Vector amb %i elements\n", N);
    for (i = 0; i < N; i++)
    {
        printf("%i, ", v[i]);
    }
}

int main()
{
    int v[N]
    inicialitza(v);
    visualitza();
    getch();
}
