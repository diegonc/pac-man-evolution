#include "OperacionMensaje.h"


OperacionMensaje::OperacionMensaje( std::string Mensaje ){
	this->Mensaje = Mensaje ;
}
void OperacionMensaje::ejecutar(ModeloCommon &modelo) {
	//les manda a todos
//	std::cout << "Me llego este mensaje" << Mensaje << "\n";
	S_ptr<Paquete> paqueteMens(new PaqueteMensaje(Mensaje));
	MessageDispatcher::get_instancia()->dispatch_message(paqueteMens);
	//creo paqueteMensaje(Mensaje) y les mando a todos
}
