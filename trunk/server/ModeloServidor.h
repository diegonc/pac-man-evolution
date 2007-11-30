#ifndef __MODELO_H__
#define __MODELO_H__

#include "../common/thread.h"
#include "../common/smart_pointer.h"
#include "MundoBasicImp.h"
#include <string>
#include <list>
#include "Jugador.h"
#include "Objeto.h"
//#include "EstructuralUnitario.h"
#include "../common/observador.h"

/** @brief Esta clase define el modelo.
		   Hereda de thread, ya que se debe actualizar automaticamente todo
		   el tiempo.
 */

class ModeloServidor : public Thread , public Observador{
	typedef S_ptr<Jugador> Tipo_Jugador;
	
	private:
		MundoBajoNivel * mundo;
	
		std::list<Tipo_Jugador> jugadores;
		
		ModeloServidor(ModeloServidor &m);
		
		bool parar;
	
		void cargar_modelo(std::string ruta_mundo);
	
		void preparar_partida();
					
	
	public:
		
		ModeloServidor(std::string ruta_mundo);

		~ModeloServidor();	
	
		void agregar_jugador(Tipo_Jugador jugador);
			
		void run();
	
		MundoBajoNivel& get_mundo();
	
		S_ptr<Jugador> get_jugador(int id);
	
		const std::list<S_ptr<Jugador> >& get_jugadores();
	
		void revisar_colisiones(S_ptr<Jugador>& j);
		
		virtual void actualizar(Observable * observable, void * param);
};


#endif /*__MODELO_H__*/
