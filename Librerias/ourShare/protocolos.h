/*
 * protocolos.h
 *
 *  Created on: 20 sep. 2018
 *      Author: utnso
 */

#ifndef PROTOCOLOS_H_
#define PROTOCOLOS_H_
typedef enum{
	VALIDARARCHIVO,
	CREARARCHIVO,
	OBTENERDATOS,
	GUARDARDATOS
}operacionMDJ;

typedef struct{
	operacionMDJ cod;
	char*path;
	off_t offset;
	size_t tam;
	void *buf;
}instruccionaMDJ;


#endif /* PROTOCOLOS_H_ */

