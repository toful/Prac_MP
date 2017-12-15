#include <stdio.h>
#include <stdlib.h>
#include <String.h>
// https://es.wikipedia.org/wiki/String.h
#include <stdbool.h>
#include <math.h>

/*
* Anomenem EXPRESSIÓ a tot el que no sigui un nombre, es a dir, tot allo que té la forma A op B, sent A o B al seu torn, EXPRESSIONS o NOMBRES
* Anomenem NOMBRE a les expressions numeriques aillades.
* Anomenem OPERADOR al signe de l'operació, es a dir: {+,-,*,/ o %}
* Anomenem OPERAND a A o B, pel que els operands poden ser EXPRESSIONS o bé NOMBRES
*
* Precondicions i assumpcions del problema:
* - No hi ha parentesi redundants envoltant NOMBRES, nomes envoltant EXPRESSIONS
*/

/*
* rep un caracter i retorna >0 si es un OPERAND, tot indicant la seva prioritat
* sino retorna 0
*/
int esSigne(char c)
{
    if (c == 94) return 3; // si es una potencia retornem 3
    if (c == 47 || c == 42 || c == 37) return 2; // si es una multiplicacio o una divisio o una operacio de modul
    if (c == 43 || c == 45) return 1;
    return 0;
}

/*
* PRE = op es un OPERAND sense errors ni parentesi redundants rodejantla
* POST = si op conte una EXPRESSIO retorna -1, si conte un NOMBRE retorna el valor d'aquest nombre amb un int
*/
int esNumero (char op[], int length){
    int i;
    op[length] = '\0'; // posem caracter de final d'array, d'aquesta manera la funcio atoi ignora la brossa de final d'array
    for (i = 0 ; i < length; i++)
    {
        if (op[i] < 48 || op[i] > 57) return -1;  //fem el bucle per a recorrer tot l'array fins al final, si trobem alguna cosa que no sigui num eric sortim
    }
    return atoi(op); // si arribem al final sennse trobar res que no sigui una xifra d'un nombre convertim el nombre a int i el retornem
}

/*
* PRE = L'operacio rebuda ha de ser una EXPRESSIO, que no conte parentesis redundants
* per tant l'expressio rebuda es pot descomposar en:
* - EXPRESSIO op NOMBRE (o a l'inrevés)
* - NOMBRE op NOMBRE
* - EXPRESSIO op EXPRESSIO
* POST =
* - La variable operador conté l'OPERADOR que delimita els dos OPERANDS
* - opA, opB, lengthA i lengthB contenen la informacio dels OPERAND (contingut i longitud de cadascun d'ells)
*/
void trobaOperands(char op[], int length, char opA[], char opB[], int *lengthA, int *lengthB, char *operador)
{
    int i, j, parentesi = 0; //funciona com una pila per a trobar el parentesi final en el cas que op sigui una expressio
    for (i=0;;i++) // recorrem fins condicio de sortida donada per l'instruccio break
    {
        if (op[i] == '(') parentesi++;   //si es un obrir parentesi apilem parentesis
        if (op [i] == ')') parentesi--;   //  si es un de tancar desapilem parentesis
        if (esSigne(op[i]) && parentesi == 0) // si trobem un operaador amb la prioritat mes baixa , es a dir, que no esta dins de cap parentesis hem arribat al final de A
        {
            *lengthA = i;   // la longitud de A sera l'index de l'array per apuntar al signe
            *operador = op[i];     // guardem el signe
            for (j = 0; j < i; j++) opA[j] = op[j]; // copiem el contingut de l'operand A a l'array de parametre
            break; // sortim del primer while
        }
    }
    i++; // i apunta al principi del segon OPERAND
    for (j = 0; j+i < length; j++) opB[j] = op[j+i]; // recorrem fins al final de l'expressio copiant el segon OPERAND
    *lengthB = length - i; // la longitud de B es la longitud total de op menys i, que apunta a la posicio inicial de B
}

