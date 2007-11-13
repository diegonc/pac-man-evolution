#ifndef __CODEC_H__
#define __CODEC_H__

/** @brief Clase que representa a un cliente que se conecta al servidor
 *
 *	Permite la comunicacion con el servidor asi como tambien le da entidad
 *	al cliente al cual esta conectado
 *	Implementado en un hilo aparte
 */
#include "../common/socket.h"
#include "../common/thread.h"
#include "Paquete.h"
#include "../common/smart_pointer.h"

class Cliente{
	typedef unsigned int Tipo_Id;
	
	private:
		Socket_Cliente * socket;
		Tipo_Id id;
	public:
		
		/** @brief Constructor de la clase
		 *
		 *  @param id Id del cliente
		 *  @param socket Socket por el cual establece la comunicacion
		 */
		Cliente(Tipo_Id id, Socket_Cliente * socket):id(id), socket(socket){}
		
		/** @brief Devuelve el id del Cliente
		 *
		 *  @return id Id del cliente
		 */	
		Tipo_id get_id();
			
		void enviar_mensaje(S_ptr<Paquete> paquete/*TODO no se si el paquete y las operacones pegan aca*/);
			
		S_ptr<Paquete> recibir_mensaje();
					
		void run();
	
		
		
		
	
};


#endif /*__CODEC_H__*/
