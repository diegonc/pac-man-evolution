#include "BufferMensajes.h"

S_ptr<BufferMensajes> BufferMensajes::instancia;

BufferMensajes::BufferMensajes(){
	HayMensajesNuevos=false;
	HayMensajesCriticosNuevos=false;
	MaxMensajes=3;
	MaxMensajesCriticos=1;
	
}

BufferMensajes::BufferMensajes(BufferMensajes &j){}

S_ptr<BufferMensajes> BufferMensajes::get_instancia(){
	if( instancia.es_nulo())
		instancia = S_ptr<BufferMensajes>(new BufferMensajes());
	return instancia;
}

void BufferMensajes::add_mensaje_critico(std::string MensajeCritico){
	Bloqueo B(&llaveMensCrit);
	HayMensajesCriticosNuevos=true;
	_colaMensajesCriticos.push(MensajeCritico);
	while (_colaMensajesCriticos.size() > MaxMensajesCriticos)
		_colaMensajesCriticos.pop();
}

void BufferMensajes::add_mensaje(std::string Mensaje){
	Bloqueo B(&llaveMens);

	HayMensajesNuevos=true;
	_colaMensajes.push(Mensaje);
	while (_colaMensajes.size() > MaxMensajes)
		_colaMensajes.pop();
}

std::queue<std::string> BufferMensajes::get_mensajes(){
	Bloqueo B(&llaveMens);
	return _colaMensajes;
}

std::queue<std::string> BufferMensajes::get_mensajes_criticos(){
	Bloqueo B(&llaveMensCrit);
	return _colaMensajesCriticos;
}

void BufferMensajes::set_max_mensajes_criticos(unsigned int MaxMensCrit){
	Bloqueo B(&llaveMensCrit);
	MaxMensajesCriticos=MaxMensCrit;
}

void BufferMensajes::set_max_mensajes(unsigned int MaxMens){
	Bloqueo B(&llaveMens);
	MaxMensajes=MaxMens;
}

bool BufferMensajes::hay_mensajes_nuevos(){
	Bloqueo B(&llaveMens);
	bool Result=HayMensajesNuevos;
	HayMensajesNuevos=false;
	return Result;
}

bool BufferMensajes::hay_mensajes_criticos_nuevos(){
	Bloqueo B(&llaveMensCrit);
	bool Result=HayMensajesCriticosNuevos;
	HayMensajesCriticosNuevos=false;
	return Result;
}

