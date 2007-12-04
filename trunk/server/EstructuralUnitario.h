#ifndef __ESTRUCTURAL_H__
#define __ESTRUCTURAL_H__


#include "Comestible.h"
#include "../common/smart_pointer.h"
#include "Jugador.h"
#include "Direccion.h"

#define _CASA_FANTASMA		1	
#define _PASILLO				-1
#define _SALIDA_PACMAN		0

class EstructuralUnitario{
		
	private:
	
		EstructuralUnitario(EstructuralUnitario &c);
	
		S_ptr<EstructuralUnitario> arriba;
		S_ptr<EstructuralUnitario> abajo;
		S_ptr<EstructuralUnitario> derecha;
		S_ptr<EstructuralUnitario> izquierda;
	
		Posicion posicion;
	
	public:
		
		typedef const char Enum_Estructural;
	
		static Enum_Estructural Casa_Fanstasma;
		static Enum_Estructural Pasillo;
		static Enum_Estructural Salida_Pacman;	
		
		EstructuralUnitario(Posicion &p);	
	
		virtual ~EstructuralUnitario();
	
		virtual void ingresar(Jugador& jugador) = 0;
		
		virtual EstructuralUnitario::Enum_Estructural get_tipo()=0;
	
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
		
		virtual bool es_salida_pacman();
		
		virtual bool es_casa_fantasma();
	
};
#endif /*__ESTRUCTURAL_H__*/
