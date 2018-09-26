#include <stdio.h>
#include <stdlib.h>
#include <gs.h>

int main(void) {
	t_log *loggerMDJ = log_create("MDJ.log", "mdj", 1,0);
	int serverMDJ = crear_server("127.0.0.1","8082",loggerMDJ);
	int conexion1 = esperandoUnaConexion(serverMDJ,loggerMDJ,1);
		char* bufferId1=malloc(10);
		int id1=recv(conexion1,bufferId1,10,MSG_WAITALL);
		printf("EL mensaje enviado por DAM es: %s",bufferId1);
		recepcionMensaje(id1,loggerMDJ,bufferId1);

		free(bufferId1);
		log_destroy(loggerMDJ);
	return EXIT_SUCCESS;
}
