#include "PaqueteMensaje.h"

PaqueteMensaje::PaqueteMensaje(std::string Mensaje):PaqueteMensajeCommon(){
	this->Mensaje=Mensaje;
}

PaqueteMensaje::PaqueteMensaje():PaqueteMensajeCommon(){
}

Operacion * PaqueteMensaje::get_operacion(){
	return new OperacionMensaje(Mensaje);
}
