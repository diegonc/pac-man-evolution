#ifndef __OBJETO_H__
#define __OBJETO_H__

#include "Posicion.h"
#include "Personaje.h"
#include "Direccion.h"
#include "ComestibleFactory.h"

class Objeto{
	
	public:
		typedef char Tipo_Objeto;
	
	private:
		Tipo_Objeto tipo;
		Posicion posicion;
		Direccion orientacion();
	
	public:
		Objeto(Tipo_Objeto tipo, Posicion &pos, Direccion& orientacion){
			this->tipo = tipo;
			this->posicion = pos;
			//this->orientacion = orientacion;
		}
		~Objeto(){}
		Posicion& get_posicion(){
			return this->posicion;
		}
		Tipo_Objeto get_tipo(){
			return this->tipo;
		}
		/*Direccion& get_orientacion(){
			return this->orientacion;
		}*/
		
};

#endif /*__OBJETO_H__*/
