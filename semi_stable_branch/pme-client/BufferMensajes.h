#ifndef BUFFER_MENSAJES_H
#define BUFFER_MENSAJES_H

#include <common/smart_pointer.h>
#include <queue>
#include <common/bloqueo.h>


class BufferMensajes{
	private:
		BufferMensajes();
	
		BufferMensajes(BufferMensajes &j);
	
		static S_ptr<BufferMensajes> instancia;
		
		std::queue<std::string> _colaMensajesCriticos;

		std::queue<std::string> _colaMensajes;

		unsigned int MaxMensajesCriticos;

		unsigned int MaxMensajes;

		Mutex llaveMensCrit;

		Mutex llaveMens;

		bool HayMensajesNuevos;						

		bool HayMensajesCriticosNuevos;
	
	public:
		
		static S_ptr<BufferMensajes> get_instancia();
	
		void add_mensaje_critico(std::string MensajeCritico);

		void add_mensaje(std::string Mensaje);

		std::queue<std::string> get_mensajes();

		std::queue<std::string> get_mensajes_criticos();

		void set_max_mensajes_criticos(unsigned int MaxMensCrit);

		void set_max_mensajes(unsigned int MaxMens);

		bool hay_mensajes_nuevos();

		bool hay_mensajes_criticos_nuevos();


};

#endif /*BUFFER_MENSAJES_H*/
