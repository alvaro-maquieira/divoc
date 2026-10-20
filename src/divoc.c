#include <stdio.h>
#include "database.h"
#include "inout.h"

int main()
{
  struct patient paciente[256];
  int numPacientes=0;
  FILE *patients;
  char cadena[256];
  int ind,i;
  // Se lee el fichero. Si existe se copian los pacientes a la tabla de pacientes y se cierra el fichero
  if((patients = fopen("patients.txt","r"))!=NULL)
    {
      for(i=0;fgets(cadena,sizeof(cadena),patients)!=NULL;i++)
	{
	  sscanf(cadena,"%s%s%d%d%d %c",paciente[i].nombre,paciente[i].DNI,&paciente[i].edad,&paciente[i].fiebre,&paciente[i].tos,&paciente[i].sintoma);
	  numPacientes++;
	}
      fclose(patients);
    }
  // Se realiza la carátula
  stripe('-');
  headline("DIVOC_",'|');
  stripe('-');
  do
    {
      // Se muestran por pantalla las opciones del menú
      fprintf(stdout,"\n\nR) Register a patient\n");
      fprintf(stdout,"S) Search for a patient\n");
      fprintf(stdout,"D) Discharge a patient\n");
      fprintf(stdout,"L) List patients by age\n");
      fprintf(stdout,"P) Mark positive\n");
      fprintf(stdout,"\nX) Exit the program\n");
      switch(get_character("RSDLPX","Choose an option"))
	{
	case 'R':
	  p_register(paciente,&numPacientes); // Se llama a la función p_register para registrar un paciente
	  break;

	case 'S':
	  p_search(paciente,numPacientes); // Se llama a la función p_search para buscar un paciente
	  break;

	case 'D':
	  p_discharge(paciente,&numPacientes); // Se llama a la función p_discharge para dar de baja un paciente
	  break;

	case 'L':
	  p_list(paciente,numPacientes); // Se llama a la función p_list para mostrar una lista de pacientes en base a su año de nacimiento
	  break;

	case 'P':
	  p_mark(paciente,numPacientes); // Se llama a la función p_mark para mostrar los pacientes que son positivos
	  break;

	case 'X':
	  ind = p_exit(paciente,patients,numPacientes); // Se llama a la función p_exit para salir del programa
	  break;
	}
    }while(ind==0);
  return 0;
}
