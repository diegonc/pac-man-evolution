#include "OperacionInit.h"

#include "JugadorLocal.h"
OperacionInit::OperacionInit( S_ptr<MapaBajoNivel> m, bool esPac ){
		this->m = m ;
      this->esPac = esPac;
}
void OperacionInit::ejecutar(ModeloServidor &modelo){
		MundoBajoNivel& mundo = modelo.get_mundo();
		mundo.agregar_mapa( m );
		modelo.set_cargado();

		JugadorLocal::get_instancia()->set_pacman( esPac );
		/* Agrega un jugador temporario hasta el start. para que puede reconocer el nivel. 
		JugadorLocal::get_instancia()->set_id( 2<<16 );
		modelo. */
}
