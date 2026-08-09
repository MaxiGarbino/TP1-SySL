#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LONGITUD 500 /*estimamos que la operacion no supera los 499 caracteres*/
#define MAX_NUMEROS 250 /*como minimo cada numero ocupa un caracter y va separado por un operador*/

/*
    alfabeto sobre el cual reconoce el automata:
    Σ = {0,1,2,3,4,5,6,7,8,9,+,-,*}
    debido a esto validamos de antemano que todos los caracteres de la cadena esten contenidos en el mismo
*/

bool verifica(char *s)
{
    int i;

    for(i = 0; s[i] != '\0'; i++)
    {
        if(!((s[i] >= '0' && s[i] <= '9') ||
             s[i] == '+' ||
             s[i] == '-' ||
             s[i] == '*'))
        {
            return false;
        }
    }

    return true;
}

/*
    Columnas de la matriz:
    0: digito (0 a 9)
    1: operador (+, - y *)
*/
int columna(int c)
{
    if(c >= '0' && c <= '9')
        return 0;

    return 1; /* +, - o * */
}

int esOperacion(char *s) /*pasa toda la cadena por el automata*/
{ /*en el documento auxiliar esta la tabla con los estados y transiciones*/
    static int tt[3][2] =
    {
        {1,2}, /*estado 0: inicio, espera un digito*/
        {1,0}, /*estado 1: leyendo un numero (estado de aceptacion)*/
        {2,2}  /*estado 2: error (estado trampa)*/
    };

    int e = 0; /*numero de estado, arranca por el inicial*/
    int i = 0; /*indice del caracter a procesar*/
    int c = s[0]; /*caracter a procesar*/

    while(c != '\0')
    {
        e = tt[e][columna(c)];
        c = s[++i];
    }

    if(e == 1)
        return 1; /*la cadena pertenece al lenguaje*/

    return 0;
}

int main()
{
    char cadena[MAX_LONGITUD];
    int numeros[MAX_NUMEROS];
    char operadores[MAX_NUMEROS];

    int cantidadNumeros = 0;
    int cantidadOperadores = 0;
    int numeroActual = 0;

    int resultado;
    int i;
    int j;

    printf("Ingrese una operacion con enteros decimales (+, - y *):\n");

    fgets(cadena, MAX_LONGITUD, stdin);

    cadena[strcspn(cadena, "\n")] = '\0'; /*sacamos el salto de linea que agrega fgets*/

    if(cadena[0] == '\0')
    {
        printf("Error: la cadena esta vacia.\n");
        return 1;
    }

    if(!verifica(cadena))
    {
        printf("Error lexico: contiene caracteres fuera del alfabeto.\n");
        return 1;
    }

    if(!esOperacion(cadena))
    {
        printf("Error: la cadena no representa una operacion valida.\n");
        return 1;
    }

    /*separamos la cadena en numeros y operadores*/
    i = 0;
    while(cadena[i] != '\0')
    {
        if(cadena[i] >= '0' && cadena[i] <= '9')
        {
            numeroActual = numeroActual * 10 + (cadena[i] - '0'); /*armamos el numero digito por digito*/
        }
        else
        {
            numeros[cantidadNumeros] = numeroActual;
            cantidadNumeros++;
            operadores[cantidadOperadores] = cadena[i];
            cantidadOperadores++;
            numeroActual = 0;
        }

        i++;
    }

    numeros[cantidadNumeros] = numeroActual; /*guardamos el ultimo numero*/
    cantidadNumeros++;

    /*primer paso: resolvemos las multiplicaciones porque tienen mayor precedencia*/
    i = 0;
    while(i < cantidadOperadores)
    {
        if(operadores[i] == '*')
        {
            numeros[i] = numeros[i] * numeros[i + 1];

            /*corremos un lugar a los numeros y operadores que quedaron a la derecha*/
            for(j = i + 1; j < cantidadNumeros - 1; j++)
                numeros[j] = numeros[j + 1];

            for(j = i; j < cantidadOperadores - 1; j++)
                operadores[j] = operadores[j + 1];

            cantidadNumeros--;
            cantidadOperadores--;
        }
        else
        {
            i++;
        }
    }

    /*segundo paso: resolvemos las sumas y restas de izquierda a derecha*/
    resultado = numeros[0];
    for(i = 0; i < cantidadOperadores; i++)
    {
        if(operadores[i] == '+')
            resultado = resultado + numeros[i + 1];
        else
            resultado = resultado - numeros[i + 1];
    }

    printf("Resultado: %d\n", resultado);

    return 0;
}
