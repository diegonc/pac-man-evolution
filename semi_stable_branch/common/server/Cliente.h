#ifndef __CODEC_H__
#define __CODEC_H__

/** @brief Clase que representa a un cliente que se conecta al servidor
 *
 *	Permite la comunicacion con el servidor asi como tambien le da entidad
 *	al cliente al cual esta conectado
 *	Implementado en un hilo aparte
 */
#include "../common/client_socket.h"
#include "../common/thread.h"
#include "Paquete.h"
#include "Jugador.h"
#include "../common/bloqueo.h"
#include "../common/smart_pointer.h"
#include "../common/ModeloCommon.h"

class EscritorCliente;
class EscuchadorCliente;

class Cliente : public Thread{
	typedef unsigned int Tipo_Id;
	//typedef Jugador * Tipo_Jugador;
	
	private:
		Socket_Cliente * socket;
		EscuchadorCliente * escuchador;
		EscritorCliente * escritor;	
		Mutex llave_lectura;
		Mutex llave_escritura;
	
		Tipo_Id id;
		//Tipo_Jugador jugador;
		Jugador * jugador;

		S_ptr<ModeloCommon> modelo;
	
	public:
		
		/** @brief Constructor de la clase
		 *
		 *  @param id Id del cliente
		 *  @param socket Socket por el cual establece la comunicacion
		 *  @param m Modelo en el que vive el cliente.
		 */
		Cliente(Tipo_Id id, Socket_Cliente * socket, S_ptr<ModeloCommon> m);

		/** @brief Constructor de la clase
		 *
		 *  Construye un cliente sin id asignada.
		 *
		 *  @param socket Socket por el cual establece la comunicacion
		 *  @param m Modelo en el que vive el cliente.
		 */
		Cliente( Socket_Cliente * socket, S_ptr<ModeloCommon> m);

		
		/** @brief Destructor de la clase
		 *
		 */
		~Cliente();
	
		/** @brief Devuelve el id del Cliente
		 *
		 *  @return id Id del cliente
		 */	
		Tipo_Id get_id();
		
		/** @brief Devuelve el modelo al que pertenece el cliente.
		 *
		 *  @return Modelo.
		 */	
		ModeloCommon& get_modelo();

		/*TODO no se si el paquete y las operacones pegan aca*/
		
		void enviar_mensaje(S_ptr<Paquete> paquete);
			
		S_ptr<Paquete> recibir_mensaje();
	
		/** @brief Implementacion de thread.
		 *
		 */
		void run();
		
		EscritorCliente& get_escritor();
		
		Jugador * get_jugador();
		
		void terminar();

};


#endif /*__CODEC_H__*/
