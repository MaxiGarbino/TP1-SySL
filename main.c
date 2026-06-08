#include <stdio.h>
#include <ctype.h>
int columna(int c)
{
	switch(c)
	{
		case '+':
			return 1;
		case '-':
			return 2;
		default:
			return 0;
	}
}
int esPalabra(char *s)
{
	static int tt[4][3]={
						  { 2,1,1 },
						  { 2,3,3 },
						  { 2,3,3 },
						  { 3,3,3 },
						};
	int e = 0;
	int i = 0;
	int c = s[0];
	while(c!='\0')
	{
		e = tt[e][columna(c)];
		c = s[++i];
	}
	if(e==2)
		return 1;
	return 0;
}

int verifica(char *s)
{
	int i;
	for(i=0;s[i];i++)
	{
		if(!(s[i]=='+'||s[i]=='-'||isdigit(s[i])))
		{
			return 0;
		}
	}
	return 1;
}

int main()
{
	char palabra[]="g98+5652";
	//verificar si todos los caracteres 
	//pertenecen al alfabeto
	if(!verifica(palabra))
	{
		printf("HAY CARACTERES QUE NO PERTENECEN AL ALFABETO");
	}
	else
	{
		if(esPalabra(palabra))
		{
			printf("se reconoce");
		}
		else
		{
			printf("no se reconoce");
		}
	}
	return 0;
}