#include "OperacionMensaje.h"


OperacionMensaje::OperacionMensaje( std::string Mensaje ){
	this->Mensaje = Mensaje ;
}
void OperacionMensaje::ejecutar(ModeloCommon &modelo) {
	S_ptr<Paquete> paqueteMens(new PaqueteMensaje(Mensaje));
	MessageDispatcher::get_instancia()->dispatch_message(paqueteMens);

}
