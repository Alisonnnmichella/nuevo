#include"gs.h"
void exit_gracefully(t_log *log,int return_nr){
	log_destroy(log);
	exit(return_nr);
}
void exit_with_error(t_log *log,int socket,char *error_msg,void *buffer){
	if(buffer!=NULL){
		free(buffer);
	}
	log_error(log,error_msg);
	close(socket);
	exit_gracefully(log,1);
}
void recepcionMensaje(int receiver,t_log*logger,char*mensaje){
	if (receiver<0){
		log_error(logger,"no se pudo recibir el mensaje");
	}
	else {log_info(logger,"mensaje recibido %s",mensaje);}
}





void enviarMensaje(int socket_cliente,t_log *logger,char *mensaje){
	int tamanio_Mens= strlen(mensaje) +1;
	void *buffer=malloc(4+tamanio_Mens*sizeof(char));
	memcpy(buffer,(void *)&tamanio_Mens,4);
	memcpy(buffer+4,mensaje,tamanio_Mens*sizeof(char));
	int r=send(socket_cliente,buffer,4+tamanio_Mens*sizeof(char),0);
	if(r<0)
		printf("error!");
	free(buffer);
}

void recibirMensaje(int socket_cliente,t_log *logger){
	printf("Recibiendo...\n");
	size_t tamanioMens;
	int bytes_recibidos= recv(socket_cliente,&tamanioMens,4,0);
	if(bytes_recibidos<0){
		perror("Fallo");
		exit(1);
	}
	char *mensaje= malloc(tamanioMens);
	bytes_recibidos=recv(socket_cliente,mensaje,tamanioMens,MSG_WAITALL);
	printf("\n%s\n",mensaje);
	free(mensaje);
}
void recibirHeaderYPayload(int socket_cliente,t_log *logger,char*bufferPayload){
	printf("recibiendo header...\n"); //envio de header
	header* mensaje=malloc(sizeof(header));
	if(recv(socket_cliente,mensaje,sizeof(header),MSG_WAITALL)<0){
		exit_with_error(logger,socket_cliente,"No se pudo recibir el enunciado",mensaje);
	}
	int handshakeHeader=send(socket_cliente,"1",1,0);//handshake 1 "recibido"
	if(handshakeHeader<0)
		exit_with_error(logger,socket_cliente,"No se pudo enviar handshake",mensaje);

	bufferPayload=malloc(sizeof(char)*(mensaje->sizePayload)); //reservo tamanio payload
	int bytes_recibidos_payload=recv(socket_cliente,&bufferPayload,mensaje->sizePayload,MSG_WAITALL);
	if(bytes_recibidos_payload<0){
		free(bufferPayload);
		exit_with_error(logger,socket_cliente,"No se pudo recibir el enunciado",mensaje);
	}
	int handshakePayload=send(socket_cliente,"1",1,0);// handshake 1 "recibido"
	if(handshakePayload<0)
				printf("error, no se recibio el handshake header");

	free(mensaje);
}
void enviarHeaderYPayload(int socket_cliente,t_log*logger,char*mensaje,int protocolo){
	//enviar header
	header*encabezado=malloc(sizeof(header));
	encabezado->id= protocolo;
	encabezado->sizePayload=strlen(mensaje)+1;
	int enviarHeader=send(socket_cliente,encabezado,sizeof(encabezado),0);
	if(enviarHeader<0)
		exit_with_error(logger,socket_cliente,"No se pudo recibir enviar",encabezado);
	//recibir handshake header
	char* bufferHandshakeHeader=malloc(sizeof(char));
	int recibirHandshakeHeader=recv(socket_cliente,bufferHandshakeHeader,1,MSG_WAITALL);
	if(recibirHandshakeHeader<0)
		exit_with_error(logger,socket_cliente,"Problemas en hand-shake",encabezado);
	//enviar payload
	int enviarPayload=send(socket_cliente,mensaje,strlen(mensaje)+1,0);
	if(enviarPayload<0)
		exit_with_error(logger,socket_cliente,"Error no se pudo enviar el payload",encabezado);
	//recibir handshakePayload
	char* bufferHandshakePayload=malloc(sizeof(char));
	int recibirHandshakePayload=recv(socket_cliente,bufferHandshakePayload,1,MSG_WAITALL);
	if(recibirHandshakePayload<0)
		exit_with_error(logger,socket_cliente,"Error, no se recibio el handshake payload",encabezado);
	free(bufferHandshakeHeader);
	free(bufferHandshakePayload);
}


int esperandoUnaConexion(int socket_servidor,t_log *logger,int numConexion){
	struct sockaddr cliente_tam;
	unsigned int sin_size=sizeof(struct sockaddr_in);
	int cliente=accept(socket_servidor,&cliente_tam,&sin_size);
	if(cliente<0){
			log_info(logger, "ERROR No se pudo aceptar la conexion %d",numConexion);
			exit(1);
		}
	log_info(logger, "Se acepto la conexion %d",numConexion);
	return cliente;
}
int connect_to_server(char * ip, char * port,t_log *logger) {
  struct addrinfo hints;
  struct addrinfo *server_info;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  getaddrinfo(ip, port, &hints, &server_info);
  int server_socket = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);
  int res = connect(server_socket, server_info->ai_addr, server_info->ai_addrlen);

  freeaddrinfo(server_info);
  if (res < 0) {
    perror("No se pudo conectar al servidor");
    exit(1);
  }
  log_info(logger, "Conectado!");
  return server_socket;
}

int crear_server(char * ip, char * port,t_log *logger) {
  struct addrinfo hints;
  struct addrinfo *server_info;
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  int a=getaddrinfo(ip, port, &hints, &server_info);
  if(a<0){
	  perror("Error");
	  log_info(logger,"No se pudo usar la estructura");
	  exit(1);
  }
  int server_socket = socket(server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol);
  int res = bind(server_socket, server_info->ai_addr, server_info->ai_addrlen);
  freeaddrinfo(server_info);
  if (res < 0) {
	  perror("No se pudo bindear");
	  exit(1);
    //_exit_with_error(server_socket, "No se puedo bindear", NULL);
  }
  log_info(logger, "Bindeado!");
  int activado=1;
  setsockopt(server_socket,SOL_SOCKET,SO_REUSEADDR,&activado,sizeof(activado));
  listen(server_socket,1000);
  return server_socket;
}
