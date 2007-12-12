#include "client_App.h"
#include "common_Evento.h"
#include "common_Thread.h"
#include "client_Cliente.h"
#include "common_StringUtil.h"
#include "client_LectorConsola.h"
#include <signal.h>
#include "common_Errores.h"

void App::setup_signal_handler()
{
    struct sigaction sa;
    sigaction(SIGUSR1, NULL, &sa);
    sa.sa_flags &= ~SA_RESTART;
    sa.sa_handler = signal_handler;
    sigaction(SIGUSR1, &sa, NULL);
}

void App::parse_arguments()
{
    if( argc != 3 )
        throw Error::CMDLINE;

    try {
        StringUtil::convertir( argv[2], port );
    } catch(  StringUtil::ConversionInvalida e ) {
        throw Error::CMDLINE;
    }

    host = argv[1];
}

int App::run()
{
    try {
        Evento fin_aplicacion;
        Cliente cliente( fin_aplicacion );
        LectorConsola lc( fin_aplicacion );

        setup_signal_handler();
        parse_arguments();

        // Inicia el cliente.
        cliente.set_port( port );
        cliente.set_ip( host );
        cliente.start();

        // Inicia el hilo lector de Xs
        lc.start();

        // Espera la finalizacion
        fin_aplicacion.esperar();

        // Se interrumpen las llamadas bloqueantes del hilo cliente.
        cliente.raise( SIGUSR1 );

        int e = (int) cliente.join();
        if( e == Error::OTRO ) {
            std::cout << "\nPresione ENTER para terminar la aplicacion.";
            std::cout << std::endl;
            lc.join();
            e = Error::OK;
        }
        return e;
    }catch( Error::SystemError e ) {
        std::cerr << e.what() << std::endl;
        return Error::OTRO;
    }catch( Error::Codes e ) {
        return e;
    }
}
