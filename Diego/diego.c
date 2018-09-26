#include <gs.h>
#include <pthread.h>

//void comunicacionCPU();
void comunicacionSAFA();

//ip y puerto de escucha "127.0.0.1""8001"
int main(int argc, char *argv[]){
	//pthread_t comCPU;
	pthread_t comSAFA;

	//pthread_create(&comCPU, NULL,(void *)comunicacionCPU, NULL);
	pthread_create(&comSAFA, NULL,(void *)comunicacionSAFA, NULL);

	//pthread_detach(comCPU);
	pthread_detach(comSAFA);
	//AGREGADO PARA EL HITO 1 POR FRANCISCO: DAM debe reenviar msj a MDJ o FM9
	/*
	t_log *loggerDAM = log_create("DIEGO.log", "diego", 1,0);
	int clienteDAM = connect_to_server("127.0.0.1","8082",loggerDAM);
	enviarMensaje(clienteDAM, loggerDAM, "Ehhhh MDJ");
	log_destroy(loggerDAM);
	close(clienteDAM);
	*/
	while (1){
	}

	return 0;
}
/*
 g.dt
 es generado por un scrip escritorio

 */
