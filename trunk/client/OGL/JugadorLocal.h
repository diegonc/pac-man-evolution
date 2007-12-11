#ifndef JUGADOR_LOCAL_H
#define JUGADOR_LOCAL_H

#include "../../common/smart_pointer.h"

class JugadorLocal{
	private:
		JugadorLocal();
	
		JugadorLocal(JugadorLocal &j);
	
		static S_ptr<JugadorLocal> instancia;
		
		int id;
	
	public:
		
		static S_ptr<JugadorLocal> get_instancia();
	
		void set_id(int id_jugador);
	
		int get_id();
	
		
};

#endif /*JUGADOR_LOCAL_H*/
