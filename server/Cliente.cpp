#include "Cliente.h"

#include "InputBitStream.h"
#include "SocketReader.h"
#include "EscuchadorCliente.h"
#include "EscritorCliente.h"

#include <iostream> //<-----------------SACARRRRRRRRRRRRR


#define _VERSION_ACEPTADA	0

Cliente::Cliente(Tipo_Id id, Socket_Cliente * socket)
{
	
	this->id = id;
	this->socket = socket;
	this->escuchador = new EscuchadorCliente(this);
	this->escritor = new EscritorCliente(this);
	this->jugador = Tipo_Jugador(new Jugador(id));
	
}

void Cliente::run()
{
	escuchador->start();
	escritor->start();
	
	escuchador->join();
	escritor->join();
	/* TODO: esto evita que se reutilice en el cliente del juego.
	 *       tal vez utilizando el patron state y determinando el estado
	 *       inicial en el constructor se puede generalizar.
	 */
	/* Estado: inicial ( servidor ) */
	//Tipo_Jugador j = modelo->get_jugador( id );
	//S_ptr<Paquete> p( new PaqueteInit( j, modelo->get_mapa() ) );
	//enviar_mensaje( p );
	
	/* Estado: espera a inicio ( servidor  ) */
	// espera con evento o algo asi. el esquema observador puede usar
	// cola con espera pasiva pej. ( pareusar/tp4/server_SyncQueue.h )
	// enviar_mensaje( S_ptr<Paquete>( new PaqueteStart( id ) ) );
	
	/* Estado: espera interacciones ( servidor ) */
	// bucle de lectura de paquetes y su procesamiento

	/* Estado: final ( sevidor ) */
	// envia paquete quit
	// sale de run.
	
	/* Transiciones: (servidor)
	 *
	 *                      siguiente mapa
	 *    +-----------------------<-------------------------+
	 *    |                                                 | no mapa
	 * inicial---->espera a inicio---->espera interacciones----------->final
	 *          |                   |                                    |
	 *          +---------->--------+---------------->-------------------+
	 *                                error en socket
	 */
}

Cliente::~Cliente()
{
	if( socket )
		delete socket;
	delete escritor;
	delete escuchador;
}

void Cliente::enviar_mensaje( S_ptr<Paquete> paquete )
{
	OutputBitStream obs;
	paquete->serialize( obs );
	
	const unsigned char* raw = obs.get_data();
	
	for(int i = 0; i < obs.get_size(); i++)
		std::cout << std::hex << (int)raw[i] << " ";
	std::cout << "\n";
	
	socket->escribir( raw, obs.get_size() );
	
	
}

S_ptr<Paquete> Cliente::recibir_mensaje()
{
	SocketReader sr( *socket );
	InputBitStream bs( sr );
	S_ptr<Paquete> sptr_paquete;

	// Lectura de encabezado
	int version = bs.read( 2 );
	if( version == _VERSION_ACEPTADA ) {
		// Lectura de tipo de paquete.
		int tipo = bs.read( 3 );
		S_ptr<Paquete> p(Paquete::crear( tipo ));
		if(p != 0){
			p->deserialize( bs );
			sptr_paquete = p;
		}
	}
	return sptr_paquete;
}
EscritorCliente& Cliente::get_escritor(){
	return *escritor;
}
S_ptr<Jugador> Cliente::get_jugador(){
	return this->jugador;
}
