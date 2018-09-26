#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <commons/string.h>

void main() {
	char * linea;
	while (1) {
		linea = readline(">>");

		if (linea)
			add_history(linea);

		if (!strcmp(linea, "ls")) {
			printf("Aca estan los archivos xd  \n");
		}
		if (!strncmp(linea, "ejecutar", 8)) {
			printf("ejecutando el archivo %s\n",
					string_substring_from(linea, 9));
			//aca empieza un fopen
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
			break;
		}
		free(linea);
	}
}
/* ESTO HAY QUE RECONOCER:
 ejecutar
 status
 finalizar
 metricas*/
