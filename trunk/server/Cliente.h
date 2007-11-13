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
	typedef S_ptr<Personaje> Tipo_Personaje;
	
	private:
		Socket_Cliente * socket;
		Tipo_Id id;
		Tipo_Personaje personaje;
	
	public:
		
		/** @brief Constructor de la clase
		 *
		 *  @param id Id del cliente
		 *  @param socket Socket por el cual establece la comunicacion
		 */
		Cliente(Tipo_Id id, Socket_Cliente * socket, S_ptr<Personaje> personaje):id(id), socket(socket), personaje(personaje){}
		
		/** @brief Devuelve el id del Cliente
		 *
		 *  @return id Id del cliente
		 */	
		Tipo_id get_id();
			
		/*TODO no se si el paquete y las operacones pegan aca*/
		
		void enviar_mensaje(S_ptr<Paquete> paquete);
			
		S_ptr<Paquete> recibir_mensaje();


		/** @brief Devuelve el personaje del cliente.
		 *
		 *  @return id  El personaje del cliente.
		 */
		Tipo_Personaje get_personaje();
			
		/** @brief Asigna un personaje nuevo al cliente.
		 *
		 *  @param id  Personaje que se desee asignar.
		 */
		void set_personaje(Tipo_Personaje personaje);
		
		/** @brief Implementacion de thread.
		 *
		 */
		void run();

};


#endif /*__CODEC_H__*/
