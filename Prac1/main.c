#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>  // En entorns Unix aquesta llibreria no funciona i podem utilitzar la equivalent ncurses.h
#include <time.h>
#include <windows.h>
#include <math.h>

#define N 20
#define NUM_REPETICIONS 3
#define NUM_ELEMENTS_ARRAY(x) (sizeof(x)/sizeof(x)[0]);


// Inicialitza seed i plena el vetor fins al final amb valors random
void ompleVectorAleatoriament (unsigned int v[], int midaVector)
{
    int i;
    srand(time(NULL));
    for (i=0; i<midaVector; i++){
        v[i] = rand()%(midaVector*100);
    }
}

//Imprimeix el vector per pantalla
void visualitza(unsigned int v[],int midaVector)
{
    int i;
    printf ("\n\nVector amb %i elements\n", midaVector);
    for (i = 0; i < midaVector; i++)
    {
        printf("%d, ", v[i]);
    }
}

// Funció auxiliar per l'algoritme de bombolla i selection sort
void swap(unsigned int v[], int i, int j){
    int a=v[i];
    v[i]=v[j];
    v[j]=a;
}


int bombolla (unsigned int v[], int midaVector){
    int i, j, cmpt=0;
    bool swapped = false;

    for(i=0; i < midaVector-1; i++)
        {
            for(j=0; j<midaVector-1-i; j++){
                if (v[j] > v[j+1]){
                swap(v, j, j+1);
                swapped = true;
                }
                cmpt++;
            }
        if(!swapped) break;
        }
        //midaVector = midaVector-1;
    return cmpt;
}

int selection_sort(unsigned int v[], int length){
    int j, i, cmpt=0;

    for (j = 0; j < length-1; j++){
        int iMin = j;
        for (i = j+1; i < length; i++) {
            if (v[i] < v[iMin])
            {
                iMin = i;
            }
            cmpt++;
        }
        if(iMin != j){
            swap(v, j, iMin);
        }
    }
    return cmpt;
}

// Cost quadràtic
int insercio(unsigned int v[], int length)
{
    int i, j, cmpt = 0, temp;
    time_t time();
    for (i = 1; i < length; i++)
    {
        temp = v[i];
        j = i - 1;
        while (v[j] > temp && j >= 0)
        {
            v[j+1] = v[j];
            j--;
            cmpt++;
        }
        v[j+1] = temp;
    }
    return cmpt;
}
void imprimeixMatriudouble(int num_proves,double m[][num_proves], double d[][num_proves], int mides_vector[], int tipus)
{
    int i, j, columnesimpreses;

    if (tipus<3) columnesimpreses=3;
    else columnesimpreses = 2;
    printf("\n\n");
    if (tipus%2 != 0) printf ("Unitats de les dades: segons\n");
    else printf ("Unitats de les dades: milions d'iteracions del bucle intern\n");
    if (tipus < 3) printf ("Elements\tBombolla\tSeleccio\tInsercio");
    else (printf ("Elements\tValor Present\tValor no Present"));
    for (j = 0; j < num_proves; j++)
    {
        printf("\n* %i\t", mides_vector[j]);
        for (i = 0; i < columnesimpreses; i++)
        {
            if (tipus == 1)
            {
                printf("* %f±%f ", m[i][j], d[i][j]);
            }
            else printf("* %f±%f ", m[i][j]/1000000, d[i][j]);
        }
    }
}
//funcio per a calcular la desviacio estandar d'un vector de dades
float desvest (float dades[], int midaVector){
    float suma = 0.0;
    float mitjana, devStand = 0.0;
    int i;
    //sumatori de totes les dades
    for (i=0; i<midaVector; i++){
        suma += dades[i];
    }
    //calcular a mitjana
    mitjana = suma/midaVector;
    //calcular desviacio
    for (i=0; i<midaVector; i++){
        devStand += pow(dades[i]-mitjana, 2);
    }
    //retornem l'arrel quadrada
    return sqrt(devStand/midaVector);
}

//Omple el vector ordenadament amb valors multiples de 2
void ompleVectorOrdenadament(unsigned int v[], int length_v)
{
    int i;
    for (i=0; i<length_v; i++)
    {
        v[i]=2*i;
    }
}

