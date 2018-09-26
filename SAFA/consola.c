
#include "planificadores.h"

extern sem_t  sem_plp;
extern sem_t sem_liberar_dir;
extern char* dirEscript;

int salida =0;

void consola() {
	char * linea;
	char * path;

	while (1) {
		linea = readline(">>");

		if (linea)
			add_history(linea);

		if (!strcmp(linea, "ls")) {
			printf("Aca estan los archivos  \n");
		}

		if (!strncmp(linea, "ejecutar ", 9)) {
			path = string_substring_from(linea, 9);
			string_trim(&path);  //Para poder hacer el if siguiente
			if (!strcmp(path, "")) {
				printf(
						"Ejecutar toma como parametro un archivo a ejecutar. Por ejemplo: ejecutar archivo\n");
			} else {
				printf("Ejecutando el archivo en %s...\n", path); //Cambiar esto en el futuro, se va a pasar path no el nombre del archivo

					dirEscript = malloc(strlen(path)+1);
						memcpy(dirEscript,path,strlen(path)+1);
							free(path);

					sem_post(&sem_plp);

					sem_wait(&sem_liberar_dir);
					//Aca se manda a crear el DTB
			}
		}


	if (!strcmp(linea, "status")) {
		printf("stus\n");
	}
	if (!strcmp(linea, "finalizar")) {
		printf("fin\n");
	}
	if (!strcmp(linea, "metricas")) {
		printf("metri\n");
	}

	if (!strcmp(linea, "clear")) {
		system("clear");
	}

	if (!strcmp(linea, "exit")) {
		free(linea);
		salida = 1;
		sem_post(&sem_plp);
		sleep(1);
		return;
	}
	free(linea);
}
}

/* ESTO HAY QUE RECONOCER:
 ejecutar
 status
 finalizar
 metricas*/
