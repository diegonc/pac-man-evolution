#include "OperacionInit.h"

#include "JugadorLocal.h"
#include "BufferMensajes.h"

OperacionInit::OperacionInit( MapaBajoNivel* m, bool esPac ){
		this->m = m ;
      this->esPac = esPac;
}
void OperacionInit::ejecutar(ModeloCommon &modelo){
		MundoBajoNivel& mundo = modelo.get_mundo();
		mundo.pasar_de_nivel();
		mundo.agregar_mapa( m );
		modelo.set_cargado();

		JugadorLocal::get_instancia()->set_pacman( esPac );
		BufferMensajes::get_instancia()->add_mensaje_critico("Cambiando de Nivel");
}