/*
* Degut a que podem tenir més de dos OPERANDS s'ha dissenyat la següent funcio que permet aplicar prioritat d'operacions afegint parentesi.
* Per tant, de la fase 1 a la 2 no hem modificat la funcio opera, sino que simplement hem afegit aquesta funcio que afegeix aquesta funcionalitat.
*
* Cal veure que si tenim mes de 3 OPERANDS a la mateixa altura la casuistica es la mateixa, ja que tot ens porta a una casuistica de tenir
* 3 OPERANDS.
* Per a entendre la seva casuistica de la funcio cal entendre que l'avaluador d'expressions en la fase 1 llegeix sempre de dreta a esquerra
* si no hi ha parentesis de prioritat. Pel que totes les expressions A op B op C s'avaluen com A op (B op C). Sabent aixo els casos que poden existir:
* A op B op C | A OP B OP C -> Indiferent, de dreta a esquerra la prioritat es la mateixa
* A op B OP C -> segueix la prioritat d'operacio implicita en la funcio opera
* A OP B op C -> L'únic cas que cal tractar, ja que si no afegim parentesi explicits l'EXPRESSIO s'avaluara com A OP (B op C), de manera incorrecta
* PRE = cert
* POST = si l'expressio es del tipus A OP B op C, afegeix els parentesis explicits de la següet manera -> (A OP B) op C per a que es compleixi
* la jerarquia d'operacions
*/
void prioritzaOperacions(char op[], int *length)
{
    int signe1, signe2, i, parentesi=0, pos_signe_ini = -1, pos_signe_fi = -1;

    for (i = 0; i < (*length); i++)
    {
        if (op[i] == '(') parentesi++;   //si es un obrir parentesi apilem parentesis
        if (op [i] == ')') parentesi--;   //  si es un de tancar desapilem parentesis
        if (parentesi == 0 && esSigne(op[i])) // si trobem una operacio
        {
            if (pos_signe_ini == -1)  // si no hem iniciat el punter del primer signe l'inicialitzem
            {
                pos_signe_ini = i; // salvem index al primer signe
            }
            else // si ja hem inicialitzat punter inicial
            {
                pos_signe_fi = i; // salvem index al segon signe
                break;  // sortim del bucle
            }
        }
    }
    if (pos_signe_fi == -1) return; // Si no hem trobat el segon signe llavors sortim

    if ( (signe1 = esSigne(op[pos_signe_ini])) != (signe2 = esSigne(op[pos_signe_fi])) )
    {
        if (signe1 > signe2) // si la prioritat del primer signe es major llavors si que hem de fer alguna cosa
        {
            (*length) = (*length) + 2; // anem a afegir un parell de parentesi per tant augmentem la quantitat de caracters en 2
            for (i = (*length) - 2; i >= 0; i--) // desplacem fins a la primera posicio
            {
                op[i+1] = op[i];
            }
            op[0] = '('; // afegim el primer parentesi
            pos_signe_fi++; // corregim un degut al primer deplaçament
            for (i = (*length) - 2; i >= pos_signe_fi; i--) // desplacem fins al segon signe incloentlo
            {
                op[i+1] = op[i];
            }
            op[pos_signe_fi]= ')'; // afegim parentesi
            return; // sortim
        }
        else return; // si la prioritat del segon signe es mejor no fem res perque es fa automaticament (de dreta a esquerra)
    }
    else return; // si els signes son de igual prioritat sortim perque no cal fer res



}