// Cerca un valor dins del vector i retorna fals o cert segons si l'ha trobat
bool dicotomic_search(unsigned int v[], int lenght, int var, int *counter){
    int inf=0;
    int sup=lenght-1;
    int cent;
    bool trobat=false;
    *counter=0;

    while(inf<=sup && !trobat){
        cent=(sup-inf)/2+inf;
        *counter=*counter+1;
        if(v[cent]==var){
            trobat=true;
        }
        else{
            if(v[cent]>var){
                sup=cent-1;
            }
            else inf = cent+1;
        }
    }
    return trobat;
}

// Imprimeix per pantalla una matriu que relaciona el tipus d'algoritme utilitzat amb la mida del vector
// Non mas utilitza el vector del main ja que per a fer les diferents proves hem de redefinir la mida del vector en temps d'execució
void mesures_temps()
{
    //Variables per a calcular el temps
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    int mida_vector[] = {10, 50, 100, 500, 1000, 2000, 5000, 10000, 20000, 25000}; // mida que tindra el vector a ordenar en cada una de les proves amb diferent mida
    int i, j, length_v, acumulador_i;
    double acumulador;  // Acumula els segons al llarg de les repeticions per a fer la mitjana aritmetica
    int num_proves = NUM_ELEMENTS_ARRAY(mida_vector); // Obté el nombre de proves (nombre de files de la matriu de resultats mat_t) utilitzant la macro definida
    float dades_t[NUM_REPETICIONS], dades_i[NUM_REPETICIONS];    // Definim dues taules de flotants per a acumular mostres i fer desvest
    double mat_t[3][num_proves], mat_t_desvest[3][num_proves];    // matriu amb les mitjanes de temps amb el format descrit a la documentacio
    double mat_i[3][num_proves], mat_i_desvest[3][num_proves];    // matriu amb les mitjanes de iteracions
    // Columna per a l'algoritme de bombolla
    for (j = 0; j < num_proves; j++)
    {
        unsigned int v[mida_vector[j]];
        length_v = NUM_ELEMENTS_ARRAY(v);
        acumulador = 0;
        acumulador_i = 0;
        for (i=0 ; i < NUM_REPETICIONS; i++)
        {
            ompleVectorAleatoriament(v, length_v);
            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&start);
            dades_i[i] = bombolla(v, length_v);
            acumulador_i += dades_i[i];
            QueryPerformanceCounter(&end);
            dades_t[i] = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
            acumulador = acumulador + dades_t[i];
        }
        mat_t[0][j] = acumulador/(double)NUM_REPETICIONS;
        mat_i[0][j] = acumulador_i/(double)NUM_REPETICIONS;
        mat_t_desvest[0][j] = desvest(dades_t, NUM_REPETICIONS);
        mat_i_desvest[0][j] = desvest(dades_i, NUM_REPETICIONS);

    }
        // Columna per a l'algoritme de selecció
    for (j = 0; j < num_proves; j++)
    {
        unsigned int v[mida_vector[j]];
        length_v = NUM_ELEMENTS_ARRAY(v);
        acumulador = 0;
        acumulador_i = 0;
        for (i=0 ; i < NUM_REPETICIONS; i++)
        {
            ompleVectorAleatoriament(v, length_v);
            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&start);
            dades_i[i] = selection_sort(v, length_v);
            acumulador_i += dades_i[i];
            QueryPerformanceCounter(&end);
            dades_t[i] = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
            acumulador = acumulador + dades_t[i];
        }
        mat_t[1][j] = acumulador/(double)NUM_REPETICIONS;
        mat_i[1][j] = acumulador_i/(double)NUM_REPETICIONS;
        mat_t_desvest[1][j] = desvest(dades_t, NUM_REPETICIONS);
        mat_i_desvest[1][j] = desvest(dades_i, NUM_REPETICIONS);

    }
        // Columna per a l'algoritme de insercio
    for (j = 0; j < num_proves; j++)
    {
        unsigned int v[mida_vector[j]];
        length_v = NUM_ELEMENTS_ARRAY(v);
        acumulador = 0;
        acumulador_i = 0;
        for (i=0 ; i < NUM_REPETICIONS; i++)
        {
            ompleVectorAleatoriament(v, length_v);
            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&start);
            dades_i[i] = insercio(v, length_v);
            acumulador_i += dades_i[i];
            QueryPerformanceCounter(&end);
            dades_t[i] = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
            acumulador = acumulador + dades_t[i];
        }
        mat_t[2][j] = acumulador/(double)NUM_REPETICIONS;
        mat_i[2][j] = acumulador_i/(double)NUM_REPETICIONS;
        mat_t_desvest[2][j] = desvest(dades_t, NUM_REPETICIONS);
        mat_i_desvest[2][j] = desvest(dades_i, NUM_REPETICIONS);

    }
    //imprimir per pantalla
    imprimeixMatriudouble(num_proves, mat_t, mat_t_desvest, mida_vector, 1);
    imprimeixMatriudouble(num_proves, mat_i, mat_i_desvest, mida_vector, 2);

    // CASOS AMB EL VECTOR JA ORDENAT
    printf("\n\nCAS MILLOR\n");
    // Columna per a l'algoritme de bombolla
    for (j = 0; j < num_proves; j++)
    {
        unsigned int v[mida_vector[j]];
        length_v = NUM_ELEMENTS_ARRAY(v);
        acumulador = 0;
        acumulador_i = 0;
        for (i=0 ; i < NUM_REPETICIONS; i++)
        {
            ompleVectorAleatoriament(v, length_v); // omplim el vector
            insercio(v, length_v); // L'ordenem amb un algoritme arbitrari, i duem a terme les mateixes proves
            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&start);
            dades_i[i] = bombolla(v, length_v);
            acumulador_i += dades_i[i];
            QueryPerformanceCounter(&end);
            dades_t[i] = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
            acumulador = acumulador + dades_t[i];
        }
        mat_t[0][j] = acumulador/(double)NUM_REPETICIONS;
        mat_i[0][j] = acumulador_i/(double)NUM_REPETICIONS;
        mat_t_desvest[0][j] = desvest(dades_t, NUM_REPETICIONS);
        mat_i_desvest[0][j] = desvest(dades_i, NUM_REPETICIONS);

    }
        // Columna per a l'algoritme de selecció
    for (j = 0; j < num_proves; j++)
    {
        unsigned int v[mida_vector[j]];
        length_v = NUM_ELEMENTS_ARRAY(v);
        acumulador = 0;
        acumulador_i = 0;
        for (i=0 ; i < NUM_REPETICIONS; i++)
        {
            ompleVectorAleatoriament(v, length_v);
            insercio(v, length_v); // L'ordenem amb un algoritme arbitrari, i duem a terme les mateixes proves
            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&start);
            dades_i[i] = selection_sort(v, length_v);
            acumulador_i += dades_i[i];
            QueryPerformanceCounter(&end);
            dades_t[i] = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
            acumulador = acumulador + dades_t[i];
        }
        mat_t[1][j] = acumulador/(double)NUM_REPETICIONS;
        mat_i[1][j] = acumulador_i/(double)NUM_REPETICIONS;
        mat_t_desvest[1][j] = desvest(dades_t, NUM_REPETICIONS);
        mat_i_desvest[1][j] = desvest(dades_i, NUM_REPETICIONS);

    }
        // Columna per a l'algoritme de insercio
    for (j = 0; j < num_proves; j++)
    {
        unsigned int v[mida_vector[j]];
        length_v = NUM_ELEMENTS_ARRAY(v);
        acumulador = 0;
        acumulador_i = 0;
        for (i=0 ; i < NUM_REPETICIONS; i++)
        {
            ompleVectorAleatoriament(v, length_v);
            insercio(v, length_v); // L'ordenem amb un algoritme arbitrari, i duem a terme les mateixes proves
            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&start);
            dades_i[i] = insercio(v, length_v);
            acumulador_i += dades_i[i];
            QueryPerformanceCounter(&end);
            dades_t[i] = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
            acumulador = acumulador + dades_t[i];
        }
        mat_t[2][j] = acumulador/(double)NUM_REPETICIONS;
        mat_i[2][j] = acumulador_i/(double)NUM_REPETICIONS;
        mat_t_desvest[2][j] = desvest(dades_t, NUM_REPETICIONS);
        mat_i_desvest[2][j] = desvest(dades_i, NUM_REPETICIONS);

    }
    //imprimir per pantalla
    imprimeixMatriudouble(num_proves, mat_t, mat_t_desvest, mida_vector, 1);
    imprimeixMatriudouble(num_proves, mat_i, mat_i_desvest, mida_vector, 2);

    //Algoritme de cerca dicotomica
    printf ("\n\n Algoritme de cerca dicotomica\n\n");
    // Cas de que el valor ja es troba
    int iteracions=0;
     for (j = 0; j < num_proves; j++)
    {
        unsigned int v[mida_vector[j]];
        length_v = NUM_ELEMENTS_ARRAY(v);
        acumulador = 0;
        acumulador_i = 0;
        for (i=0 ; i < NUM_REPETICIONS; i++)
        {
            ompleVectorAleatoriament(v, length_v); //Omplim el vector
            insercio(v, length_v);  //L'ordenem
            iteracions = 0; // Iniciem comptador
            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&start);
            dicotomic_search(v, length_v, v[rand()%mida_vector[j]], &iteracions); //Li passem una posicio dins del vector que sabem que existeix
            QueryPerformanceCounter(&end);
            dades_t[i] = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
            acumulador += dades_t[i];
            acumulador_i += iteracions; // acumulem per a la mitjana
            dades_i[i] = iteracions;  // guardem a la taula per a desvest
        }
        mat_t[0][j] = acumulador/(double)NUM_REPETICIONS;
        mat_i[0][j] = acumulador_i/(double)NUM_REPETICIONS;
        mat_t_desvest[0][j] = desvest(dades_t, NUM_REPETICIONS);
        mat_i_desvest[0][j] = desvest(dades_i, NUM_REPETICIONS);
    }

    //Cas de que el valor no es trobi
    int value;

      for (j = 0; j < num_proves; j++)
    {
        unsigned int v[mida_vector[j]];
        length_v = NUM_ELEMENTS_ARRAY(v);
        acumulador = 0;
        acumulador_i = 0;   // En aquet algoritme no acumulen res pero reaprofitem les variables, contenen el resultat de cada iteracio e temps i iteracions
        for (i=0 ; i < NUM_REPETICIONS; i++)
        {
            ompleVectorOrdenadament(v, length_v); //Omplim el vector
            value = rand();
            if (value % 2 == 0) value++;
            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&start);
            dicotomic_search(v, length_v, value, &iteracions); //Li passem una posicio dins del vector que sabem que no existeix
            QueryPerformanceCounter(&end);
            dades_t[i] = (double) (end.QuadPart - start.QuadPart) / frequency.QuadPart;
            acumulador += dades_t[i];
            acumulador_i += iteracions; // acumulem per a la mitjana
            dades_i[i] = iteracions;  // guardem a la taula per a desvest
        }
        mat_t[1][j] = acumulador/(double)NUM_REPETICIONS;
        mat_i[1][j] = acumulador_i/(double)NUM_REPETICIONS;
        mat_t_desvest[1][j] = desvest(dades_t, NUM_REPETICIONS);
        mat_i_desvest[1][j] = desvest(dades_i, NUM_REPETICIONS);
    }
    imprimeixMatriudouble(num_proves, mat_t, mat_t_desvest, mida_vector, 3);
    imprimeixMatriudouble(num_proves, mat_i, mat_i_desvest, mida_vector, 4);
}

