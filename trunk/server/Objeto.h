#ifndef __OBJETO_H__
#define __OBJETO_H__

#include "Posicion.h"
#include "Personaje.h"
#include "ComestibleFactory.h"

class Objeto{
	
	public:
		typedef char Tipo_Objeto;
	
	private:
		Tipo_Objeto tipo;
		Posicion posicion;
	
	public:
		Objeto(Tipo_Objeto tipo, Posicion &pos){
			this->tipo = tipo;
			this->posicion = pos;
		}
		~Objeto(){}
		Posicion& get_posicion(){
			return this->posicion;
		}
		Tipo_Objeto get_tipo(){
			return this->tipo;
		}
};

#endif /*__OBJETO_H__*/
