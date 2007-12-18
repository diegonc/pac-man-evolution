#include "OperacionMensaje.h"

#include "BufferMensajes.h"

OperacionMensaje::OperacionMensaje( std::string Mensaje ){
	this->Mensaje = Mensaje ;
}
void OperacionMensaje::ejecutar(ModeloCommon &modelo) {
	BufferMensajes::get_instancia()->add_mensaje(Mensaje);
}
