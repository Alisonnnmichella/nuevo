/*
 * cliente_socket.c
 *
 *  Created on: 10 sep. 2018
 *      Author: utnso
 */

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<readline/readline.h>
#include<readline/history.h>
void enviarMensaje(int socket_cliente,char *mensaje);
int main(){

	struct sockaddr_in direccionServidor;
	direccionServidor.sin_family=AF_INET;
	direccionServidor.sin_addr.s_addr=INADDR_ANY;
	direccionServidor.sin_port=htons(8080);
	int cliente= socket(AF_INET,SOCK_STREAM,0);
	if(connect(cliente,(struct sockaddr*)&direccionServidor,sizeof(direccionServidor))!=0){
		perror("No se pudo conectar");
		return 1;
	}
	char rec[1000];
	int receptor;
	if((receptor=recv(cliente,rec,999,0))<0){
		perror("No se pudo recibir el mensaje");
	    return 1;
	}
	rec[receptor]='\0';
	printf("Mensaje de bienvenida %s\n",rec);
	printf("\nIngrese el mensaje a enviar al servidor! \n");

	char *mensaje=readline("");
	enviarMensaje(cliente,mensaje);
	return 0;


}

void enviarMensaje(int socket_cliente,char *mensaje){
	printf("\n%s\n",mensaje);
	int tamanio_Mens= strlen(mensaje) +1;
	void *buffer=malloc(4+tamanio_Mens*sizeof(char));
	memcpy(buffer,(void *)&tamanio_Mens,4);
	memcpy(buffer+4,mensaje,tamanio_Mens*sizeof(char));
	//come on come on turn the radio on its operativos
	int r=send(socket_cliente,buffer,4+tamanio_Mens*sizeof(char),0);
	if(r<0)
		printf("error!");
	printf("\nCharacters send %d",r);
	free(buffer);
}

