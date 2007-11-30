#ifndef __MODELO_H__
#define __MODELO_H__

#include "../common/thread.h"
#include "../common/smart_pointer.h"
#include "MundoBasicImp.h"
#include <string>
#include <list>
#include "Jugador.h"
#include "Objeto.h"
#include "EstructuralUnitario.h"

/** @brief Esta clase define el modelo.
		   Hereda de thread, ya que se debe actualizar automaticamente todo
		   el tiempo.
 */

class ModeloServidor : public Thread{
	typedef S_ptr<Jugador> Tipo_Jugador;
	
	private:
		Mundo * mundo;
	
		std::list<Tipo_Jugador> jugadores;
		
		ModeloServidor(ModeloServidor &m);
		
		void cargar_modelo(std::string ruta_mundo);
	
	public:
		
		ModeloServidor(std::string ruta_mundo);

		~ModeloServidor();	
	
		void agregar_jugador(Tipo_Jugador jugador);
			
		void run();
	
		std::list<S_ptr<Objeto> > get_objetos();
	
		Mundo& get_mundo();
	
		S_ptr<Jugador> get_jugador(int id);
	
		const std::list<S_ptr<Jugador> >& get_jugadores();
	
		void revisar_colisiones(S_ptr<Jugador>& j);
			
};


#endif /*__MODELO_H__*/
