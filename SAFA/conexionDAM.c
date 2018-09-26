#include <gs.h>
#include <commons/log.h>
void conexionDAM(){

	t_log *logger=log_create("comSAFA.log","SAFA",true,LOG_LEVEL_INFO);
	int servidor=crear_server("127.0.0.1","8000",logger);
	int cliente= esperandoUnaConexion(servidor,logger,100);
	recibirMensaje(cliente,logger);
	close(cliente);
}
