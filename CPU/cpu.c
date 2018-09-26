#include <gs.h>


int main(){
	t_log* logger = log_create("cpu.log","cpu",1,0);
	int cliente=connect_to_server("127.0.0.1","8000",logger); ;
	send(cliente,"CPU",4,0);

	return 0;
}


