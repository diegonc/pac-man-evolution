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
#include "../common/smart_pointer.h"


class Cliente : public Thread{
	typedef unsigned int Tipo_Id;
	typedef S_ptr<Jugador> Tipo_Jugador;
	
	private:
		Socket_Cliente * socket;
		Tipo_Id id;
		Tipo_Jugador jugador;
	
	public:
		
		/** @brief Constructor de la clase
		 *
		 *  @param id Id del cliente
		 *  @param socket Socket por el cual establece la comunicacion
		 */
		Cliente(Tipo_Id id, Socket_Cliente * socket);
		
		/** @brief Destructor de la clase
		 *
		 */
		~Cliente();
	
		/** @brief Devuelve el id del Cliente
		 *
		 *  @return id Id del cliente
		 */	
		Tipo_Id get_id();
	
		/*TODO no se si el paquete y las operacones pegan aca*/
		
		void enviar_mensaje(S_ptr<Paquete> paquete);
			
		S_ptr<Paquete> recibir_mensaje();
	
		/** @brief Implementacion de thread.
		 *
		 */
		void run();
		
		

};


#endif /*__CODEC_H__*/
