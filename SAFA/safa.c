#include <gs.h>
#include <pthread.h>
#include <sys/select.h>

int seConectaronElDamYUnCpu(int, int, char*, char*, t_log*);

//ip "192.168.1.2"
//puerto 8000
//pero usamos loop

int main(int argc, char *argv[]) {

	t_log* logger = log_create("SAFA.log", "safa", 1, 0);
	log_info(logger, "SAFA: corrupto");
	int serverSAFA = crear_server("127.0.0.1", "8000", logger);

	int conexion1 = esperandoUnaConexion(serverSAFA, logger, 1);
	char* bufferId1 = malloc(4);
	int id1 = recv(conexion1, bufferId1, 4, MSG_WAITALL);
	recepcionMensaje(id1, logger, bufferId1);

	int conexion2 = esperandoUnaConexion(serverSAFA, logger, 2);
	char* bufferId2 = malloc(4);
	int id2 = recv(conexion2, bufferId2, 4, MSG_WAITALL);
	recepcionMensaje(id2, logger, bufferId2);

	/*validacion safa es una variable que representa si se realizo la conexion inicial
	 y ademas que conexion es diego*/

	int validacionSAFA = seConectaronElDamYUnCpu(conexion1, conexion2,
			bufferId1, bufferId2, logger);

	free(bufferId2);
	free(bufferId1);

	if (validacionSAFA > 0) {
		log_info(logger, "SAFA: operativo");
	} else {
		log_error(logger, "No se pudo salir del estado corrupto");
	}
	log_destroy(logger);
	return 0;
}

