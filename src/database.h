struct patient{
  char nombre[25];
  char DNI[10];
  int edad;
  int fiebre;
  int tos;
  char sintoma;};

void p_register(struct patient *p,int *numPacientes);
void p_search(struct patient *p,int numPacientes);
void p_discharge(struct patient *p,int *numPacientes);
void p_list(struct patient *p,int numPacientes);
void p_mark(struct patient *p,int numPacientes);
int p_exit(struct patient *p,FILE *pa,int numPacientes);
