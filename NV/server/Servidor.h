#ifndef __SERVIDOR_H__
#define __SERVIDOR_H__

#include "../common/Cliente.h"
#include "ClientPool.h"
#include "../common/server_socket.h"
#include "../common/thread.h"
#include "../common/evento.h"
#include "ModeloServidor.h"
#include "MessageDispatcher.h"
#include "../common/smart_pointer.h"
#include "../common/observador.h"
#include "AvisadorNovedades.h"
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
		
      AvisadorNovedades* avisador;		

      unsigned int cant_min_clientes;
		unsigned int cant_max_clientes;
	
		Socket_Server * socket;

		bool ejecutando; //Determina si el servidor se esta ejecutando o no	

      Evento* llave_max_jugadores; //Evento que traba al servidor cuando se alcanza la cantidad maxima de jugadores

      bool ya_mando_start; //Controla si se manda el primer start en cada nivel

      bool debo_cambiar_nivel; //Controla si el server tiene que cambiar de nivel o no

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

      void finalizar_servidor();

      bool esta_ejecutando();
		
		void actualizar(Observable * observable, void * param);

    private:

     void inicializar();

     Cliente* aceptar_nuevo_cliente();

     void iniciar_nivel();

     void procesar_nivel();

     void finalizar_nivel();

     void cambiar_nivel();

     void mandar_init(Cliente* cliente);

     void mandar_start(Cliente* cliente);
	
	 void mandar_stop(const char razon);
	
	 void mandar_quit();
	
};

#endif /*__SERVIDOR_H__*/
