#ifndef __CASILLERO_H__
#define __CASILLERO_H__


#include "Comestible.h"
#include "../common/smart_pointer.h"
#include "Jugador.h"

class Casillero{
		
	private:
	
		Casillero(Casillero &c);
	
		S_ptr<Casillero> arriba;
	
		S_ptr<Casillero> abajo;
		
		S_ptr<Casillero> derecha;
	
		S_ptr<Casillero> izquierda;
		
	public:
		
		Casillero();	
	
		virtual ~Casillero();
	
		virtual void ingresar(Jugador *jugador) = 0;
			
			
		void set_arriba(S_ptr<Casillero> casillero);
			
		void set_abajo(S_ptr<Casillero> casillero);
			
		void set_derecha(S_ptr<Casillero> casillero);
			
		void set_izquierda(S_ptr<Casillero> casillero);
			
		S_ptr<Casillero> get_arriba();
		
		S_ptr<Casillero> get_abajo();
			
		S_ptr<Casillero> get_derecha();
			
		S_ptr<Casillero> get_izquierda();
	
};
#endif /*__CASILLERO_H__*/
