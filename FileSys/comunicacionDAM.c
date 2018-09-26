#include<gs.h>
int socket;
t_log logger;

void recibirInstruccion(instruccionaMDJ *instruccion,int socket,t_log *logger){
	instruccion=malloc(sizeof(instruccionaMDJ));
	recibir(socket,logger,(void*)instruccion->cod,sizeof(operacionMDJ));
	switch(instruccion->cod){
	case VALIDARARCHIVO||CREARARCHIVO:
		recibirMensaje(socket,logger,instruccion->path);
		break;
	case OBTENERDATOS:
		recibirObtenerDatos(instruccion);
		break;
	case GUARDARDATOS:
		recibirCrearDatos(instruccion);
		break;
	}

}
void recibirObtenerDatos(t_log logger,instruccionaMDJ *instruccion){
	recibirMensaje(socket,logger,instruccion->path);
	recibir(socket,logger,(void*)&instruccion->offset,sizeof(off_t));
	recibir(socket,logger,(void*)&instruccion->tam,sizeof(size_t));


}
void recibirCrearArchivo(t_log logger,instruccionaMDJ *instruccion){
	recibirCrearArchivo(logger,instruccion);
	recibir(socket,logger,instruccion->buf,sizeof(char));
}
