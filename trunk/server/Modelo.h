#ifndef __MODELO_H__
#define __MODELO_H__

#include "../common/thread.h"
#include "../common/smart_pointer.h"
#include "MundoBasicImp.h"
#include <string>
#include <list>
#include "Jugador.h"

/** @brief Esta clase define el modelo.
		   Hereda de thread, ya que se debe actualizar automaticamente todo
		   el tiempo.
 */

class Modelo : public Thread{
	typedef S_ptr<Jugador> Tipo_Jugador;
	
	private:
		Mundo * mundo;
	
		std::list<Tipo_Jugador> jugadores;
		
		Modelo(Modelo &m);
		
		void cargar_modelo(std::string ruta_mundo);
	
	public:
		
		Modelo(std::string ruta_mundo);

		~Modelo();	
	
		void agregar_jugador(Tipo_Jugador jugador);
			
		void run();
	
	
};


#endif /*__MODELO_H__*/
