#include "OperacionStart.h"

#include "JugadorLocal.h"
#include "../common/PacMan.h"
#include "../common/Fantasma.h"

OperacionStart::OperacionStart( int id ){
	this->id = id ;
}
void OperacionStart::ejecutar(ModeloServidor &modelo) {

   bool pac = JugadorLocal::get_instancia()->get_pacman();
	JugadorLocal::get_instancia()->set_id( id );
	Jugador* j = new Jugador( id );
	Personaje* p;
	if( pac )
		p = new PacMan( j );
	else
		p = new Fantasma( j );
	j->set_personaje( p );
	modelo.agregar_jugador(  j );

}
