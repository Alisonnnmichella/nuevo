#include<gs.h>
#include<string.h>

void enviarInstruccion(instruccionaMDJ *instruccion,int socket,t_log logger){
	enviar(socket,instruccion->cod,logger,sizeof(int));
	if(instruccion->cod==VALIDARARCHIVO||instruccion->cod==CREARARCHIVO){

		enviarMensaje(socket,logger,instruccion->path);

	}
	else if(instruccion->cod==OBTENERDATOS || instruccion->cod==GUARDARDATOS){

		void* buffer=malloc(4+sizeof(char)*(strlen(instruccion->path)+1)+sizeof(off_t)+sizeof(instruccion->buf));
		size_t sizepath= sizeof(char)*(1+strlen(instruccion->path));
		memcpy(buffer,(void*)&sizepath,4);
		memcpy(buffer+4,(void*)instruccion->path,sizepath);
		memcpy(buffer+4+sizepath,(void*)instruccion->offset,sizeof(off_t));
		memcpy(buffer+4+sizepath+sizeof(off_t),(void*)instruccion->tam,sizeof(size_t));
		if(instruccion->cod==OBTENERDATOS)
			send(socket,buffer,buffer+4+sizepath+sizeof(off_t),0);
		if(instruccion->cod==GUARDARDATOS){
		memcpy(buffer+4+sizepath+sizeof(off_t)+sizeof(size_t),instruccion->buf,sizeof(instruccion->buf));
			send(socket,buffer,buffer+4+sizepath+sizeof(off_t)+sizeof(instruccion->buf),0);
		}
	}
	free(instruccion->path);
	free(instruccion->buf);
	free(instruccion);
}

