#include <stdio.h>

int caracterAEntero(char c)
{
    return c - '0';
}

/*
    Se resta el carácter '0'. Como los caracteres numéricos son consecutivos
    en la tabla ASCII, la diferencia entre el carácter recibido y '0'
    coincide con su valor numérico.
*/

int main()
{
    char c;

    printf("Ingrese un caracter numerico: ");
    scanf(" %c", &c);

    if(c >= '0' && c <= '9')
        printf("Valor entero: %d\n", caracterAEntero(c));
    else
        printf("Error. El caracter ingresado no es numerico.\n");

    return 0;
}