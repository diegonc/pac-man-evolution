#ifndef __ESTRUCTURAL_H__
#define __ESTRUCTURAL_H__


#include "Comestible.h"
#include "../common/smart_pointer.h"
#include "Jugador.h"
#include "Direccion.h"

class Estructural{
		
	private:
	
		Estructural(Estructural &c);
	
		S_ptr<Estructural> arriba;
		S_ptr<Estructural> abajo;
		S_ptr<Estructural> derecha;
		S_ptr<Estructural> izquierda;
	
		Posicion posicion;
	
	public:
		
		Estructural();	
	
		virtual ~Estructural();
	
		virtual void ingresar(Jugador& jugador) = 0;
		
		virtual int get_tipo()=0;
	
		virtual S_ptr<Comestible> get_comestible();
		
		void set_arriba(S_ptr<Estructural> e);
		void set_abajo(S_ptr<Estructural> e);
		void set_derecha(S_ptr<Estructural> e);
		void set_izquierda(S_ptr<Estructural> e);
			
		S_ptr<Estructural> get_arriba();
		S_ptr<Estructural> get_abajo();
		S_ptr<Estructural> get_derecha();
		S_ptr<Estructural> get_izquierda();
			
		S_ptr<Estructural> get_vecino(Direccion &dir);
		
		void set_posicion(Posicion &p);
		
		Posicion& get_posicion();
	
};
#endif /*__ESTRUCTURAL_H__*/
