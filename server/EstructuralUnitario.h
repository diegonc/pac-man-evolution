#ifndef __ESTRUCTURAL_H__
#define __ESTRUCTURAL_H__


#include "Comestible.h"
#include "../common/smart_pointer.h"
#include "Jugador.h"
#include "Direccion.h"

#define CASA_FANTASMA		1	
#define PASILLO				-1
#define SALIDA_PACMAN		0

class EstructuralUnitario{
		
	private:
	
		EstructuralUnitario(EstructuralUnitario &c);
	
		S_ptr<EstructuralUnitario> arriba;
		S_ptr<EstructuralUnitario> abajo;
		S_ptr<EstructuralUnitario> derecha;
		S_ptr<EstructuralUnitario> izquierda;
	
		Posicion posicion;
	
	public:
		static const char Casa_Fanstasma;
		static const char Pasillo;
		static const char Salida_Pacman;	
	
		
		typedef char Enum_Estructural;
	
		EstructuralUnitario(Posicion &p);	
	
		virtual ~EstructuralUnitario();
	
		virtual void ingresar(Jugador& jugador) = 0;
		
		virtual char get_tipo()=0;
	
		virtual S_ptr<Comestible> get_comida();
		
		void set_arriba(S_ptr<EstructuralUnitario> e);
		void set_abajo(S_ptr<EstructuralUnitario> e);
		void set_derecha(S_ptr<EstructuralUnitario> e);
		void set_izquierda(S_ptr<EstructuralUnitario> e);
			
		S_ptr<EstructuralUnitario> get_arriba();
		S_ptr<EstructuralUnitario> get_abajo();
		S_ptr<EstructuralUnitario> get_derecha();
		S_ptr<EstructuralUnitario> get_izquierda();
			
		S_ptr<EstructuralUnitario> get_vecino(Direccion &dir);
		
		void set_posicion(Posicion &p);
		
		Posicion& get_posicion();
	
};
#endif /*__ESTRUCTURAL_H__*/
