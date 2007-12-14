#include "server_Cliente.h"
#include <iostream>

Cliente::Cliente( Socket* s, unsigned int id ) : sock( s ), id( id )
{
    Log::getInstance().add_observer( this );
}

Cliente::~Cliente()
{
    Log::getInstance().remove_observer( this );
    delete sock;
}

void* Cliente::run()
{
    EventPool& eventos = EventPool::getInstance();

    try {
        // Manda id de cliente
        sock->write( Socket::hton( id ) );

        while( !eventos.probar( "simulacion-fin" ) ) {
            pending.wait();
            while(!pending.empty() ) {
                LogEntry* e = pending.pop();

                // envia e por socket
                sock->write( e->raw_form() );
                e->destruir();
            }
        }

        // Despacha los eventos que podrian haber ingresado pero no fueron
        // procesados por haber recibido el evento de finalizacion
        while( !pending.empty() ) {
            LogEntry* e = pending.pop();

            // envia e por socket
            sock->write( e->raw_form() );
            e->destruir();
        }
    } catch( Socket::ConnectionClosed e ) { }

    return 0;
}

void Cliente::notify( LogEntry* le )
{
    pending.push( le );
}
