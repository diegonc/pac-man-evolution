#include "Cliente.h"

#include "InputBitStream.h"
#include "SocketReader.h"
#include "EscuchadorCliente.h"
#include "EscritorCliente.h"

#include <iostream> //<-----------------SACARRRRRRRRRRRRR


#define _VERSION_ACEPTADA	0

Cliente::Cliente(Tipo_Id id, Socket_Cliente * socket, S_ptr<ModeloCommon> m)
	: modelo( m )
{
	
	this->id = id;
	this->socket = socket;
	this->escuchador = new EscuchadorCliente(this);
	this->escritor = new EscritorCliente(this);
	this->jugador = new Jugador(id);
	
}

Cliente::Cliente(Socket_Cliente * socket, S_ptr<ModeloCommon> m)
	: modelo( m )
{
	
	//this->id = id;
	this->socket = socket;
	this->escuchador = new EscuchadorCliente(this);
	this->escritor = new EscritorCliente(this);
	this->jugador = 0; //new Jugador(id);
	//this->jugador = Tipo_Jugador(new Jugador(id));
}

void Cliente::run()
{
	
	escuchador->start();
	escritor->start();
	
	escuchador->join();
	escritor->join();

}

Cliente::~Cliente()
{
	if( socket )
		delete socket;
	delete escritor;
	delete escuchador;
   if (this->jugador != NULL)   
      this->jugador->set_invalido();
}

void Cliente::enviar_mensaje( Paquete * paquete )
{
	//Bloqueo b(&llave_escritura);
	OutputBitStream obs;
	
	if(paquete != NULL){
		paquete->serialize( obs );
		const unsigned char* raw = obs.get_data();
		socket->escribir( raw, obs.get_size() );
		//delete paquete;
	}
	
}

Paquete * Cliente::recibir_mensaje()
{
	//Bloqueo b(&llave_lectura);
	SocketReader sr( *socket );
	InputBitStream bs( sr );
	Paquete * p;
	
	// Lectura de encabezado
	int version = bs.read( 2 );
	if( version == _VERSION_ACEPTADA ) {
		// Lectura de tipo de paquete.
		int tipo = bs.read( 3 );
		p = Paquete::crear( tipo, get_id() );
      	if( p != NULL ){
		   p->deserialize( bs );
		}
		
	}
	return p;
}

Cliente::Tipo_Id Cliente::get_id(){
	return id;
}

ModeloCommon& Cliente::get_modelo()
{
	return *modelo;
}

EscritorCliente& Cliente::get_escritor(){
	return *escritor;
}
//S_ptr<Jugador> Cliente::get_jugador(){
Jugador * Cliente::get_jugador(){
	return this->jugador;
}

void Cliente::terminar(){
	//this->escritor->terminar();
   this->jugador->set_invalido();
	this->socket->cerrar();
}