// Mostra el menu d'opcions i evita que l'usuari esculli una opcio incorrecta
int opcio ()
{
    int c=0;
    while (1){
    printf ("\nQue vols fer?\n1.-Seleccio\n2.-Bombolla\n3.-Insercio\n4.-Cerca dicotomica\n5.-Taula de resultats (tarda uns quant segons)\n6.-Reomplir vector\n7.-Visualitzar contingut del vector\n8.-Sortir\t\t->");
    c = getche();
    if (c < 49 || c > 56) printf ("\n\nOpcio incorrecta, torna-ho a intentar...");
    else break;
    }
    return (c - 48);
    //return c;
}

int main()
{
    unsigned int v[100], valor;
    int midaVector = NUM_ELEMENTS_ARRAY(v);
    int counter;

    ompleVectorAleatoriament(v, midaVector);
    while (true)
    {
        switch (opcio())
        {
            case 1: printf("\n\nLi ha costat %i iteracions ordenar el vector",selection_sort(v, midaVector)); break;
            case 2: printf("\n\nLi ha costat %i iteracions ordenar el vector",bombolla(v, midaVector)); break;
            case 3: printf("\n\nLi ha costat %i iteracions ordenar el vector",insercio(v, midaVector)); break;
            case 4:
                printf("\nQuin valor vols buscar?\n");
                scanf("%i", &valor);
                if (dicotomic_search(v, midaVector, valor, &counter)) printf("\n\nEl valor es troba dins del nostre vector i ha tardat %d iteracions",counter);
                    else printf("\n\nEl valor no es troba dins del nostre vector i ha tardat %d iteracions",counter);
                break;
            case 5: mesures_temps(v, midaVector); break;
            case 6: ompleVectorAleatoriament(v, midaVector); break;
            case 7: visualitza(v, midaVector); break;
            case 8: return 0;
        }
        printf ("\n\n");
    }
    return 0;
}
