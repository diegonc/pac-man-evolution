#include "OperacionStart.h"

#include "JugadorLocal.h"
#include "BufferMensajes.h"
#include "../common/PacMan.h"
#include "../common/Fantasma.h"

OperacionStart::OperacionStart( int id ){
	this->id = id ;
}
void OperacionStart::ejecutar(ModeloCommon &modelo) {
	BufferMensajes::get_instancia()->add_mensaje_critico("Comenzando Partida!");

	bool pac = JugadorLocal::get_instancia()->get_pacman();

	JugadorLocal::get_instancia()->set_id( id );
	Jugador* j;

	j=ModeloServidor::get_instancia()->get_jugador(id);

	Personaje* p;
	if (j!=NULL){		
		
		if( pac )
			p = new PacMan( j );
		else
			p = new Fantasma( j );
		j->set_personaje( p );
		ModeloServidor::get_instancia()->preparar_partida();
	}else{
		j = new Jugador( id );		
		if( pac )
			p = new PacMan( j );
		else
			p = new Fantasma( j );
		j->set_personaje( p );
		modelo.agregar_jugador(  j );
	}
}
