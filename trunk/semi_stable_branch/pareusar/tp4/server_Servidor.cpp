#include "server_Servidor.h"
#include "common_Errores.h"

Servidor::Servidor( int port ) : sock( Socket::TCP ), port( port )
{
    // Inicializa el socket
    sock.set_reuse_addr( true );
    sock.bind( port );
    sock.listen();
}

void *Servidor::run()
{
    int err = 0;

    try {
        while( true ) {
            Socket* client = sock.accept();
            pool.lanzar_cliente( client );
        }
    } catch( Error::SystemError e ) {
        // En caso de haber sido interrumpido concluye sin error.
        if( !e.interrumpido() ) {
            std::cerr << "Servidor: " << e.what() << std::endl;
            err = Error::OTRO;
        }
    }

    pool.join_all();
    return (void*)err;
}
