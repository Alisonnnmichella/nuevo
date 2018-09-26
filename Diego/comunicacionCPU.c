#include <gs.h>

void comunicacionCPU(){

t_log *logger=log_create("diego.log","diego",1,LOG_LEVEL_INFO);
int servidor=crear_server("127.0.0.1","8001",logger);
int cliente= esperandoUnaConexion(servidor,logger,100);
enviarMensaje(cliente,logger,"dog");
close(cliente);
}