/*
* Pre= L'expressio rebuda per op es correcta i pot contenir parentesis redundants rodejantla
* Post = l'expressio retornada no conte parentesis redundants en els extrems i length ha disminuit tants cops com parentesis eliminats
*/
void eliminaParentesi(char op[], int *length)
{
    int i, parentesi = 0;
    while (true)
    {
        if (op[0] == '(' && op[*length-1] == ')') // si la posicio inicial i final tenen un obrir i tancar parentesis respectivament, pot ser  que aquests siguin redundants
        {
            for (i = 0; i < *length; i++)   // recorrem l'array
            {
                if (op[i] == '(') parentesi++;  // si trobem un parentesi d'obrir apilem un parentesi
                if (op[i] == ')')   // si trobem un de tancar
                {
                    parentesi--; // desapilem un parentesi
                    if (i != (*length -1) && parentesi == 0) // si hem trobat el parentesi que tancava el primer i NO estem a l'ultima posicio de l'array, vol dir que no hi ha parentesi redundants
                    {
                        return; // sortim
                    }
                }
            }
            // si no hem sortit vol dir que els parentesi eren redundants
            for (i = 0; (i < (*length)); i++) op[i] = op[i+1];  // copiem el contingut de op sobre ell mateix, matxacant la primera posicio
            *length = *length - 2; // hem perdut dos parentesi, pel que length disminueix dos cops
        }
        else return;
    }
}

/*
* PRE = rep una expressio sense errors
* POST = calcula l'expressio rebuda i retorna el seu valor
*/
int operate(char op[], int *length)
{
    char opA[256], opB[256], operador;  // conte els operands
    int length_opA, length_opB, num, divisor;     // longitud de opA, opB, i el nombre si hem rebut una EXPRESSIO que es un NOMBRE

    eliminaParentesi(op, length); // eliminem parentesis redundants sobre l'expressio
    prioritzaOperacions(op, length);
    if ((num = esNumero(op, *length)) != -1) return num; // cas directe, si l'EXPRESSIO rebuda es tracta d'un NOMBRE el retornem
    else trobaOperands(op, *length, opA, opB, &length_opA, &length_opB, &operador); // cas no directe, descomposem l'expressio
    switch (operador) // segons l'operador fem una determinada operacio
    {
    case '+': return operate(opA, &length_opA) + operate(opB, &length_opB);
    case '-': return operate(opA, &length_opA) - operate(opB, &length_opB);
    case '*': return operate(opA, &length_opA) * operate(opB, &length_opB);
    case '/':
        if ((divisor = operate(opB, &length_opB))!= 0) return operate(opA, &length_opA) / divisor;
        else
        {
            printf("\nExcepcio aritmetica, s'ha intentat dividir per 0, canviem el 0 per un 1");
            return operate(opA, &length_opA);
        }
    case '%': return operate(opA, &length_opA) % operate(opB, &length_opB); // cas extra, operacio modul
    case '^': return pow (operate(opA, &length_opA), operate(opB, &length_opB)); // cas extra, operacio potencia
    default: return -1; // per evitar el warning del compilador
    }
}

/* Valida que el veïnatge de les operacions sigui l'adequat
 * Pre = cert
 * Post = per a qualsevol alfa tal que alfa pren valors de 0 fins length - 1 i per a qualsevol beta tal que beta va de 0 fins
 * number.length-1 llavors, si op[alfa] == number[beta] llavors retorna (op[alfa+1] == (number[beta] | (op[alfa+1] es un nombre) & op[alfa+1] != '(')))
 */
