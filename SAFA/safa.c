#include <gs.h>
#include <pthread.h>
#include <sys/select.h>
#include <semaphore.h>
#include "planificadores.h"


int seConectaronElDamYUnCpu(int, int, char*, char*, t_log*);

//variables globales
sem_t sem_plp;
sem_t sem_liberar_dir;
char* dirEscript;


//ip "192.168.1.2"
//puerto 8000
//pero usamos loop


int main(int argc, char *argv[]) {

/*
	t_log* logger = log_create("SAFA.log", "safa", 1, 0);
	log_info(logger, "SAFA: corrupto");
	int serverSAFA = crear_server("127.0.0.1", "8000", logger);

int conexion1 = esperandoUnaConexion(serverSAFA,logger,1);
	char* bufferId1=malloc(4);
		int id1=recv(conexion1,bufferId1,4,MSG_WAITALL);
			recepcionMensaje(id1,logger,bufferId1);

int conexion2 = esperandoUnaConexion(serverSAFA,logger,2);
	char* bufferId2=malloc(4);
		int id2=recv(conexion2,bufferId2,4,MSG_WAITALL);
			recepcionMensaje(id2,logger,bufferId2);

*/
	/*validacion safa es una variable que representa si se realizo la conexion inicial
	 y ademas que conexion es diego*/
/*
int validacionSAFA = seConectaronElDamYUnCpu(conexion1, conexion2,
			bufferId1, bufferId2, logger);

free(bufferId2);
free(bufferId1);

if(validacionSAFA>0){
	log_info(logger,"SAFA: operativo");
	//En esta parte se va a ejecutar el programa entero Safa
*/

sem_init(&sem_plp,0,0);
sem_init(&sem_liberar_dir,0,0);

pthread_t h_plp;
pthread_t h_pcp;
pthread_t h_consola;

pthread_create(&h_plp,NULL,(void *)plp,NULL);
pthread_create(&h_pcp,NULL,(void *)pcp,NULL);
pthread_create(&h_consola,NULL,(void *)consola,NULL);

pthread_detach(h_plp);
pthread_detach(h_pcp);
pthread_join(h_consola,NULL);

/*
}
else{
	log_error(logger,"No se pudo salir del estado corrupto");
}*/

return 1;
}
