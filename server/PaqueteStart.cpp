#include "PaqueteStart.h"
#include "Operacion.h"
#include "MundoBajoNivel.h"
#include "PacMan.h"
#include "Fantasma.h"
#include "Personaje.h"
#include "Jugador.h"

#ifdef PROGRAMA_CLIENTE
#include "../client/OGL/JugadorLocal.h"
#endif

namespace {
	const int ID = 1;

	class OperacionStart : public Operacion
	{
		private:
			int id;

		public:
			OperacionStart( int id ) : id( id ) { }

			void ejecutar(ModeloServidor &modelo) {
#ifdef PROGRAMA_CLIENTE
				bool pac = JugadorLocal::get_instancia()->get_pacman();
				JugadorLocal::get_instancia()->set_id( id );
				Jugador* j = new Jugador( id );
				Personaje* p;
				if( pac )
				       p = new PacMan( j );
				else
					p = new Fantasma( j );
				j->set_personaje( S_ptr<Personaje>( p ) );
				modelo.agregar_jugador( S_ptr<Jugador>( j ) );
#endif
			}
	};

}

PaqueteStart::PaqueteStart() : Paquete( ID )
{
}

PaqueteStart::PaqueteStart(int id_cliente):Paquete( ID ){
	this->id_cliente = id_cliente;
}

void PaqueteStart::serialize( OutputBitStream& bs ){
	Paquete::serialize( bs );
	bs.skip();
	
	bs.append(16,id_cliente);
}

void PaqueteStart::deserialize( InputBitStream& bs ) {
	bs.skip(); // Campo auxiliar no utilizado.
	id_cliente = bs.read( 16 );
}

Operacion * PaqueteStart::get_operacion(){
	return new OperacionStart( id_cliente );
}