bool sintax_validation(char op[], int length)
{
    char number[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int i, j;
    bool nombrellegit = false, signellegit = false;
    for (i = 0; i < length; i++) // recorrem l'expressio
    {
        for (j = 0; j < 10 && !nombrellegit; j++)    // per cada posicio mirem si hi ha un nombre o no sempre que no haguem llegit un nombre previament
        {
            if (op[i] == number[j]) // si hi ha nombre
            {
                nombrellegit = true;    // diem que estem llegint un nombre (sortirem del bucle)
                signellegit = false;
            }
            else nombrellegit = false; // diem que no estem llegint un nombre  i provem un altre nombre
        }
        if (op[i] == '(')  // si trobem un parentesi
        {
            if (nombrellegit) return false; // i acababem de llegir un nombre veinatge no correcte
            signellegit = false;    // diem que ja no acabem de llegir un signe
        }
        if (esSigne(op[i])) // si trobem un signe
        {
            nombrellegit = false;  //diem que ja no acabem de llegir un nombre
            if (signellegit) return false;  // si acababem de lleir un signe, i acabem de trobarne un veinatge no correcte
            else signellegit = true;    // si no acabem de llegir un signe diem que si que ho aabem de fer
        }
    }
    return true; // sortim indicant veinatge correcte
}

/* Valida que els simbols siguin correctes
 * Pre = cert
 * Post = per a qualsevol alfa tal que alfa pren valors de 0 fins length - 1 llavors op[alfa+1] = seguent xifra del nombre | operador & !parentesis
 */
bool op_validation(char op[], int length){
    int j, i=0;
    bool correcte= false;
    char caracters_permesos[18] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '-', '*', '/', '%', '(', ')','^'};

    for (i = 0; i< length; i++)
    {
        for (j = 0; j < 18; j++)
        {
            if (op[i] == caracters_permesos[j])
            {
                correcte = true;    // si trobem que hi ha un dels caracters activem flag
                break;              // i sortim
            }
        }
        if (!correcte) return false; // si hem arribat aqui sense activar flag retornem fals
        correcte = false; // reiniciem variable
    }
    return true; // si arribem al final es que l'expresio es correecta
}


bool parenthesis_validation (char op[], int length){
    int parenthesis=0, i;
    for(i = 0; i < length; i++)
    {
        if(op[i]=='(' || op[i]==')')
        {
            if(op[i]=='(') parenthesis++;
            if(op[i]==')') parenthesis--;
            if(parenthesis<0) return false;
        }
    }
    if(parenthesis!=0) return false;
    else return true;
}

/****************************
*
*
*
*PROVES
*
*
*
*****************************/

void proof_op_validation(){
    char op[] = {'a', '1'};
    printf("\nExpressio amb una 'a' i un '1': %d", op_validation(op, 2));
    char op2[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '-', '*', '/', '(', ')'};
    printf("\nExpressio amb els elements acceptats: %d", op_validation(op2, 16));
    char op3[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', 'b', '9', '+', '-', '*', '/', '(', ')'};
    printf("\nExpressio amb els elements acceptats i una 'b': %d", op_validation(op3, 17));
}

void parenthesis_op_validation(){
    char op[] = {'(', ')'};
    printf("\nParentesis correctes (): %d", parenthesis_validation(op, 2));
    char op2[] = {'(', '(', '(', ')', '(', ')', ')', ')', '(', '9', ')', '(', '(', '6', ')', ')'};
    printf("\nParentesis correcets ((()()))(9)((6)): %d", parenthesis_validation(op2, 16));
    char op3[] = {')'};
    printf("\nParentesis incorrecets ): %d", parenthesis_validation(op3, 1));
    char op4[] = {'(',')',')'};
    printf("\nParentesis incorrecets ()): %d", parenthesis_validation(op4, 3));
    char op5[] = {'(','(',')'};
    printf("\nParentesis incorrecets ((): %d", parenthesis_validation(op5, 3));
}

int main()
{
    FILE *f;
    f = fopen("proves.txt","rt");
    char op[256], c;
    int i, j, length;

    while (c!= EOF)
    {
        for (i = 0; i < 256; i++) op[i] = ' '; // statement with no effect
        i=0;
        while((c=fgetc(f))!='\n' && c != EOF )
        {
            if (c != ' ' && c != '\n' && c != EOF)
            {
                op[i] = c;
                i++;
            }
        }
        length = i;
        printf("\n");
        for (j = 0; j < length; j++)
        {
            printf("%c", op[j] );
        }
        if (sintax_validation(op, length) && parenthesis_validation(op, length) && op_validation(op, length))
        {
            printf("\nEl resultat es %i\n", operate(op, &length));
        }
        else
        {
            printf ("\nAlguna validacio no s'ha dut a terme satisfactoriament. Abortant.\n");
        }
    }
    fclose(f);
    return 0;
}
