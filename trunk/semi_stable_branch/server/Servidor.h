#ifndef __SERVIDOR_H__
#define __SERVIDOR_H__

#include "../common/Cliente.h"
#include "ClientPool.h"
#include "../common/server_socket.h"
#include "../common/thread.h"
#include "ModeloServidor.h"
#include "../common/smart_pointer.h"
#include "../common/observador.h"
#include <map>
#include <string>
#include <errno.h>
#include <signal.h>

class Servidor : public Thread, public Observador{
	
	typedef unsigned int Tipo_Id_Cliente;
	
	struct sigaction accion_signal;
	
	private:
		static void manejador_signal(int num_signal);
		static const int SENIAL_CANCELAR;
	
	    ClientPool pool;
		
		unsigned int cant_min_clientes;
		unsigned int cant_max_clientes;
	
		Socket_Server * socket;

		bool parar;	
	
		/** Modelo al que se asocia el servidor.
		  */
		//S_ptr<ModeloServidor> modelo;
	
		void set_propiedades_signal(const int id_signal);
	
	public:
		/** @brief Constructor de la clase.
		 *
		 *  @param direccion Direccion ip de la cual va a escuchar
		 *  @param puerto    Puerto del que va a escuchar
		 */
		Servidor(std::string &direccion, unsigned short int puerto);
		
		/** @brief Constructor de la clase. En este caso escucha todas
	     *         las ip
		 *
		 *  @param puerto Puerto a traves del cual se va a comunicar
		 */
		Servidor(unsigned short int puerto);
	
		/** @brief Destructor de la clase.
		 */
		~Servidor();	
	
		/** @brief Implementacion del run de thread
		 *
		 */
		void run();
		
		void set_cant_min_clientes(unsigned int cant);
		
		void set_cant_max_clientes(unsigned int cant);
		
		void actualizar(Observable * observable, void * param);
		
};
#endif /*__SERVIDOR_H__*/