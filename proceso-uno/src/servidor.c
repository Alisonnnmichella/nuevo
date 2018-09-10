/*
 * servidor.c
 *
 *  Created on: 10 sep. 2018
 *      Author: utnso
 */


#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
void recibirMensaje(int socket_cliente);
void comprobarMensajesRecibidos(int bytes_recibidos);
int main(void){
	struct sockaddr_in direccionServidor;
	struct sockaddr_in direccionCliente;
	direccionServidor.sin_family=AF_INET;
	direccionServidor.sin_port=htons(8080);
	direccionServidor.sin_addr.s_addr=INADDR_ANY;

	int servidor= socket(AF_INET,SOCK_STREAM,0);
	int activado=1;
	setsockopt(servidor,SOL_SOCKET,SO_REUSEADDR,&activado,sizeof(activado)	);
	if(bind(servidor,(struct sockaddr*)&direccionServidor,sizeof(struct sockaddr))!=0){
		perror("Fallo el bind");
		return 1;
	}
	printf("Estoy escuchando\n");

	listen(servidor,100);
	int sin_size=sizeof(struct sockaddr_in);

	int cliente= accept(servidor,(struct sockaddr*)&direccionCliente,&sin_size);
	if(cliente<1){
		perror("Fallo el accept()");
		return 1;
	}
	printf("Recibi una conexion en %d !!\n", cliente);
	int len,bytes_sent;
	//----Envio un mensaje al cliente
	char msg[]="Come on everybody everybody\n";
	len=strlen(msg);
	bytes_sent=send(cliente,msg,len,0);
	if(bytes_sent<0){
		printf("No se envio un carajo.");
	}
	//--------------------
	recibirMensaje(cliente);

return 0;

}
void recibirMensaje(int socket_cliente){
	printf("Recibiendo...");
	size_t tamanioMens;
	int bytes_recibidos= recv(socket_cliente,&tamanioMens,4,0);
	if(bytes_recibidos<0){
		perror("Fallo");
		exit(1);
			}
	char *mensaje= malloc(tamanioMens);
	printf("Tamaño del mensaje %d\n",tamanioMens);
	bytes_recibidos=recv(socket_cliente,mensaje,tamanioMens,MSG_WAITALL);
	printf("\n%s\n",mensaje);

}
