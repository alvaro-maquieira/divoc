// MÓDULO DATABASE

#include <stdio.h>
#include <string.h>
#include "database.h"
#include "inout.h"

void p_register(struct patient *p,int *numPacientes) // Función para registrar pacientes
{
  char nombre[25],dni[10], sintoma;
  int fiebre,tos,fecha;
  fprintf(stdout,"\nRegister\n");
  // A continuación se realiza la introducción de datos para registrar un paciente
  get_string(nombre,1,24,"Name");
  do
    {
      get_string(dni,9,9,"DNI");
    }while(verify_DNI(dni)==0);
  fecha=get_integer(1900,2020,"Date");
  fiebre=yes_or_no("Fever");
  tos=yes_or_no("Cough");
  sintoma=get_character("FSTMN","Symptom");
  // Una vez que todos los datos son correctos se guardan los datos del nuevo paciente resgistrado en la tabla de pacientes
  strcpy(p[*numPacientes].nombre,nombre);
  strcpy(p[*numPacientes].DNI,dni);
  p[*numPacientes].edad=fecha;
  p[*numPacientes].fiebre=fiebre;
  p[*numPacientes].tos=tos;
  p[*numPacientes].sintoma=sintoma;
  fprintf(stdout,"\nNew patient:\n");
  display_patient(p[*numPacientes]);
  (*numPacientes)++;
  return;
}

void p_search(struct patient *p,int numPacientes) // Función para buscar pacientes por su DNI
{
  char d[10];
  int ind=0, i;
  fprintf(stdout,"\nSearch\n");
  if (numPacientes==0) fprintf(stdout,"\nNo patients yet\n");
  else
    {
      get_string(d,9,9,"DNI"); // Se introduce el DNI del paciente que se desea buscar
      for(i=0;i<numPacientes;i++)
	{
	  // Se compara la cadena introducida con los DNI de la tabla de pacientes
	  if(strcmp(d,p[i].DNI)) continue;
	  else
	    {
	      ind=1;
	      break;
	    }
	}
      if(ind==1)
	{
	  fprintf(stdout,"\nPatient data:\n");
	  display_patient(p[i]); // Si se encuentra un DNI que coincida se muestra en pantalla los datos de dicho paciente
	}
      else fprintf(stdout,"\nUnknown patient\n");
    }
  return;
}

void p_discharge(struct patient *p,int *numPacientes) // Función para dar de baja a un paciente de la tabla de pacientes
{
  char d[10];
  int ind=0,i;
  fprintf(stdout,"\nDischarge\n");
  if (*numPacientes==0) fprintf(stdout,"\nNo patients yet\n");
  else
    {
      get_string(d,9,9,"DNI"); // Se introduce el DNI del paciente que se desea buscar
      for(i=0;i<*numPacientes;i++)
	{
	  // Se compara la cadena introducida con los DNI de la tabla de pacientes
	  if(strcmp(d,p[i].DNI)) continue;
	  else
	    {
	      ind=1;
	      break;
	    }
	}
      if(ind==1)
	{
	  // Si se encuentra un DNI igual al introducido se elimina el pacientes y la lista de pacientes se reduce
	  for(i=i+1;i<*numPacientes;i++)
	    {
	      p[i-1]=p[i];
	    }
	  (*numPacientes)--;
	  fprintf(stdout,"\nDischarged patient\n");
	}
      else fprintf(stdout,"\nUnknown patient\n");
    }
  return;
}

void p_list(struct patient *p,int numPacientes) // Función para mostrar una lista de los pacientes en función de su fecha de nacimiento
{
  int ind,i;
  fprintf(stdout,"\nList\n");
  if (numPacientes==0) fprintf(stdout,"\nNo patients yet\n");
  else
    {
      // Se introduce una fecha de nacimiento y se muestran los pacientes que hayan nacido antes de la fecha dada
      ind = get_integer(1900,2020,"Date");
      fprintf(stdout,"\nPatients born before %d:\n",ind);
      for(i=0;i<numPacientes;i++)
	{
	  if(ind>=p[i].edad) display_patient(p[i]);
	}
    }
  return;
}

void p_mark(struct patient *p,int numPacientes) // Función para indicar si un paciente es positivo
{
  int i;
  fprintf(stdout,"\nPositives\n");
  if (numPacientes==0) fprintf(stdout,"\nNo patients yet\n");
  else
    {
      // Si algún paciente tiene fiebre, tos y algún síntoma se muestra su información por pantalla
      fprintf(stdout,"\nPositive patients:\n");
      for(i=0;i<numPacientes;i++)
	{
	  if((p[i].fiebre==1)&&(p[i].tos==1)&&(p[i].sintoma!='N')) display_patient(p[i]);
	}
    }
  return;
}

int p_exit(struct patient *p,FILE *pa,int numPacientes) // Función para salir del programa
{
  int i;
  fprintf(stdout,"\nExit\n");
  // Se pide al usuario que confirme que desea salir del programa, en caso afirmativo se guarda la tabla de pacientes en el fichero correspondiente
  if(yes_or_no("Are you sure you want to exit the program?"))
    {
      pa = fopen("patients.txt","w");
      for(i=0;i<numPacientes;i++)
	{
	  fprintf(pa,"%s %s %d %d %d %c\n",p[i].nombre,p[i].DNI,p[i].edad,p[i].fiebre,p[i].tos,p[i].sintoma);
	}
      fclose(pa);
      return 1;
    }
  else return 0;
}
