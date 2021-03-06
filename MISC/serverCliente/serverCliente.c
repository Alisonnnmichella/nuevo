/*
 * serverCliente.c
 *
 * un server que taambien es cliente
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include "string.h"
#include <unistd.h>

void emptyString(char*);


int main(int argc, char *argv[])
{
     struct sockaddr_in direccionServidor;
     direccionServidor.sin_family= AF_INET;
     direccionServidor.sin_addr.s_addr =inet_addr("127.0.0.1");
     direccionServidor.sin_port = htons(9001);


     int servidor = socket(AF_INET,SOCK_STREAM,0);

     int activado=1;
     setsockopt(servidor,SOL_SOCKET,SO_REUSEADDR,&activado,sizeof(activado));
     //esto sirve para que no haya problemas al cerrar el socket y reabrirlo

int returnBind = bind(servidor,(struct sockaddr *)&direccionServidor,sizeof(direccionServidor));

     if(returnBind != 0){
    	 perror("fallo el bind");
    	 return 1;
     }

     printf("estoy escuchando\n");
     listen(servidor,100); //hasta 100 conexiones escucha

     struct sockaddr_in direccionCliente;
     unsigned int tamanoDireccion;

    char recibir[10];
	 printf("quiere aceptar conexiones como servidor?");
	 scanf("%s",recibir);
while(string_equals_ignore_case(recibir,"si")){

     int cliente = accept(servidor,(struct sockaddr *)&direccionCliente,&tamanoDireccion);

     printf("recibi una direccion de %d\n",cliente);
     char* buffer= malloc(4);

     while(string_equals_ignore_case(buffer,"endc")==0){

     emptyString(buffer);
     int bytesRecibidos= recv(cliente,buffer,4,0);

     if(bytesRecibidos<=0){
    	 printf("el cliente no figura como conectado o no me llegaron los bytes \n");
    	 return 1;
     }

     printf("dice: %s \n",buffer);

     }
     free(buffer);
     close(cliente);
     printf("quiere aceptar conexiones como servidor?");
     scanf("%s",recibir);
}// fin de comunicacion

printf("hora de ser cliente");

struct sockaddr_in direccionServidor2;
direccionServidor.sin_family= AF_INET;
direccionServidor.sin_addr.s_addr=inet_addr("127.0.0.1");
direccionServidor.sin_port=htons(9002);

int cliente= socket(AF_INET,SOCK_STREAM,0);

if(connect(cliente,(struct sockaddr *)&direccionServidor2,sizeof(direccionServidor2))!=0){
	perror("no se pudo conectar");
	return 1;
}

while(1){
char* buffer= malloc(100);
scanf("%s",buffer);
send(cliente,buffer,strlen(buffer),0);
free(buffer);
}













    	return 0;
}

void emptyString(char*string){

	for(int i=0;i < strlen(string);i++){
		string[i]= ' ';
	}
}

