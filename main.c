#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_PALABRAS 1000 /*estimamos que el input no superara los 999 caracteres*/
#define MAX_LONGITUD 500 /*estimamos que la cadena a reconocer no supera los 499 caracteres*/

/*
    alfabeto sobre el cual reconoce el automata:
    Σ = {0,1,2,3,4,5,6,7,8,9,+,-,x,A,B,C,D,E,F}
	debido a esto validamos de antemano que todos los caracteres de la cadena a reconocer esten contenidos en el mismo

*/

bool verifica(char *s)
{
    int i;

    for(i = 0; s[i] != '\0'; i++)
    {
        if(!(isdigit((unsigned char)s[i]) ||
             s[i] == '+' ||
             s[i] == '-' ||
             s[i] == 'x' ||
             (s[i] >= 'A' && s[i] <= 'F')))
        {
            return false;
        }
    }

    return true;
}

/*
    Columnas de la matriz:
    0: 0
    1: 1 a 7
    2: 8 y 9
    3: + y -
    4: x
    5: A a F
*/
int columna(int c)
{
    if(c == '0')
        return 0;

    if(c >= '1' && c <= '7')
        return 1;

    if(c == '8' || c == '9')
        return 2;

    if(c == '+' || c == '-')
        return 3;

    if(c == 'x')
        return 4;

    return 5; /* A-F */
}


int esPalabra(char *s) /*pasa toda la palabra por el automata*/
{ /*en el documento auxiliar esta la tabla con los estados y transiciones*/
    static int tt[8][6] =
    {
        {2,3,3,1,7,7},
        {3,3,3,7,7,7},
        {4,4,7,7,5,7},
        {3,3,3,7,7,7},
        {4,4,7,7,7,7},
        {6,6,6,7,7,6},
      	{6,6,6,7,7,6},
    	{7,7,7,7,7,7}
    };

    int e = 0; /*numero de estado, arranca por el inicial*/
    int i = 0; /*indice del caracter a procesar*/
    int c = s[0]; /*caracter a procesar*/

    while(c != '\0')
    {
        e = tt[e][columna(c)];
        c = s[++i];
    }

    if(e == 2 || e == 3)
        return 1;

    if(e == 4)
        return 2;

    if(e == 6)
        return 3;

    return 0;
}

int separar(char *cadena, char palabras[][MAX_LONGITUD])
{
    int i = 0;
    int fila = 0;
    int posicion = 0;

    while(cadena[i] != '\0')
    {
        if(cadena[i] == '@')
        {
            palabras[fila][posicion] = '\0';
            fila++;
            posicion = 0;
        }
        else
        {
            palabras[fila][posicion] = cadena[i];
            posicion++;
        }

        i++;
    }

    palabras[fila][posicion] = '\0';

    return fila + 1; /*cantidad de palabras = cantidad de @ + 1*/
}

int main()
{
    char cadena[MAX_LONGITUD];
    char palabras[MAX_PALABRAS][MAX_LONGITUD];

    int cantidadPalabras;
    int cantidadDecimales = 0;
    int cantidadOctales = 0;
    int cantidadHexadecimales = 0;

    int resultado;
    int hayError = 0;
    int i;

    printf("Ingrese las constantes separadas por @:\n");

    fgets(cadena, MAX_LONGITUD, stdin) 

    cadena[strcspn(cadena, "\n")] = '\0'; /*acalarar en documentacion*/

    if(cadena[0] == '\0')
    {
        printf("Error lexico: la cadena esta vacia.\n");
        return 1;
    }

    cantidadPalabras = separar(cadena, palabras);

    for(i = 0; i < cantidadPalabras; i++)
    {
        printf("\nConstante %d: %s\n", i + 1, palabras[i]);

        if(palabras[i][0] == '\0')
        {
            printf("Error lexico: constante vacia.\n");
            hayError = 1;
        }
        else if(!verifica(palabras[i]))
        {
            printf("Error lexico: contiene caracteres fuera del alfabeto.\n");
            hayError = 1;
        }
        else
        {
            resultado = esPalabra(palabras[i]);

            if(resultado == 1)
            {
                printf("Tipo: decimal\n");
                cantidadDecimales++;
            }
            else if(resultado == 2)
            {
                printf("Tipo: octal\n");
                cantidadOctales++;
            }
            else if(resultado == 3)
            {
                printf("Tipo: hexadecimal\n");
                cantidadHexadecimales++;
            }
            else
            {
                printf("Error lexico: no pertenece a ningun grupo.\n");
                hayError = 1;
            }
        }
    }

    printf("\n----------------------------------\n");
    printf("Cantidad de decimales: %d\n", cantidadDecimales);
    printf("Cantidad de octales: %d\n", cantidadOctales);
    printf("Cantidad de hexadecimales: %d\n", cantidadHexadecimales);

    if(hayError)
        printf("Existe una cadena que contiene errores lexicos.\n");
    else
        printf("Todas las cadenas son lexicamente correctas.\n");

    return 0;
}