#ifndef GESTION_SOCKETS_GS_H_
#define GESTION_SOCKETS_GS_H_
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<commons/log.h>
#include<netdb.h>
#include<unistd.h>
#include <pthread.h>

typedef struct{
	int id; //1999,2000 van a ser los id ejemplo
	int sizePayload; //el resto
	/*aca podriamos agregar un indicador de cuantos
	streams de datos se envian por ejemplo, si se envía un nombre y la edad
	entonces dataStreams seria igual a 2*/
} header;
void recepcionMensaje(int receiver,t_log*logger,char*mensaje);
void enviarMensaje(int socket_cliente,t_log *logger,char *mensaje);
void recibirMensaje(int socket_cliente,t_log *logger,char *mensaje);
void recibirHeaderYPayload(int socket_cliente,t_log *logger,char*bufferPayload);
void enviarHeaderYPayload(int socket_cliente,t_log*logger,char*mensaje,int protocolo);
void recibirHeader(int socket_cliente,t_log *logger);
int connect_to_server(char * ip, char * port,t_log *logger);
int crear_server(char * ip, char * port,t_log *logger);
int esperandoUnaConexion(int socket_servidor,t_log *logger,int numConexion);
void recibir(int socket_cliente,t_log *logger,void *dato ,size_t tamTipo);
void enviar(int socket_cliente,void *dato,t_log *logger,size_t tamdetipo);

#endif /* GESTION_SOCKETS_GS_H_ */
