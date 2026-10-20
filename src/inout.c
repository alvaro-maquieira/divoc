// MÓDULO INOUT

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "database.h"
#include "inout.h"

void stripe(char c) // Función para realizar la caja de la carátula
{
  int i;
  for(i=0;i<50;i++)
    {
      fprintf(stdout,"%c",c);
    }
  return;
}

void headline(char *t,char c) // Función que muestra el título del programa
{
  int i, l;
  l=strlen(t);
  fprintf(stdout,"\n%c",c);
  for(i=0;i<((49-l)/2);i++)
    {
      fprintf(stdout," ");
    }
  fprintf(stdout,"%s",t);
  if (l%2) l+=1;
  for(i=0;i<((49-l)/2);i++)
    {
      fprintf(stdout," ");
    }
  fprintf(stdout,"%c\n",c);
  return;
}

void get_string(char *cadena,int min,int max,char *frase) // Función utilizada para la entrada de texto
{
  char texto[256],comp[256];
  do
    {
      fprintf(stdout,"\n%s(%d-%d char): ",frase,min,max);
      fgets(texto,sizeof(texto),stdin);
      sscanf(texto,"%s",comp);
    }while((strlen(comp)<min)||(strlen(comp)>max)); // Se vuelve a pedir una cadena hasta que el usuario la introduzca con la longitud correcta
  strcpy(cadena,comp);
  return;
}

int get_integer(int min,int max,char *frase) // Función para realizar la introducción de números
{
  char texto[256];
  int num;
  do
    {
      fprintf(stdout,"\n%s[%d-%d]: ",frase,min,max);
      fgets(texto,sizeof(texto),stdin);
      sscanf(texto,"%d",&num);
    }while((num<min)||(num>max)); // Se pide el número hasta que este dentro del intervalo pedido
  return num; // Se retorna el número introducido
}

char get_character(char *palabra, char *mensaje) // Función usada para obtener caracteres
{
  char letra,texto[256];
  do
    {
      fprintf(stdout,"\n%s (%s): ",mensaje,palabra);
      fgets(texto,sizeof(texto),stdin);
      sscanf(texto,"%c",&letra);
    }while((strlen(texto)>2)||(strchr(palabra,toupper(letra))==NULL)); // Se repite la peticiónd e introducción del carácter hasta que se introduzca una carácter válido
  return toupper(letra); // Se retorna dicho carácter
}

int yes_or_no(char *m) // Función para que el usuario seleccione si o no y se retorne 1 o 0 respecto a la respuesta
{
  char texto[256],c;
  do
    {
      fprintf(stdout,"\n%s (y/n): ",m);
      fgets(texto,sizeof(texto),stdin);
      sscanf(texto,"%c",&c);
      c=toupper(c);
    }while((strlen(texto)>2)||((c!='Y')&&(c!='N'))); // Se introduce el la cadena hasta que esta sea y o n
  if(c=='Y') return 1; // Si se introduce 'y' se retorna 1
  else return 0; // Se retorna 0 si se ha introducido 'n'
}

void display_patient(struct patient pac) // Función para mostrar a un paciente
{
  fprintf(stdout,">%24s;%s;%d;%d;%d;%c;\n",pac.nombre,pac.DNI,pac.edad,pac.fiebre,pac.tos,pac.sintoma);
  return;
}

int verify_DNI(char *dni) // Función para comprobar que el DNI introducido es el correcto
{
  char comp[]="TRWAGMYFPDXBNJZSQVHLCKE";
  int num,ind,i;
  char digit[10];
  strcpy(digit,dni);
  digit[8]='\0';
  // Se comprueba que ne el DNI se han introducido 8 digitos
  for(i=0;i<8;i++)
    {
      if (isdigit(digit[i])) continue;
      else
	{
	  fprintf(stdout,"\nInvalid DNI\n");
	  return 0;
	}
    }
  num = atoi(dni);
  ind = num%23;
  // Se comprueba que si la letra del DNI dado se corresponde con la letra correspondiente de la lista
  if (comp[ind]==dni[8]) return 1;
  else
    {
      fprintf(stdout,"\nInvalid DNI\n");
      return 0;
    }
}
