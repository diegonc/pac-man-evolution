#include <server/Cliente.h>

#include <server/InputBitStream.h>
#include <server/SocketReader.h>
#include <server/EscuchadorCliente.h>
#include <server/EscritorCliente.h>

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

void Cliente::enviar_mensaje( S_ptr<Paquete> paquete )
{
	//Bloqueo b(&llave_escritura);
	OutputBitStream obs;
	
	paquete->serialize( obs );
	const unsigned char* raw = obs.get_data();
	socket->escribir( raw, obs.get_size() );

}

S_ptr<Paquete> Cliente::recibir_mensaje()
{
	//Bloqueo b(&llave_lectura);
	SocketReader sr( *socket );
	InputBitStream bs( sr );
	S_ptr<Paquete> sptr_paquete;
	
	// Lectura de encabezado
	int version = bs.read( 2 );
	if( version == _VERSION_ACEPTADA ) {
		// Lectura de tipo de paquete.
		int tipo = bs.read( 3 );
		Paquete * paquete = Paquete::crear( tipo, get_id() );
      	if( paquete != NULL){		
        	S_ptr<Paquete> p(paquete);
   			if(! p.es_nulo() ){
			   p->deserialize( bs );
			   sptr_paquete = p;
		   }
		}
		
	}
	return sptr_paquete;
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

EscuchadorCliente& Cliente::get_escuchador(){
	return *escuchador;
}

Jugador * Cliente::get_jugador(){
	return this->jugador;
}

void Cliente::terminar(){

   this->jugador->set_invalido();
	this->socket->cerrar();
}
