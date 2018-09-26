#include "planificadores.h"

extern sem_t sem_plp;
extern sem_t sem_liberar_dir;
extern char* dirEscript;

extern int salida;


typedef struct{
	int ID;
	char*path;
	int PC;
	int FlagInic; //Incompleto, agregar mas
}DTB;

void plp(){

	int codigo=1560;

	while (1){

	sem_wait(&sem_plp);

	if(salida!=1){

	DTB*bloque=malloc(sizeof(DTB));

	bloque->path=malloc(strlen(dirEscript)+1);
	strcpy(bloque->path,dirEscript);

	free(dirEscript);

	bloque->ID = codigo;

	printf("el id es %d \n",bloque->ID);
	printf("el path es %s \n",bloque->path);

	free(bloque->path);
	free(bloque);

	sem_post(&sem_liberar_dir);

	codigo++;
	}else {break;}
	}
}

