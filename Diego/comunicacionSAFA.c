#include <gs.h>

void comunicacionSAFA(){
	t_log *logger=log_create("diego.log","diego",1,0);
	int cliente=connect_to_server("127.0.0.1","8000",logger);
	send(cliente,"DAM",4,0);
}
