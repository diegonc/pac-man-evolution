#include "client_Cliente.h"
#include <iostream>
#include "common_Errores.h"

Cliente::Cliente( Evento& t ) : fin_app( t ) { }

void* Cliente::run()
{
    #define BUF_SIZE 20
    int error = Error::OK;
    char buffer[BUF_SIZE+1];

    try {
        Socket sock( Socket::TCP );
        sock.set_intentos( 0 );
        sock.connect( ip, port );

        // Lee los primero cuatro bytes que contienen el identificador del
        // cliente
        unsigned int id;
        sock.read( id );
        id = Socket::ntoh( id );

        // se muestra por pantalla
        std::cout << id << std::endl;

        // Luego se leen los datos que vienen del servidor, siempre que no
        // se haya oprimido la tecla X.
        while( !fin_app.probar() ) {
            int r = sock.read( buffer, BUF_SIZE );
            buffer[r] = 0;
            std::cout << buffer;
        }
    } catch( Socket::ConnectionClosed e ) {

    } catch( Error::SystemError e ) {
        if( !e.interrumpido() ){
            // Se no ha sido interrumpido, muestra error.
            std::cerr << e.what() << std::endl;
        }
        error = Error::OTRO;
    }

    std::cout << std::flush;

    fin_app.activar();

    return (void*)error;
}
