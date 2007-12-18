#ifndef JUGADOR_LOCAL_H
#define JUGADOR_LOCAL_H

#include "../common/smart_pointer.h"

class JugadorLocal{
	private:
		JugadorLocal();
	
		JugadorLocal(JugadorLocal &j);
	
		static S_ptr<JugadorLocal> instancia;
		
		unsigned int id;

		bool esPacman;
	
	public:
		
		static S_ptr<JugadorLocal> get_instancia();
	
		void set_id(unsigned int id_jugador);

		void set_pacman( bool p );

		bool get_pacman();
	
		unsigned int get_id();
		
};

#endif /*JUGADOR_LOCAL_H*/
